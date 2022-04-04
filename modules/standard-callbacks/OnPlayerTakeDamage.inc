#if defined _attdef_OnPTakeDamage
	#endinput
#endif
#define _attdef_OnPTakeDamage

public OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
{
	if (lagcompmode == 0)
		HandlePlayerDamage(playerid, issuerid, amount, weaponid, bodypart);
	return 1;
}
