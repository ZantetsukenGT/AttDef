#if defined dyn_dialog_pages_included
	#endinput
#endif
#define dyn_dialog_pages_included

/**
	Yet another Dialog Pages Library that leverages malloc to avoid declaring super huge arrays at compile time.
	API heavily inspired by Nickk888SAMP's own library.

	Also leverages y_dialog, y_va and y_inline
*/

/** API
DynDialog_AddItem(playerid, item_value, const itemstring[], va_args<>);
DynDialog_Show(playerid, Func: callback<iiis>, DIALOG_STYLE: style, const title[], const button1[], const button2[] = "", const items_per_page, const nextbutton[] = "{FF0000}>>>", const backbutton[] = "{FF0000}<<<");
DynDialog_Destroy(playerid);
*/

#if !defined MAX_PLAYERS
	#warning it is recommended that you define `MAX_PLAYERS` before the `dyn-dialog-pages` include or any `YSI` include for a potentially smaller gamemode size.
#endif

#include <open.mp>
#include <YSI_Visual\y_dialog>
#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_hooks>

#if !defined MAX_DIALOG_ITEMS
	#define MAX_DIALOG_ITEMS (1024 * MAX_PLAYERS)
#endif

#if defined DYNDIALOG_NO_CB
	#undef DYNDIALOG_NO_CB
#endif
#define DYNDIALOG_NO_CB (Func: 0<iiis>)

#if !defined DIALOG_STYLE
	#define DIALOG_STYLE: _:
#endif

static enum E_PAGE_DIRECTION {
	PREVIOUS,
	STAY,
	NEXT
}

static stock Iterator: s_ItemOwnerships<MAX_PLAYERS, MAX_DIALOG_ITEMS>;

static stock Alloc: s_DialogItems[MAX_DIALOG_ITEMS]		= { NO_ALLOC, ... };
static stock s_ItemLength[MAX_DIALOG_ITEMS char]		= { 0, ... };
static stock s_AdditionalItemData[MAX_DIALOG_ITEMS]		= { 0, ... };

static stock bool: s_Shown[MAX_PLAYERS char]			= { false, ... };
static stock Func: s_Callback<iiis>[MAX_PLAYERS]		= { DYNDIALOG_NO_CB, ... };
static stock s_ItemCount[MAX_PLAYERS]					= { 0, ... };
static stock s_CurrentPage[MAX_PLAYERS]					= { 0, ... };
static stock s_CurrentPageFirstItemIndex[MAX_PLAYERS]	= { cellmin, ... }; // absolute index for `MAX_DIALOG_ITEMS` sized arrays
static stock s_CurrentNextButtonIndex[MAX_PLAYERS char] = { -1, ... };		// response's listitem index
static stock s_CurrentBackButtonIndex[MAX_PLAYERS char] = { -1, ... };		// response's listitem index

static stock DynDialog_ResetInternal(playerid)
{
	foreach (new i : s_ItemOwnerships<playerid>)
	{
		free(s_DialogItems[i]);
		s_DialogItems[i]		= NO_ALLOC;
		s_ItemLength { i }		= 0;
		s_AdditionalItemData[i] = 0;
	}
	Iter_Clear(s_ItemOwnerships<playerid>);
	s_ItemCount[playerid]				  = 0;
	s_Shown { playerid }				  = false;
	s_CurrentPage[playerid]				  = 0;
	s_CurrentPageFirstItemIndex[playerid] = cellmin;
	s_CurrentNextButtonIndex { playerid } = -1;
	s_CurrentBackButtonIndex { playerid } = -1;
}

static stock DynDialog_ResetAllInternal(playerid)
{
	DynDialog_ResetInternal(playerid);
	if (s_Callback[playerid])
	{
		Indirect_Release(s_Callback[playerid]);
		s_Callback[playerid] = DYNDIALOG_NO_CB;
	}
}

