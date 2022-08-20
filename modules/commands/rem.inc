#if defined _attdef_cmd_rem
	#endinput
#endif
#define _attdef_cmd_rem

YCMD: rem(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "remove yourself from the round.");
	if (!Player[playerid][Playing])
		return SendErrorMessage(playerid, "You are not playing.");
	if (ElapsedTime > 60)
		return SendErrorMessage(playerid, "Too late to remove yourself.");

	new HP[2];
	GetHP(playerid, HP[0]);
	GetAP(playerid, HP[1]);

	RemovePlayerFromRound(playerid);
	return va_SendClientMessageToAll(-1, "{FFFFFF}%s (%d) " COL_PRIM "removed himself from round. {FFFFFF}(HP %d | AP %d)", Player[playerid][Name], playerid, HP[0], HP[1]);
}
