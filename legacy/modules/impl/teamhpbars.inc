#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_teamhpbars
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/' folder."
#endif

#if defined _attdef_impl_teamhpbars
	#endinput
#endif
#define _attdef_impl_teamhpbars

/*
	Team HP Bars
*/

#include <YSI_Coding\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
	DeletePlayerTeamBar(playerid);
	return 1;
}

// This finds the Y co-ordinate of the next free place for the team HP bar textdraw
FindPlayerTeamBarY(playerid, &Float: y)
{
	y = TEAMBARS_BAR_START_Y;			// Set the Y co-ordinate to the default value
	foreach (new i : PlayerWithTeamBar) // Loops through all players who have a team bar created for them
	{
		if (!IsTeamTheSame(TeamBarsData[i][TeamBar_Team], Player[playerid][Team])) // If teams aren't the same
			continue;															   // We won't make checks or we will mess up team team bars, so we skip to the next index.

		if (TeamBarsData[i][TeamBar_Y] == y) // If there's a player who got his team bar positioned at this Y co-ordinate
		{
			// So this Y isn't available and is already used.
			y -= TEAMBARS_DIFF_Y; // Set Y value to the next slot/space value and repeat the checks on the next index (player who got team bar and is in the same team as playerid)
			continue;
		}
		// If this Y co-ordinate is free and not used
		break; // We've found what we were looking for, get out of the loop now.
	}
}

// This initializes team bars and creates their textdraws for a specific player
// To be used when you add a player to the round for example, it should not be used for updating values
CreatePlayerTeamBar(playerid)
{
	if (!ShowHPBars)
		return 0;

	// 5 bars for a team is the limit.
	// If more than that, it'd look ugly thus we cancel this operation.
	if (GetTeamBarsCount(Player[playerid][Team]) >= 5)
		return 0;

	if (Iter_Contains(PlayerWithTeamBar, playerid))
		DeletePlayerTeamBar(playerid);

	if (Player[playerid][Team] != ATTACKER && Player[playerid][Team] != DEFENDER)
		return 0;

	new teamToSet	  = Player[playerid][Team];
	new teamBarColour = TEAMBARS_ATTACKER_COLOR;
	new formatToUse[] = "~w~~h~%s ~r~~h~~h~~h~%d/%d";
	if (teamToSet == DEFENDER)
	{
		teamBarColour	= TEAMBARS_DEFENDER_COLOR;
		formatToUse[10] = 'b';
	}

	new Float: y;
	FindPlayerTeamBarY(playerid, y); // Finds a free space for textdraws to be created at
	// Create team progress bar
	TeamBarsData[playerid][TeamBar]		= CreatePlayerProgressBar(playerid, TEAMBARS_BAR_START_X, y, 80.50, 9.19, teamBarColour, 200.0);
	// Create team bar textdraws
	TeamBarsData[playerid][TeamBarText] = TextDrawCreate(
		TEAMBARS_TEXT_START_X, y, va_return(formatToUse, Player[playerid][NameWithoutTag], GetHP(playerid) + GetAP(playerid), floatround(Player[playerid][RoundDamage])));
	TextDrawBackgroundColor(TeamBarsData[playerid][TeamBarText], 51);
	TextDrawFont(TeamBarsData[playerid][TeamBarText], 1);
	TextDrawLetterSize(TeamBarsData[playerid][TeamBarText], 0.160000, 0.900000);
	TextDrawColor(TeamBarsData[playerid][TeamBarText], -1);
	TextDrawSetOutline(TeamBarsData[playerid][TeamBarText], 1);
	TextDrawSetProportional(TeamBarsData[playerid][TeamBarText], 1);

	TeamBarsData[playerid][TeamBar_Team] = teamToSet; // Set the team that this bar is going to be shown for
	TeamBarsData[playerid][TeamBar_Y]	 = y;		  // Indicate that this Y pos is already taken, so that no other textdraws can be placed here
	Iter_Add(PlayerWithTeamBar, playerid);			  // Add this player to the array that holds IDs of players who got team bars
	// Show them to who should see them
	foreach (new i : Player)
	{
		if (Player[i][Playing] || Player[i][Spectating])
			if (IsTeamTheSame(Player[playerid][Team], Player[i][Team]))
			{
				TextDrawShowForPlayer(i, TeamBarsData[playerid][TeamBarText]);
				ShowPlayerProgressBar(i, TeamBarsData[playerid][TeamBar]);
				TeamBarShownForPlayer[i] [_:TeamBarsData[playerid][TeamBar]] = true;
			}
	}
	return 1;
}

