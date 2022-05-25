#if defined _attdef_OnPUpdate
	#endinput
#endif
#define _attdef_OnPUpdate

static Weapons[MAX_PLAYERS][10][2];

public OnPlayerUpdate(playerid)
{
	// Player is sending updates, hence they're not paused
	Player[playerid][PauseCount] = 0;

	// Free camera check
	if (noclipdata[playerid][cameramode] == CAMERA_MODE_FLY)
	{
		ProcessFreeCameraMovement(playerid);
		return 0;
	}

	//remove parachute functions
	if (GetPlayerWeapon(playerid) == WEAPON_PARACHUTE)
	{
		switch (GetPlayerAnimationIndex(playerid))
		{
			case 971: // PARA_open
			{
				for (new i = 0; i < 10; i++) { GetPlayerWeaponData(playerid, i, Weapons[playerid][i][0], Weapons[playerid][i][1]); }
				ResetPlayerWeapons(playerid);
				for (new i = 0; i < 10; i++) { GivePlayerWeapon(playerid, Weapons[playerid][i][0], Weapons[playerid][i][1]); }
				SetPlayerVelocity(playerid, 0, 0, 0);
				ClearAnimations(playerid);
			} 
			case 1231: // run_player
			{
				for (new i = 0; i < 10; i++) { GetPlayerWeaponData(playerid, i, Weapons[playerid][i][0], Weapons[playerid][i][1]); }
				ResetPlayerWeapons(playerid);
				for (new i = 0; i < 10; i++) { GivePlayerWeapon(playerid, Weapons[playerid][i][0], Weapons[playerid][i][1]); }
			}
		}
	}
	return 1;
}
