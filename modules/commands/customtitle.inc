#if defined _attdef_cmd_customtitle
	#endinput
#endif
#define _attdef_cmd_customtitle

static Iterator: s_ActiveTitles<MAX_PLAYERS>;
static s_Titles[MAX_PLAYERS][64];
static dialogString[sizeof(s_Titles) * sizeof(s_Titles[])];
static currentTitle;

hook OnScriptInit()
{
	Iter_Clear(s_ActiveTitles);
	currentTitle = Iter_Free(s_ActiveTitles);
	Iter_Add(s_ActiveTitles, currentTitle);

	s_Titles[currentTitle] = "Community -> ";
	strcat(s_Titles[currentTitle], GM_WEBSITE);
	dialogString[currentTitle] = EOS;
	strcat(dialogString, s_Titles[currentTitle]);
}

task UpdateTitle[6543]()
{
	SendRconCommand("hostname .: %s :.", s_Titles[currentTitle]);
	currentTitle = currentTitle == Iter_Last(s_ActiveTitles) ? Iter_First(s_ActiveTitles): Iter_Next(s_ActiveTitles, currentTitle);
	return 1;
}

static UpdateDialogString()
{
	currentTitle	= 0;
	dialogString[0] = EOS;
	foreach (new i: s_ActiveTitles) { format(dialogString, sizeof(dialogString), "%s%s\n", dialogString, s_Titles[i]); }
}

static CustomTitle_ShowDialog(playerid)
{
	inline addTitle(response, listitem, string: inputtext[])
	{
#pragma unused listitem
		if (!response)
			return 1;

		new titleIndex = Iter_Free(s_ActiveTitles);
		Iter_Add(s_ActiveTitles, titleIndex);
		format(s_Titles[titleIndex], sizeof(s_Titles[]), "%s", inputtext);
		UpdateDialogString();
		return 1;
	}
	inline removeTitle(response, listitem, string: inputtext[])
	{
#pragma unused inputtext
		if (!response)
			return 1;
		Iter_Remove(s_ActiveTitles, listitem);
		UpdateDialogString();
		return 1;
	}
	inline readOptions(pid, did, response, listitem, string: inputtext[])
	{
#pragma unused did, inputtext
		if (!response)
			return 1;
		if (listitem == 0)
			Dialog_ShowCallback(pid, using inline addTitle, DIALOG_STYLE_INPUT, "Add server title", "Enter a new title:", "Ok", "Cancel");
		else if (listitem == 1)
			Dialog_ShowCallback(pid, using inline removeTitle, DIALOG_STYLE_LIST, "Remove server titles", dialogString, "Ok", "Cancel");
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
