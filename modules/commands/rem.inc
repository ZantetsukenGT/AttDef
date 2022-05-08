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

	new Float: pHP	   = GetPlayerHealth(playerid);
	new Float: pArmour = GetPlayerArmour(playerid);

	RemovePlayerFromRound(playerid);
	va_SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "removed himself from round. {FFFFFF}(HP %.1f | AP %.1f)", Player[playerid][Name], pHP, pArmour);
	return 1;
}
