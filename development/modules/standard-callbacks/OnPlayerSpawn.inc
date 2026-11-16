#if defined _attdef_OnPSpawn
	#endinput
#endif
#define _attdef_OnPSpawn

public OnPlayerSpawn(playerid)
{
	PlayerPlaySound(playerid, 1188, 0.0, 0.0, 0.0);
	if (Player[playerid][IgnoreSpawn])
	{
		// This spawn call should be ignored (used for many things .. e.g the SyncPlayer function)
		Player[playerid][IgnoreSpawn] = false;
		return 1;
	}

	// If they're selecting from gunmenu
	if (Player[playerid][OnGunmenu])
	{
		// Hide it!!!
		HidePlayerGunmenu(playerid);
	}

	// If this player is just spawning regularly
	if (!Player[playerid][Playing] && !Player[playerid][InDM] && !Player[playerid][InDuel])
	{
		// Adjust player HP
		SetHP(playerid, 100);
		SetAP(playerid, 100);

		// Unarm players from any weapons
		ResetPlayerWeapons(playerid);
		// 'playerid' is unique which means playerids can never match, hence we use that to initialize player's team
		// and workaround SAMP's built-in anti team-shooting (i.e players in the same team cannot harm each other)
		SetPlayerTeam(playerid, NO_TEAM);
		SetPlayerScore(playerid, 0);

		// Initialize player spawn camera and position
		SetPlayerInterior(playerid, MainInterior);
		SetPlayerVirtualWorld(playerid, 0);
		SetCameraBehindPlayer(playerid);

		ColorFix(playerid); // Fixes player color based on their team.
		RadarFix();
	}

	// Fixes the x Vs y textdraws with current team player count
	FixVsTextDraw();

	// If there's no round running, hide the round stats textdraws
	if (Current == -1)
		HideRoundStats(playerid);
	else if (ElapsedTime <= 20 && !Player[playerid][Playing] && !WarMode && (Player[playerid][Team] == ATTACKER || Player[playerid][Team] == DEFENDER))
		SendClientMessage(playerid, -1, COL_PRIM "You may want to use {FFFFFF}/addme " COL_PRIM "to add yourself to the round.");
	return 1;
}
