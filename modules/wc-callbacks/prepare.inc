#if defined _attdef_OnPPrepareDeath
	#endinput
#endif
#define _attdef_OnPPrepareDeath

public OnPlayerPrepareDeath(playerid, animlib[32], animname[32], &anim_lock, &respawn_time)
{
	respawn_time = 500;
	return 1;
}
