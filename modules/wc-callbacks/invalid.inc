#if defined _attdef_OnInvalidWeaponDamage
	#endinput
#endif
#define _attdef_OnInvalidWeaponDamage

public OnInvalidWeaponDamage(playerid, damagedid, Float: amount, weaponid, bodypart, error, bool: given)
{
	switch (error)
	{
		case WC_NO_DAMAGED, WC_NO_ISSUER: return 1;
		case WC_SNIPER_BUG:
		{
			if (IsSkinshot || given)
				return 1;
			// sniper bug, we could punish sniper bug in more interesting ways
			if (weaponid == WEAPON_SNIPER)
			{
				new Float: totalhp = GetPlayerHealth(damagedid) + GetPlayerArmour(damagedid);
				new Float: weapondmg = GetWeaponDamage(weaponid);
				DamagePlayer(damagedid, GetWeaponDamage(weaponid), .weaponid = weaponid, .bodypart = bodypart);
				MessageBox(damagedid, MSGBOX_TYPE_MIDDLE, "~r~~h~Sniper Bug", "You are sniper bugged and a relog is needed", 3000);
				if (totalhp > weapondmg)
				{
					SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "has been forced to relog for being sniper bugged.", Player[damagedid][Name]);
					SetTimerEx("OnPlayerKicked", GetPlayerPing(damagedid) + 10, false, "i", damagedid);
					return 1;
				}
				SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "is sniper bugged.", Player[damagedid][Name]);
				return 1;
			}
		}
	}
	return 1;
}
