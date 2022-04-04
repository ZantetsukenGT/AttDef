#if defined _attdef_cmd_fakepacket
	#endinput
#endif
#define _attdef_cmd_fakepacket

forward FakePacketRenovationEnd(playerid, Float: fakepacket, bool: message);
public FakePacketRenovationEnd(playerid, Float: fakepacket, bool: message)
{
	if (!Player[playerid][FakePacketRenovation] || !IsPlayerConnected(playerid))
		return 0;

	Player[playerid][FakePacketRenovation] = false;
	if (message)
	{
		new Float: currPacket = NetStats_PacketLossPercent(playerid);
		if (currPacket >= fakepacket)
		{
			new str[160];
			format(
				str, sizeof str, "" COL_PRIM "Fake PL renovation on {FFFFFF}%s " COL_PRIM "has failed - Old: {FFFFFF}%.2f " COL_PRIM " | Current: {FFFFFF}%.2f",
				Player[playerid][Name], fakepacket, currPacket);
			return SendClientMessageToAll(-1, str);
		}
		new str[160];
		format(
			str, sizeof str, "" COL_PRIM "Fake PL renovation on {FFFFFF}%s " COL_PRIM "has ended - Old: {FFFFFF}%.2f " COL_PRIM " | Current: {FFFFFF}%.2f", Player[playerid][Name],
			fakepacket, currPacket);
		return SendClientMessageToAll(-1, str);
	}
	return 1;
}

YCMD: fakepacket(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level.");
	if (help)
		return SendCommandHelpMessage(playerid, "disable packet-loss status check on a player for a specific time.");

	new pID, interv;
	if (sscanf(params, "id", pID, interv))
		return SendUsageMessage(playerid, "/fakepacket [Player ID] [Time in minutes]");
	if (!IsPlayerConnected(pID))
		return SendErrorMessage(playerid, "That player isn't connected.");
	if (interv <= 0 || interv > 5)
		return SendErrorMessage(playerid, "Invalid (Min: 1 | Max: 5).");
	if (Player[pID][FakePacketRenovation])
		return SendErrorMessage(playerid, "Player is already on fake packetloss renovation.");
	if (NetStats_PacketLossPercent(pID) == 0.0)
		return SendErrorMessage(playerid, "That player has 0.0% packet-loss");

	SetPreciseTimer("FakePacketRenovationEnd", interv * 60 * 1000, false, "ifb", pID, NetStats_PacketLossPercent(pID), true);
	Player[pID][FakePacketRenovation] = true;

	LogAdminCommand("fakepacket", playerid, pID);

	new str[160];
	format(
		str, sizeof str, "{FFFFFF}%s " COL_PRIM "has started fake packetloss renovation on {FFFFFF}%s " COL_PRIM " - Interval: {FFFFFF}%d min(s).", Player[playerid][Name],
		Player[pID][Name], interv);
	return SendClientMessageToAll(-1, str);
}
