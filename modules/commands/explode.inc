#if defined _attdef_cmd_explode
	#endinput
#endif
#define _attdef_cmd_explode

YCMD: explode(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 2 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "explode a specific player.");
	new eid;
	if (sscanf(params, "r", eid))
		return SendUsageMessage(playerid, "/explode [Player Name/ID]");

	if (eid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isn't connected.");

	new Float: x,
		Float: y,
		Float: z;
	GetPlayerPos(eid, x, y, z);
	CreateExplosion(x, y, z, 7, 6.0);

	LogAdminCommand("explode", playerid, eid);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has exploded {FFFFFF}%s" COL_PRIM ".", Player[playerid][Name], Player[eid][Name]);
}
