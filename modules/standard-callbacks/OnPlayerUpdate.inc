#if defined _attdef_OnPUpdate
	#endinput
#endif
#define _attdef_OnPUpdate

public OnPlayerUpdate(playerid)
{
	if (!IsPlayerConnected(playerid))
		return 0;
	// Player is sending updates, hence they're not paused
	Player[playerid][PauseCount] = 0;

	// Free camera check
	if (noclipdata[playerid][cameramode] == CAMERA_MODE_FLY)
	{
		ProcessFreeCameraMovement(playerid);
		return 0;
	}

	new animLib[32], animName[32];
	new pAnimIndex = GetPlayerAnimationIndex(playerid);
	if (pAnimIndex)
        GetAnimationName(pAnimIndex, animLib, sizeof animLib, animName, sizeof animName);
	new pAnimNameHash = YHash(animName);
	//new pAnimLibHash = YHash(animLib);
	//remove parachute functions
	if (GetPlayerWeapon(playerid) == WEAPON_PARACHUTE)
	{
		new Weapons[10][2];
		for (new i = 0; i < 10; i++) { GetPlayerWeaponData(playerid, i, Weapons[i][0], Weapons[i][1]); }
		switch (pAnimNameHash)
		{
			case _H<RUN_PLAYER>:
			{
				ResetPlayerWeapons(playerid);
				for (new i = 0; i < 10; i++) { GivePlayerWeapon(playerid, Weapons[i][0], Weapons[i][1]); }
			}
			case _H<PARA_OPEN>:
			{
				ResetPlayerWeapons(playerid);
				for (new i = 0; i < 10; i++) { GivePlayerWeapon(playerid, Weapons[i][0], Weapons[i][1]); }
				SetPlayerVelocity(playerid, 0, 0, 0);
				ClearAnimations(playerid);
			}
		}
	}
	return 1;
}
