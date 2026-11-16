#if defined _attdef_cmd_vworld
	#endinput
#endif
#define _attdef_cmd_vworld

YCMD: vworld(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "teleport you to a virtual world.");
	if (!Player[playerid][InDM])
		return SendErrorMessage(playerid, "Can't use this command while you are not in a DM.");
	if (Player[playerid][InDuel])
		return SendErrorMessage(playerid, "Can't use this command during duel.");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "Can't use this command while playing.");
	if (Player[playerid][Spectating])
		return 1;

	new vID;
	if (sscanf(params, "i", vID))
		return SendUsageMessage(playerid, "/vworld [World ID]");

	if (vID <= 5)
		return SendErrorMessage(playerid, "Pick a virtual world above 5.");

	return SetPlayerVirtualWorld(playerid, vID);
}
