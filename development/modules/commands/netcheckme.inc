#if defined _attdef_cmd_netcheckme
	#endinput
#endif
#define _attdef_cmd_netcheckme

forward RemoveTempNetcheck(playerid);
public RemoveTempNetcheck(playerid)
{
	Player[playerid][TempNetcheck] = false;
	return 1;
}

YCMD: netcheckme(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "temporarily netcheck yourself until an admin does it for you");
	if (Player[playerid][TempNetcheck])
		return SendErrorMessage(playerid, "Netcheck is already temporarily disabled on you");
	if (!Player[playerid][NetCheck])
		return SendErrorMessage(playerid, "You've already got netcheck disabled on you");

	new dummyHour, dummyMinute, dummySecond, timeStamp = gettime(dummyHour, dummyMinute, dummySecond);
	if (Player[playerid][NetCheckTimeoutTimestamp] != -1 && (timeStamp - Player[playerid][NetCheckTimeoutTimestamp]) <= 15 * 60)
		return SendErrorMessage(playerid, "You must wait 15 minutes before you can netcheck yourself again");

	Player[playerid][NetCheckTimeoutTimestamp] = timeStamp;
	Player[playerid][TempNetcheck]			   = true;
	SetTimerEx("RemoveTempNetcheck", 45000, false, "i", playerid);
	SendClientMessage(playerid, -1, COL_PRIM "You've been temporarily netchecked for 45 seconds only.");
	return SendClientMessageToAll(-1, va_return("{FFFFFF}%s (%d) " COL_PRIM "requests permanent {FFFFFF}net-check" COL_PRIM ".", Player[playerid][Name], playerid));
}
