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

	new health = GetHP(playerid);
	new armour = GetAP(playerid);

	RemovePlayerFromRound(playerid);
	return va_SendClientMessageToAll(-1, "%s (%d) " COL_PRIM "removed himself from round. {FFFFFF}(HP %d | AP %d)", Player[playerid][Name], playerid, health, armour);
}
