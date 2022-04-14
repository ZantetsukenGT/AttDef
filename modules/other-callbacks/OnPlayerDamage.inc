#if defined _attdef_OnPDamage
	#endinput
#endif
#define _attdef_OnPDamage

public OnPlayerDamage(&playerid, &Float: amount, &issuerid, &weapon, &bodypart)
{
	return 1;
}
