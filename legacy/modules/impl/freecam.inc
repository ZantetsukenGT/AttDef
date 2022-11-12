#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_freecam
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/' folder."
#endif

#if defined _attdef_impl_freecam
	#endinput
#endif
#define _attdef_impl_freecam

/*
	Free camera script
*/

SetFreeCamPos(playerid, Float: toX, Float: toY, Float: toZ) { SetPlayerObjectPos(playerid, noclipdata[playerid][flyobject], toX - 5.0, toY - 5.0, toZ + 7.0); }

PlayerFlyMode(playerid, bool: frozencamera)
{
	// If the player is spectating, cancel spectation mode
	if (Player[playerid][Spectating])
		StopSpectate(playerid);
	else
	{
		// If the player was being spectated by someone else, stop spectation mode for them
		if (Player[playerid][BeingSpeced])
		{
			foreach (new i : AllSpectators)
			{
				if (Player[i][IsSpectatingID] == playerid)
				{
					Iter_Remove(AllSpectators, i);
					StopSpectate(i, false);
				}
			}
		}
	}

	// Get the player's position
	new Float: X,
		Float: Y,
		Float: Z;
	GetPlayerPos(playerid, X, Y, Z);

	// Create an invisible object for the players camera to be attached to
	noclipdata[playerid][flyobject]	 = CreatePlayerObject(playerid, 19300, X, Y, Z, 0.0, 0.0, 0.0);

	// Set variables correct values
	noclipdata[playerid][FlyMode]	 = true;
	Player[playerid][Spectating]	 = true;
	noclipdata[playerid][cameramode] = CAMERA_MODE_FLY;
	noclipdata[playerid][camfrozen]	 = frozencamera;

	// Set player's virtual world to main world
	SetPlayerVirtualWorld(playerid, 0);

	// Clear player's animations
	ClearAnimations(playerid);

	// Place the player in spectating mode so objects will be streamed based on camera location
	TogglePlayerSpectating(playerid, true);

	// Attach the players camera to the previously created (invisible) object
	AttachCameraToPlayerObject(playerid, noclipdata[playerid][flyobject]);
}

CancelFlyMode(playerid)
{
	if (!noclipdata[playerid][FlyMode])
		return 0;

	noclipdata[playerid][FlyMode] = false;

	CancelEdit(playerid);
	TogglePlayerSpectating(playerid, false);

	DestroyPlayerObject(playerid, noclipdata[playerid][flyobject]);
	noclipdata[playerid][cameramode] = CAMERA_MODE_NONE;
	return 1;
}

GetNextCameraPosition(move_mode, const Float: CP[3], const Float: FV[3], &Float: vX, &Float: vY, &Float: vZ)
{
	// Calculate the cameras next position based on their current position and the direction their camera is facing
	new Float: OFFSET_X = FV[0] * 6000.0,
		Float: OFFSET_Y = FV[1] * 6000.0,
		Float: OFFSET_Z = FV[2] * 6000.0;
	switch (move_mode)
	{
		case MOVE_FORWARD:
		{
			vX = CP[0] + OFFSET_X;
			vY = CP[1] + OFFSET_Y;
			vZ = CP[2] + OFFSET_Z;
		}
		case MOVE_BACK:
		{
			vX = CP[0] - OFFSET_X;
			vY = CP[1] - OFFSET_Y;
			vZ = CP[2] - OFFSET_Z;
		}
		case MOVE_LEFT:
		{
			vX = CP[0] - OFFSET_Y;
			vY = CP[1] + OFFSET_X;
			vZ = CP[2];
		}
		case MOVE_RIGHT:
		{
			vX = CP[0] + OFFSET_Y;
			vY = CP[1] - OFFSET_X;
			vZ = CP[2];
		}
		case MOVE_BACK_LEFT:
		{
			vX = CP[0] + (-OFFSET_X - OFFSET_Y);
			vY = CP[1] + (-OFFSET_Y + OFFSET_X);
			vZ = CP[2] - OFFSET_Z;
		}
		case MOVE_BACK_RIGHT:
		{
			vX = CP[0] + (-OFFSET_X + OFFSET_Y);
			vY = CP[1] + (-OFFSET_Y - OFFSET_X);
			vZ = CP[2] - OFFSET_Z;
		}
		case MOVE_FORWARD_LEFT:
		{
			vX = CP[0] + (OFFSET_X - OFFSET_Y);
			vY = CP[1] + (OFFSET_Y + OFFSET_X);
			vZ = CP[2] + OFFSET_Z;
		}
		case MOVE_FORWARD_RIGHT:
		{
			vX = CP[0] + (OFFSET_X + OFFSET_Y);
			vY = CP[1] + (OFFSET_Y - OFFSET_X);
			vZ = CP[2] + OFFSET_Z;
		}
	}
}

