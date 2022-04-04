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
	return 1;
}