// Gets how many bars created in a specific team
GetTeamBarsCount(team)
{
	new ct = 0;
	foreach (new i : PlayerWithTeamBar) // Loops through all players who have a team bar created for them
	{
		if (Player[i][Team] == team)
			ct++;
	}
	return ct;
}

// Shows team bars for a specific player
ShowTeamBarsForPlayer(playerid)
{
	if (!ShowHPBars)
		return 0;

	HideTeamBarsForPlayer(playerid);
	if (Current == -1)
		return 1;

	new PlayerBar: barid;
	foreach (new i : PlayerWithTeamBar) // Loops through all players who have a team bar created for them
	{
		if (!IsTeamTheSame(Player[playerid][Team], TeamBarsData[i][TeamBar_Team]))
			continue;

		barid = TeamBarsData[i][TeamBar];
		if (TeamBarShownForPlayer[playerid] [_:barid])
			continue;

		TeamBarShownForPlayer[playerid] [_:barid] = true;
		TextDrawShowForPlayer(playerid, TeamBarsData[i][TeamBarText]);
		ShowPlayerProgressBar(playerid, barid);
	}
	return 1;
}

// Hide a specifc team bar for a player
TeamBarHideForPlayer(playerid, barofplayerid)
{
	if (!ShowHPBars)
		return;

	new PlayerBar: barid;
	barid = TeamBarsData[barofplayerid][TeamBar];

	if (!TeamBarShownForPlayer[playerid] [_:barid])
		return;

	TeamBarShownForPlayer[playerid] [_:barid] = false;
	TextDrawHideForPlayer(playerid, TeamBarsData[barofplayerid][TeamBarText]);
	HidePlayerProgressBar(playerid, barid);
}

// Hides team bars for a specific player
HideTeamBarsForPlayer(playerid)
{
	if (!ShowHPBars)
		return 0;

	new PlayerBar: barid;
	foreach (new i : PlayerWithTeamBar) // Loops through all players who have a team bar created for them
	{
		if (!IsTeamTheSame(Player[playerid][Team], TeamBarsData[i][TeamBar_Team]))
			continue;

		barid = TeamBarsData[i][TeamBar];
		if (!TeamBarShownForPlayer[playerid] [_:barid])
			continue;

		TeamBarShownForPlayer[playerid] [_:barid] = false;
		TextDrawHideForPlayer(playerid, TeamBarsData[i][TeamBarText]);
		HidePlayerProgressBar(playerid, barid);
	}
	return 1;
}

// Hide all team bars for a player with a force (doesn't matter if they're shown or not)
HideAllTeamBarsForPlayer(playerid)
{
	if (!ShowHPBars)
		return 0;

	new PlayerBar: barid;
	foreach (new i : PlayerWithTeamBar) // Loops through all players who have a team bar created for them
	{
		barid									  = TeamBarsData[i][TeamBar];
		TeamBarShownForPlayer[playerid] [_:barid] = false;
		TextDrawHideForPlayer(playerid, TeamBarsData[i][TeamBarText]);
		HidePlayerProgressBar(playerid, barid);
	}
	return 1;
}

