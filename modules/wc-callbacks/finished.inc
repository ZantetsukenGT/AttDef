#if defined _attdef_OnPDeathFinished
	#endinput
#endif
#define _attdef_OnPDeathFinished

public OnPlayerDeathFinished(playerid)
{
	ColorFix(playerid);
	return 1;
}
