#if defined _attdef_cmd_customtitle
	#endinput
#endif
#define _attdef_cmd_customtitle

#include <YSI_Coding\y_hooks>

static Iterator: s_ActiveTitles<MAX_PLAYERS>;
static s_Titles[MAX_PLAYERS][64];
static currentTitle;
static Timer: updateTimer = Timer: 0;

hook OnScriptInit()
{
	Iter_Clear(s_ActiveTitles);
	currentTitle = Iter_Alloc(s_ActiveTitles);
#if defined _YSF_included
	GetConsoleVarAsString("hostname", s_Titles[currentTitle]);
#else
	GetConsoleVarAsString("name", s_Titles[currentTitle]);
#endif
	if (Timer_IsRunning(updateTimer))
		stop updateTimer;
	updateTimer = Timer: 0;
	return 1;
}

timer UpdateTitle[5000]()
{
	SendRconCommand("hostname %s", s_Titles[currentTitle]);
	currentTitle = currentTitle == Iter_Last(s_ActiveTitles) ? Iter_First(s_ActiveTitles) : Iter_Next(s_ActiveTitles, currentTitle);
	return 1;
}

static CustomTitle_ShowDialog(playerid)
{
	inline const addTitle(response, listitem, string: inputtext[])
	{
#pragma unused listitem
		if (!response)
			return 1;

		new titleIndex = Iter_Alloc(s_ActiveTitles);
		format(s_Titles[titleIndex], sizeof(s_Titles[]), "%s", inputtext);
		if (!Timer_IsRunning(updateTimer))
			updateTimer = repeat UpdateTitle();
		return 1;
	}
	inline const removeTitle(pid, response, item_value, string: inputtext[])
	{
#pragma unused pid, inputtext
		if (!response)
			return 1;
		if (currentTitle == item_value)
			currentTitle = currentTitle == Iter_Last(s_ActiveTitles) ? Iter_First(s_ActiveTitles) : Iter_Next(s_ActiveTitles, currentTitle);
		Iter_Remove(s_ActiveTitles, item_value);
		if (Iter_Count(s_ActiveTitles) == 1)
		{
			stop updateTimer;
			UpdateTitle();
		}
		return 1;
	}
	inline const readOptions(pid, did, response, listitem, string: inputtext[])
	{
#pragma unused did, inputtext
		if (!response)
			return 1;
		if (listitem == 0)
			Dialog_ShowCallback(pid, using inline addTitle, DIALOG_STYLE_INPUT, "Add server title", "Enter a new title:", "Ok", "Cancel");
		else if (listitem == 1)
		{
			foreach (new i : s_ActiveTitles) { DynDialog_AddItem(pid, i, s_Titles[i]); }
			DynDialog_Show(pid, using inline removeTitle, DIALOG_STYLE_LIST, "Remove server titles", "Ok", "Cancel", 15);
		}
		return 1;
	}
	if (Iter_Count(s_ActiveTitles) == 1)
		Dialog_ShowCallback(playerid, using inline readOptions, DIALOG_STYLE_LIST, "Looping server titles", "Add", "Ok", "Cancel");
	else
		Dialog_ShowCallback(playerid, using inline readOptions, DIALOG_STYLE_LIST, "Looping server titles", "Add\nRemove", "Ok", "Cancel");
	return 1;
}

YCMD: customtitle(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "set a looping server title");
	CustomTitle_ShowDialog(playerid);
	return 1;
}
