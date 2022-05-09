#if defined _attdef_OnInvalidWeaponDamage
	#endinput
#endif
#define _attdef_OnInvalidWeaponDamage

public OnInvalidWeaponDamage(playerid, damagedid, Float: amount, weaponid, bodypart, error, bool: given)
{
	switch (error)
	{
		case WC_NO_ERROR: return 1;
		case WC_NO_ISSUER:
		{
			// given == true means that playerid reported the damage in OnPlayerGiveDamage
			// given == false means that damagedid reported the damage in OnPlayerTakeDamage
			if (given)
				return 1;
			//sniper bug check, we could punish sniper bug in more interesting ways
			if (weaponid == WEAPON_CARPARK)
				return 1;
			MessageBox(playerid, MSGBOX_TYPE_MIDDLE, "~r~~h~Sniper Bug", "You likely to have Sniper Bug and a relog is needed", 3000);
			va_SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "has been forced to relog for having weapon bugs. {FFFFFF}(Most likely Sniper Bug)", Player[playerid][Name]);
			SetPreciseTimer("OnPlayerKicked", 500, false, "i", playerid);
		}
	}
	return 1;
}
