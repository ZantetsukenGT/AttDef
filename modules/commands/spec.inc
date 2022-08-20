#if defined _attdef_cmd_spec
	#endinput
#endif
#define _attdef_cmd_spec

YCMD: spec(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "enable you to spectate someone.");

	new specid;
	if (sscanf(params, "r", specid))
		return SendUsageMessage(playerid, "/spec [Player Name/ID]");

	return PerformCommandSpec(playerid, specid);
}

PerformCommandSpec(playerid, specid)
{
	if (specid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "That player isn't connected.");
	if (specid == playerid)
		return SendErrorMessage(playerid, "Can't spectate yourself.");
	if (Player[playerid][Playing])
		return SendErrorMessage(playerid, "Can't spectate while you are playing.");
	if (Player[specid][Spectating])
		return SendErrorMessage(playerid, "That player is spectating someone else.");
	if (GetPlayerState(specid) != 1 && GetPlayerState(specid) != 2 && GetPlayerState(specid) != 3)
		return SendErrorMessage(playerid, "That player is not spawned.");
	if (Current != -1 && Player[playerid][Team] != REFEREE && !IsTeamTheSame(Player[specid][Team], Player[playerid][Team]))
		return SendErrorMessage(playerid, "You can only spectate your own team.");
	if (Iter_Count(PlayerSpectators[specid]) == MAX_PLAYER_SPECTATORS)
	{
		if (Player[playerid][InDM])
		{
			Player[playerid][InDM]	  = false;
			Player[playerid][DMReadd] = 0;
		}
	}

	SpectatePlayer(playerid, specid);
	return 1;
}
