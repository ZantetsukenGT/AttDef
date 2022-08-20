#if defined _attdef_cmd_pm
	#endinput
#endif
#define _attdef_cmd_pm

YCMD: pm(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "send a private message to a specific player.");
	if (Player[playerid][Mute])
		return SendErrorMessage(playerid, "You are muted.");

	new receiverID, message[144];
	if (sscanf(params, "rs[144]", receiverID, message))
		return SendUsageMessage(playerid, "/pm [Player Name/ID] [Message]");
	if (receiverID == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "Player not connected.");

	if (Player[receiverID][blockedid] == playerid)
		return SendErrorMessage(playerid, "That player has blocked PMs from you.");
	if (Player[receiverID][blockedall])
		return SendErrorMessage(playerid, "That player has blocked PMs from everyone.");
	if (Player[receiverID][Mute] && Player[playerid][Team] != Player[receiverID][Team])
		return SendErrorMessage(playerid, "That player is currently muted and can not reply!");

	new str[144];
	format(str, sizeof(str), "PM from %s (%d): %s", Player[playerid][Name], playerid, message);
	SendClientMessage(receiverID, 0xFFF000FF, str);

	SendClientMessage(receiverID, -1, "" COL_PRIM "Use {FFFFFF}/r [Message]" COL_PRIM " to reply quicker!");
	Player[receiverID][LastMsgr] = playerid;

	format(str, sizeof(str), "PM to %s (%d): %s", Player[receiverID][Name], receiverID, message);
	SendClientMessage(playerid, 0xECDE00FF, str);

	return PlayerPlaySound(receiverID, 1054, 0, 0, 0);
}
