#if defined _attdef_OnPUpdate
	#endinput
#endif
#define _attdef_OnPUpdate

static const PARACHUTE_SLOT = 11;

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
	new weaponid, ammo;
	GetPlayerWeaponData(playerid, PARACHUTE_SLOT, weaponid, ammo);
	if (ammo && weaponid == WEAPON_PARACHUTE)
	{
		switch (GetPlayerAnimationIndex(playerid))
		{
			case 971: // PARA_open
			{
				RemovePlayerWeapon(playerid, weaponid);
				SetPlayerVelocity(playerid, 0, 0, 0);
				ClearAnimations(playerid);
			}
			case 1231: // run_player
			{
				RemovePlayerWeapon(playerid, weaponid);
			}
		}
	}
	return 1;
}