// This deletes a player team bar
// To be used when round ends or when a player is removed
DeletePlayerTeamBar(playerid)
{
	if (!ShowHPBars)
		return 0;

	if (!Iter_Contains(PlayerWithTeamBar, playerid))
		return 0;

	// Delete the textdraws
	DestroyPlayerProgressBar(playerid, TeamBarsData[playerid][TeamBar]);
	TextDrawDestroy(TeamBarsData[playerid][TeamBarText]);
	TeamBarsData[playerid][TeamBar_Y]	 = Float: INVALID_PLAYER_ID;
	TeamBarsData[playerid][TeamBar_Team] = REFEREE;
	Iter_Remove(PlayerWithTeamBar, playerid); // Remove this player from the array that holds IDs of players who got team bars
	return 1;
}

// This deletes all team bars
// Usually used when a round is ended
DeleteAllTeamBars()
{
	if (!ShowHPBars)
		return 0;

	foreach (new i : PlayerWithTeamBar) // Loops through all players who have a team bar created for them
	{
		// Delete the textdraws
		DestroyPlayerProgressBar(i, TeamBarsData[i][TeamBar]);
		TextDrawDestroy(TeamBarsData[i][TeamBarText]);
		TeamBarsData[i][TeamBar_Y]	  = Float: INVALID_PLAYER_ID;
		TeamBarsData[i][TeamBar_Team] = REFEREE;
	}
	Iter_Clear(PlayerWithTeamBar);
	return 1;
}

// This updates a player team bar with the correct damage done and HP
// To be used when player does damage or their health is changed
UpdatePlayerTeamBar(playerid)
{
	if (!ShowHPBars)
		return 0;

	if (!Iter_Contains(PlayerWithTeamBar, playerid)) // Check if this player has a team bar or not
		return 0;

	if (Player[playerid][Playing])
	{
		new colourToSet;
		new formatToUse[] = "~w~~h~%s ~r~~h~~h~~h~%d / %d";
		if (Player[playerid][Team] == ATTACKER)
			colourToSet = Player[playerid][AskingForHelp] ? TEAMBARS_ATTACKER_HELP_COLOR : TEAMBARS_ATTACKER_COLOR;
		else if (Player[playerid][Team] == DEFENDER)
		{
			colourToSet		= Player[playerid][AskingForHelp] ? TEAMBARS_DEFENDER_HELP_COLOR : TEAMBARS_DEFENDER_COLOR;
			formatToUse[10] = 'b';
		}
		SetPlayerProgressBarValue(playerid, TeamBarsData[playerid][TeamBar], GetHP(playerid) + GetAP(playerid));
		SetPlayerProgressBarColour(playerid, TeamBarsData[playerid][TeamBar], colourToSet);
		TextDrawSetString(
			TeamBarsData[playerid][TeamBarText],
			va_return(formatToUse, Player[playerid][NameWithoutTag], GetHP(playerid) + GetAP(playerid), floatround(Player[playerid][RoundDamage])));
	}
	else
	{
		new formatToUse[] = "~w~~h~%s ~r~~h~~h~~h~Dead / %d";
		if (Player[playerid][Team] == DEFENDER)
			formatToUse[10] = 'b';
		SetPlayerProgressBarValue(playerid, TeamBarsData[playerid][TeamBar], 0.0);
		TextDrawSetString(TeamBarsData[playerid][TeamBarText], va_return(formatToUse, Player[playerid][NameWithoutTag], floatround(Player[playerid][RoundDamage])));
	}

	foreach (new i : Player)
	{
		if (IsTeamTheSame(Player[playerid][Team], Player[i][Team]))
		{
			if (!Player[i][Playing] && !Player[i][Spectating])
				TeamBarHideForPlayer(i, playerid);
		}
		else if (TeamBarShownForPlayer[i] [_:TeamBarsData[playerid][TeamBar]])
			TeamBarHideForPlayer(i, playerid);
	}
	return 1;
}
