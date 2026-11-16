#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_messagebox
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/' folder."
#endif

#if defined _attdef_impl_messagebox
	#endinput
#endif
#define _attdef_impl_messagebox

/*
	MessageBox Script
*/

CreateMessageBoxTextDraws(playerid)
{
	// Top textdraws
	MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_TOP] = CreatePlayerTextDraw(playerid, 341.000000, 92.000000, "caption");
	PlayerTextDrawAlignment(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_TOP], 2);
	PlayerTextDrawBackgroundColor(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_TOP], 34);
	PlayerTextDrawFont(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_TOP], 3);
	PlayerTextDrawLetterSize(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_TOP], 0.419999, 2.000000);
	PlayerTextDrawColor(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_TOP], -1);
	PlayerTextDrawSetOutline(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_TOP], 0);
	PlayerTextDrawSetProportional(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_TOP], 1);
	PlayerTextDrawSetShadow(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_TOP], 1);

	MsgBoxData[playerid][info_TD][MSGBOX_TYPE_TOP] = CreatePlayerTextDraw(playerid, 323.000000, 126.000000, "This is supposed to be a short message otherwise it would look ugly!");
	PlayerTextDrawAlignment(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_TOP], 2);
	PlayerTextDrawBackgroundColor(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_TOP], 34);
	PlayerTextDrawFont(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_TOP], 1);
	PlayerTextDrawLetterSize(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_TOP], 0.200000, 1.200000);
	PlayerTextDrawColor(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_TOP], -1);
	PlayerTextDrawSetOutline(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_TOP], 1);
	PlayerTextDrawSetProportional(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_TOP], 1);

	// Middle textdraws
	MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_MIDDLE] = CreatePlayerTextDraw(playerid, 21.000000, 204.000000, "~y~~h~caption");
	PlayerTextDrawBackgroundColor(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_MIDDLE], 119);
	PlayerTextDrawFont(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_MIDDLE], 3);
	PlayerTextDrawLetterSize(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_MIDDLE], 0.449999, 1.500000);
	PlayerTextDrawColor(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_MIDDLE], -1);
	PlayerTextDrawSetOutline(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_MIDDLE], 0);
	PlayerTextDrawSetProportional(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_MIDDLE], 1);
	PlayerTextDrawSetShadow(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_MIDDLE], 1);

	MsgBoxData[playerid][info_TD][MSGBOX_TYPE_MIDDLE]
		= CreatePlayerTextDraw(playerid, 22.000000, 220.000000, "This is a text. This is another one. The whole paragraph is supposed to be quite long. So, yeah!");
	PlayerTextDrawBackgroundColor(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_MIDDLE], 187);
	PlayerTextDrawFont(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_MIDDLE], 1);
	PlayerTextDrawLetterSize(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_MIDDLE], 0.159999, 1.100000);
	PlayerTextDrawColor(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_MIDDLE], -1);
	PlayerTextDrawSetOutline(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_MIDDLE], 0);
	PlayerTextDrawSetProportional(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_MIDDLE], 1);
	PlayerTextDrawSetShadow(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_MIDDLE], 1);
	PlayerTextDrawUseBox(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_MIDDLE], 1);
	PlayerTextDrawBoxColor(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_MIDDLE], 68);
	PlayerTextDrawTextSize(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_MIDDLE], 179.000000, 0.000000);

	// Bottom textdraws
	MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_BOTTOM] = CreatePlayerTextDraw(playerid, 162.000000, 364.000000, "~y~~h~caption");
	PlayerTextDrawBackgroundColor(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_BOTTOM], MAIN_BACKGROUND_COLOUR);
	PlayerTextDrawFont(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_BOTTOM], 3);
	PlayerTextDrawLetterSize(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_BOTTOM], 0.3, 1.6);
	PlayerTextDrawColor(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_BOTTOM], -1);
	PlayerTextDrawSetOutline(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_BOTTOM], 0);
	PlayerTextDrawSetProportional(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_BOTTOM], 1);
	PlayerTextDrawSetShadow(playerid, MsgBoxData[playerid][caption_TD][MSGBOX_TYPE_BOTTOM], 1);

	MsgBoxData[playerid][info_TD][MSGBOX_TYPE_BOTTOM] = CreatePlayerTextDraw(playerid, 161.000000, 393.000000, "This is the message. We tell the user what's going on here!");
	PlayerTextDrawBackgroundColor(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_BOTTOM], MAIN_BACKGROUND_COLOUR);
	PlayerTextDrawFont(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_BOTTOM], 1);
	PlayerTextDrawLetterSize(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_BOTTOM], 0.17, 1.17);
	PlayerTextDrawColor(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_BOTTOM], -1);
	PlayerTextDrawSetOutline(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_BOTTOM], 1);
	PlayerTextDrawSetProportional(playerid, MsgBoxData[playerid][info_TD][MSGBOX_TYPE_BOTTOM], 1);
	return 1;
}

InitPlayerMessageBox(playerid)
{
	MsgBoxData[playerid][MsgBoxtimer][MSGBOX_TYPE_TOP]	  = PlayerText: 0;
	MsgBoxData[playerid][MsgBoxtimer][MSGBOX_TYPE_MIDDLE] = PlayerText: 0;
	MsgBoxData[playerid][MsgBoxtimer][MSGBOX_TYPE_BOTTOM] = PlayerText: 0;
	return 1;
}

forward HideMessageBox(playerid, MessageBoxType: type);
public HideMessageBox(playerid, MessageBoxType: type)
{
	MsgBoxData[playerid][MsgBoxtimer][type] = 0;
	PlayerTextDrawHide(playerid, MsgBoxData[playerid][info_TD][type]);
	PlayerTextDrawHide(playerid, MsgBoxData[playerid][caption_TD][type]);
	return 1;
}

MessageBox(playerid, MessageBoxType: type, const caption[], const info[], interval = 6000, bool: sound = true)
{
	if (playerid == INVALID_PLAYER_ID)
		return 0;
	if (strlen(caption) < 1)
		return 0;
	if (strlen(info) < 1)
		return 0;
	if (interval < 500)
		return 0;
	if (sound)
		PlayerPlaySound(playerid, 1053, 0.0, 0.0, 0.0);

	PlayerTextDrawSetString(playerid, MsgBoxData[playerid][caption_TD][type], caption);
	PlayerTextDrawSetString(playerid, MsgBoxData[playerid][info_TD][type], info);
	PlayerTextDrawShow(playerid, MsgBoxData[playerid][caption_TD][type]);
	PlayerTextDrawShow(playerid, MsgBoxData[playerid][info_TD][type]);

	if (MsgBoxData[playerid][MsgBoxtimer][type])
		KillTimer(MsgBoxData[playerid][MsgBoxtimer][type]);
	MsgBoxData[playerid][MsgBoxtimer][type] = SetTimerEx("HideMessageBox", interval, false, "ii", playerid, _: type);
	return 1;
}