MoveCamera(playerid)
{
	new Float: FV[3],
		Float: CP[3];
	GetPlayerCameraPos(playerid, CP[0], CP[1], CP[2]);		   // 	Cameras position in space
	GetPlayerCameraFrontVector(playerid, FV[0], FV[1], FV[2]); //  Where the camera is looking at

	// Increases the acceleration multiplier the longer the key is held
	if (noclipdata[playerid][accelmul] <= 1)
		noclipdata[playerid][accelmul] += ACCEL_RATE;

	// Determine the speed to move the camera based on the acceleration multiplier
	new Float: speed = noclipdata[playerid][accelmul] * MOVE_SPEED;

	// Calculate the cameras next position based on their current position and the direction their camera is facing
	new Float: X,
		Float: Y,
		Float: Z;
	GetNextCameraPosition(noclipdata[playerid][noclipcammode], CP, FV, X, Y, Z);
	MovePlayerObject(playerid, noclipdata[playerid][flyobject], X, Y, Z, speed);

	// Store the last time the camera was moved as now
	noclipdata[playerid][lastmove] = GetTickCount();
	return 1;
}

GetMoveDirectionFromKeys(ud, lr)
{
	switch (lr)
	{
		case KEY_LEFT:
		{
			switch (ud)
			{
				case KEY_UP: return MOVE_FORWARD_LEFT;
				case KEY_DOWN: return MOVE_BACK_LEFT;
				default: return MOVE_LEFT;
			}
		}
		case KEY_RIGHT:
		{
			switch (ud)
			{
				case KEY_UP: return MOVE_FORWARD_RIGHT;
				case KEY_DOWN: return MOVE_BACK_RIGHT;
				default: return MOVE_RIGHT;
			}
		}
		default:
		{
			switch (ud)
			{
				case KEY_UP: return MOVE_FORWARD;
				case KEY_DOWN: return MOVE_BACK;
			}
		}
	}
	return NOT_MOVING;
}

ProcessFreeCameraMovement(playerid)
{
	if (noclipdata[playerid][noclipcammode] && GetTickCount() - noclipdata[playerid][lastmove] > 100)
	{
		// If the last move was > 100ms ago, process moving the object the players camera is attached to
		MoveCamera(playerid);
	}
	if (!noclipdata[playerid][camfrozen])
	{
		new keys, ud, lr;
		GetPlayerKeys(playerid, keys, ud, lr);
		// Is the players current key state different than their last keystate?
		if (noclipdata[playerid][udold] != ud || noclipdata[playerid][lrold] != lr)
		{
			if ((noclipdata[playerid][udold] != 0 || noclipdata[playerid][lrold] != 0) && ud == 0 && lr == 0)
			{ // All keys have been released, stop the object the camera is attached to and reset the acceleration multiplier
				StopPlayerObject(playerid, noclipdata[playerid][flyobject]);
				noclipdata[playerid][noclipcammode] = 0;
				noclipdata[playerid][accelmul]		= 0.0;
			}
			else
			{ // Indicates a new key has been pressed

				// Get the direction the player wants to move as indicated by the keys
				noclipdata[playerid][noclipcammode] = GetMoveDirectionFromKeys(ud, lr);

				// Process moving the object the players camera is attached to
				MoveCamera(playerid);
			}
		}
		noclipdata[playerid][udold] = ud;
		noclipdata[playerid][lrold] = lr; // Store current keys pressed for comparison next update
	}
}