stock DynDialog_Destroy(playerid)
{
	if (s_Shown { playerid })
#if defined HidePlayerDialog
		return HidePlayerDialog(playerid);
#else
		return ShowPlayerDialog(playerid, -1, DIALOG_STYLE_MSGBOX, #, #, #, #);
#endif
	return 0;
}

stock DynDialog_AddItem(playerid, item_value, const itemstring[], va_args<>)
{
	if (s_Shown { playerid })
		DynDialog_Destroy(playerid);

	new allocIndex = Iter_Alloc(s_ItemOwnerships<playerid>);
	if (allocIndex == cellmin)
		return 0;

	new formatted_item[YSI_MAX_STRING];
	va_format(formatted_item, sizeof(formatted_item), itemstring, va_start<3>);
	strcat(formatted_item, "\n");

	s_DialogItems[allocIndex] = Malloc_NewS(formatted_item, true);
	if (!s_DialogItems[allocIndex])
	{
		Iter_Remove(s_ItemOwnerships<playerid>, allocIndex);
		return 0;
	}
	s_ItemLength { allocIndex }		 = strlen(formatted_item);
	s_AdditionalItemData[allocIndex] = item_value;
	return 1;
}

static stock DynDialog_CalculatePage(playerid, E_PAGE_DIRECTION: direction, items_per_page, bool: style_has_headers, const nextbutton[], const backbutton[])
{
	new dialog_info[4096 + 1], item[YSI_MAX_STRING];
	new this_page_first_index = s_CurrentPage[playerid] * items_per_page + _: style_has_headers;
	new items_on_page		  = min(s_ItemCount[playerid] - this_page_first_index, items_per_page);
	new currentLength		  = 0;

	new itemIndex			  = Iter_First(s_ItemOwnerships<playerid>);
	if (style_has_headers)
	{
		Malloc_GetS(item, sizeof(item), s_DialogItems[itemIndex], 0, true);
		strins(dialog_info, item, currentLength);
		currentLength += s_ItemLength { itemIndex };
		itemIndex = Iter_Next(s_ItemOwnerships<playerid>, itemIndex);
	}

	if (s_CurrentPageFirstItemIndex[playerid] == cellmin)
		s_CurrentPageFirstItemIndex[playerid] = itemIndex;
	else
		itemIndex = s_CurrentPageFirstItemIndex[playerid];

	// need to skip `items_per_page` items in the iterator to get to the correct page
	if (direction == NEXT)
	{
		for (new i = 0; i < items_per_page; i++) { itemIndex = Iter_Next(s_ItemOwnerships<playerid>, itemIndex); }
	}
	else if (direction == PREVIOUS)
	{
		for (new i = 0; i < items_per_page; i++) { itemIndex = Iter_Prev(s_ItemOwnerships<playerid>, itemIndex); }
	}

	s_CurrentPageFirstItemIndex[playerid] = itemIndex;
	for (new i = 0; i < items_on_page; i++)
	{
		Malloc_GetS(item, sizeof(item), s_DialogItems[itemIndex], 0, true);
		strins(dialog_info, item, currentLength);
		currentLength += s_ItemLength { itemIndex };
		itemIndex = Iter_Next(s_ItemOwnerships<playerid>, itemIndex);
	}

	if (this_page_first_index + items_on_page == s_ItemCount[playerid]) // must be the last page
	{
		if (s_CurrentPage[playerid] == 0) // and its the first page
		{
			s_CurrentNextButtonIndex { playerid } = s_CurrentBackButtonIndex { playerid } = -1;
			return dialog_info;
		}
		s_CurrentNextButtonIndex { playerid } = -1;
		s_CurrentBackButtonIndex { playerid } = items_on_page;
		strins(dialog_info, backbutton, currentLength);
		return dialog_info;
	}
	if (s_CurrentPage[playerid] == 0) // its the first page and cannot be the last
	{
		s_CurrentNextButtonIndex { playerid } = items_on_page;
		s_CurrentBackButtonIndex { playerid } = -1;
		strins(dialog_info, nextbutton, currentLength);
		return dialog_info;
	}
	s_CurrentNextButtonIndex { playerid } = items_on_page;
	s_CurrentBackButtonIndex { playerid } = items_on_page + 1;
	strins(dialog_info, nextbutton, currentLength);
	currentLength += strlen(nextbutton);
	strins(dialog_info, "\n", currentLength);
	currentLength += 1;
	strins(dialog_info, backbutton, currentLength);
	return dialog_info;
}

stock DynDialog_Show(playerid, Func: callback<iiis>, DIALOG_STYLE: style, const title[], const button1[], const button2[] = "",
					 const items_per_page, const nextbutton[] = "{FF0000}>>>", const backbutton[] = "{FF0000}<<<")
{
	new bool: style_has_headers = style == DIALOG_STYLE_TABLIST_HEADERS;
	if (s_Shown { playerid } || (s_ItemCount[playerid] = Iter_Count(s_ItemOwnerships<playerid>)) - _: style_has_headers < 1)
		return 0;
	inline const dialog_response(response, listitem, string: inputtext[])
	{
		if (listitem == s_CurrentNextButtonIndex { playerid })
		{
			s_CurrentPage[playerid]++;
			Dialog_ShowCallback(
				playerid, using inline dialog_response, style, title,
				DynDialog_CalculatePage(playerid, NEXT, items_per_page, style_has_headers, nextbutton, backbutton), button1,
				button2);
			return 1;
		}
		else if (listitem == s_CurrentBackButtonIndex { playerid })
		{
			s_CurrentPage[playerid]--;
			Dialog_ShowCallback(
				playerid, using inline dialog_response, style, title,
				DynDialog_CalculatePage(playerid, PREVIOUS, items_per_page, style_has_headers, nextbutton, backbutton), button1,
				button2);
			return 1;
		}

		// need to skip `listitem` items starting from currentItemIndex to get the correct item's `item_value`
		new itemIndex			= s_CurrentPageFirstItemIndex[playerid];
		for (new i = 0; i < listitem; i++) { itemIndex = Iter_Next(s_ItemOwnerships<playerid>, itemIndex); }
		new item_value	  = s_AdditionalItemData[itemIndex];

		new Func: func<iiis> = s_Callback[playerid];
		s_Callback[playerid]  = DYNDIALOG_NO_CB;
		DynDialog_ResetInternal(playerid);
		@.func(playerid, response, item_value, inputtext);
		Indirect_Release(func);
		return 1;
	}
	Indirect_Claim(callback);
	s_Callback[playerid] = callback;

	Dialog_ShowCallback(
		playerid, using inline dialog_response, style, title,
		DynDialog_CalculatePage(playerid, STAY, items_per_page, style_has_headers, nextbutton, backbutton), button1, button2);
	s_Shown { playerid } = true;
	return 1;
}

#if defined HidePlayerDialog
hook native HidePlayerDialog(playerid)
{
	if (s_Shown { playerid })
		DynDialog_ResetAllInternal(playerid);
	return continue(playerid);
}
#endif

hook native ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE: style, const title[], const body[], const button1[], const button2[]){
	if (s_Shown { playerid })
		DynDialog_ResetAllInternal(playerid);
	return continue(playerid, dialogid, style, title, body, button1, button2);
}

hook OnPlayerConnect(playerid)
{
	if (s_Shown { playerid })
		DynDialog_ResetAllInternal(playerid);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
	if (s_Shown { playerid })
		DynDialog_ResetAllInternal(playerid);
	return 1;
}
