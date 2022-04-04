#if defined _attdef_cmd_slap
	#endinput
#endif
#define _attdef_cmd_slap

YCMD: slap(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 2 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level to do that.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "slap a player ass a few meters in the air.");
	if (isnull(params))
		return SendUsageMessage(playerid, "/slap [Player ID]");

	new sid = strval(params);
	if (!IsPlayerConnected(sid))
		return SendErrorMessage(playerid, "That player isnt connected.");

	new Float: posX,
		Float: posY,
		Float: posZ;
	GetPlayerPos(sid, posX, posY, posZ);
	SetPlayerPos(sid, posX, posY, posZ + 10);

	PlayerPlaySound(playerid, 1190, 0.0, 0.0, 0.0);
	PlayerPlaySound(sid, 1190, 0.0, 0.0, 0.0);

	LogAdminCommand("slap", playerid, sid);

	new iString[128];
	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has slapped {FFFFFF}%s", Player[playerid][Name], Player[sid][Name]);
	return SendClientMessageToAll(-1, iString);
}
