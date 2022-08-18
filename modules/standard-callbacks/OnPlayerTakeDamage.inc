#if defined _attdef_OnPTakeDamage
	#endinput
#endif
#define _attdef_OnPTakeDamage

public OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
{
	if (!IsSkinshot)
		HandlePlayerDamage(playerid, issuerid, amount, weaponid, bodypart);
	return 1;
}
