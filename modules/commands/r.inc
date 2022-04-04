#if defined _attdef_cmd_r
	#endinput
#endif
#define _attdef_cmd_r

YCMD: r(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "reply to someone's private message to you.");

	new replytoid = Player[playerid][LastMsgr];
	if (replytoid == -1)
		return SendErrorMessage(playerid, "You have not received any private messages since last login.");
	if (Player[playerid][Mute] && Player[playerid][Team] != Player[replytoid][Team])
		return SendErrorMessage(playerid, "You are muted.");
	if (!IsPlayerConnected(replytoid))
		return SendErrorMessage(playerid, "That player is not connected.");
	if (Player[replytoid][blockedid] == playerid)
		return SendErrorMessage(playerid, "That player has blocked PMs from you.");
	if (Player[replytoid][blockedall])
		return SendErrorMessage(playerid, "That player has blocked PMs from everyone.");

	if (isnull(params))
		return SendUsageMessage(playerid, "/r [Message]");
	if (strlen(params) > 142)
		return SendErrorMessage(playerid, "This message is quite long (max: 142 characters).");

	new str[144];
	format(str, sizeof(str), "PM from %s (%d): %s", Player[playerid][Name], playerid, params);
	SendClientMessage(replytoid, 0xFFF000FF, str);

	format(str, sizeof(str), "PM to %s (%d): %s", Player[replytoid][Name], replytoid, params);
	SendClientMessage(playerid, 0xECDE00FF, str);

	Player[replytoid][LastMsgr] = playerid;

	return PlayerPlaySound(replytoid, 1054, 0, 0, 0);
}
