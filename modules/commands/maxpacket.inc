#if defined _attdef_cmd_maxpacket
	#endinput
#endif
#define _attdef_cmd_maxpacket

YCMD: maxpacket(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "set maximum packet-loss limit.");
	if (isnull(params))
		return SendUsageMessage(playerid, "/maxpacket [Maximum Packetloss]");

	new Float: iPacket = floatstr(params);
	if (iPacket <= 0 || iPacket > 10)
		return SendErrorMessage(playerid, "Packetloss value can be between 0 and 10 maximum.");

	Max_Packetloss = iPacket;

	new iString[144];
	format(iString, sizeof(iString), "UPDATE Configs SET Value = %.2f WHERE Option = 'Maximum Packetloss'", iPacket);
	db_free_result(db_query(sqliteconnection, iString));

	LogAdminCommand("maxpacket", playerid, INVALID_PLAYER_ID);

	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has changed maximum packet-loss to: {FFFFFF}%.2f", Player[playerid][Name], iPacket);
	return SendClientMessageToAll(-1, iString);
}
