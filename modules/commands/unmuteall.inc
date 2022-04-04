#if defined _attdef_cmd_unmuteall
	#endinput
#endif
#define _attdef_cmd_unmuteall

YCMD: unmuteall(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "unmute everyone.");
	foreach (new i : Player)
		Player[i][Mute] = false;

	LogAdminCommand("unmuteall", playerid, INVALID_PLAYER_ID);

	return SendClientMessageToAll(-1, va_return("{FFFFFF}%s " COL_PRIM "has unmuted everyone!", Player[playerid][Name]));
}
