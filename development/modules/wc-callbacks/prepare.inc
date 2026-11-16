#if defined _attdef_OnPPrepareDeath
	#endinput
#endif
#define _attdef_OnPPrepareDeath

public OnPlayerPrepareDeath(playerid, animlib[32], animname[32], &anim_lock, &respawn_time)
{
	respawn_time = GetPlayerPing(playerid);
	return 1;
}
