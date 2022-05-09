#if defined _attdef_OnRejectedHit
	#endinput
#endif
#define _attdef_OnRejectedHit

public OnRejectedHit(playerid, hit[E_REJECTED_HIT])
{
	new reason = hit[e_Reason];
	new i1 = hit[e_Info1];
	new i2 = hit[e_Info2];
	new i3 = hit[e_Info3];

	new weapon = hit[e_Weapon];
	new weapon_name[32];
	WC_GetWeaponName(weapon, weapon_name);

	new output[256];
	format(output, sizeof(output), COL_ERROR "(%s -> %s): " COL_USAGE "%s", weapon_name, hit[e_Name], g_HitRejectReasons[reason]);
	va_SendClientMessage(playerid, COL_ERROR_HEX, output, i1, i2, i3);
	return 1;
}
