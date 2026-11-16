#if defined _attdef_cmd_weapondmg
	#endinput
#endif
#define _attdef_cmd_weapondmg

#include <YSI_Coding\y_hooks>

static Float: s_DefaultDamages[sizeof(s_WeaponDamage)];

hook OnScriptInit()
{
	for (new i = 0; i < sizeof(s_WeaponDamage); ++i) { s_DefaultDamages[i] = GetWeaponDamage(i); }
	return 1;
}

YCMD: weapondmg(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "toggle any weapon's damage between default damage and custom damage.");
	new weapon_name_id[WC_MAX_WEAPON_NAME], Float: damageValue;
	if (sscanf(params, "s[*]F(-1.000)", sizeof(weapon_name_id), weapon_name_id, damageValue))
		return UsageWeaponDMG(playerid);
	return DoWeaponDMG(playerid, weapon_name_id, damageValue);
}

static UsageWeaponDMG(playerid) { return SendUsageMessage(playerid, "/weapondmg [Weapon Name/ID] [New DMG (optional, default DMG if not provided)]"); }

DoWeaponDMG(playerid, const weapon_name_id[WC_MAX_WEAPON_NAME], Float: damageValue)
{
	if (Current != -1)
		return SendErrorMessage(playerid, "Can't use this while a round is in progress.");
	new weaponid = IsNumeric(weapon_name_id) ? strval(weapon_name_id) : GetWeaponID(weapon_name_id);
	if (!IsBulletWeapon(weaponid) && !IsMeleeWeapon(weaponid) && !IsHighRateWeapon(weaponid))
		return SendErrorMessage(playerid, "That weapon doesn't exist or its damage is not allowed to be changed.");
	if (damageValue == -1.000)
	{
		SetWeaponDamage(weaponid, s_DamageType[weaponid], s_DefaultDamages[weaponid]);
		return SendClientMessageToAll(
			-1, "%s " COL_PRIM "has set {FFFFFF}%s's damage " COL_PRIM "to its {FFFFFF}default" COL_PRIM ".", Player[playerid][Name], ReturnWeaponName(weaponid));
	}
	if (damageValue < 0.3)
		return SendErrorMessage(playerid, "The new weapon's damage is too low, minimum is 0.3.");
	if (damageValue > 75.0)
		return SendErrorMessage(playerid, "The new weapon's damage is too high, maximum is 75.0.");
	SetWeaponDamage(weaponid, s_DamageType[weaponid], damageValue);
	return SendClientMessageToAll(-1, "%s " COL_PRIM "has set {FFFFFF}%s's damage " COL_PRIM "to " COL_USAGE "%0.3f{FFFFFF}", Player[playerid][Name], ReturnWeaponName(weaponid), damageValue);
}
