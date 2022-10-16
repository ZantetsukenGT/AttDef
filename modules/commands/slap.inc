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
	new sid;
	if (sscanf(params, "r", sid))
		return SendUsageMessage(playerid, "/slap [Player Name/ID]");

	if (sid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isnt connected.");

	new Float: posX,
		Float: posY,
		Float: posZ;
	GetPlayerPos(sid, posX, posY, posZ);
	SetPlayerPos(sid, posX, posY, posZ + 10);

	PlayerPlaySound(playerid, 1190, 0.0, 0.0, 0.0);
	PlayerPlaySound(sid, 1190, 0.0, 0.0, 0.0);

	LogAdminCommand("slap", playerid, sid);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has slapped {FFFFFF}%s", Player[playerid][Name], Player[sid][Name]);
}
