#if defined _attdef_OnInvalidWeaponDamage
	#endinput
#endif
#define _attdef_OnInvalidWeaponDamage

public OnInvalidWeaponDamage(playerid, damagedid, Float: amount, weaponid, bodypart, error, bool: given)
{
	return 1;
}
