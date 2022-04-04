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
	if (isnull(params))
		return SendUsageMessage(playerid, "/explode [Player ID]");

	new eid = strval(params);
	if (!IsPlayerConnected(eid))
		return SendErrorMessage(playerid, "That player isn't connected.");

	new Float: Pos[3];
	GetPlayerPos(eid, Pos[0], Pos[1], Pos[2]);
	CreateExplosion(Pos[0], Pos[1], Pos[2], 7, 6.0);

	LogAdminCommand("explode", playerid, eid);

	new iString[128];
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has exploded {FFFFFF}%s", Player[playerid][Name], Player[eid][Name]);
	return SendClientMessageToAll(-1, iString);
}
