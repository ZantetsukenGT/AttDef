#if defined _attdef_cmd_addall
	#endinput
#endif
#define _attdef_cmd_addall

YCMD: addall(playerid, params[], help)
{
	//if(Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be a higher admin level.");
	if (help)
		return SendCommandHelpMessage(playerid, "add everyone to the round.");
	if (Current == -1)
		return SendErrorMessage(playerid, "Round is not active.");

	new bool: addDead = strcmp(params, "dead", true) == 0;
	new ct			  = 0;
	foreach (new i : Player)
	{
		if (addDead && Player[i][WasInBase])
			continue;

		if (!Player[i][Playing] && !Player[i][InDuel] && (Player[i][Team] == ATTACKER || Player[i][Team] == DEFENDER))
		{
			if (WarMode)
			{
				Player[i][Team] = GetTeamWithLessPlayers();
				SwitchTeamFix(i, false, false);
			}
			switch (GameType)
			{
				case BASE:
				{
					AddPlayerToBase(i);
				}
				case ARENA:
				{
					AddPlayerToArena(i);
				}
			}
			ct++;
		}
	}
	if (ct == 0)
	{
		if (addDead)
			return SendErrorMessage(playerid, "Found no players which could be added to the round!");
		else
			return SendErrorMessage(playerid, "No players to add! Did you want to add dead players? Use " COL_PRIM "/addall dead");
	}
	if (!addDead)
		SendUsageMessage(playerid, "to also add players who died, you can type " COL_PRIM "/addall dead");

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has added everyone to the round.", Player[playerid][Name]);
}
