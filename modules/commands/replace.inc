#if defined _attdef_cmd_replace
	#endinput
#endif
#define _attdef_cmd_replace

YCMD: replace(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "replace players whether they're connected to the server or not.");
	if (Current == -1)
		return SendErrorMessage(playerid, "Round is not active.");

	LogAdminCommand("replace", playerid, INVALID_PLAYER_ID);

	foreach (new i : Player)
	{
		if (Player[i][InDuel] || Player[i][IsAFK] || !Player[i][Spawned])
			continue;

		AddDialogListitem(playerid, Player[i][Name]);
	}
	ShowPlayerDialog(playerid, DIALOG_REPLACE_FIRST, DIALOG_STYLE_LIST, COL_PRIM "Player to add", #, "Process", "Cancel", 15);
	return 1;
}
