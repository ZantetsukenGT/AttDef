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
			// given == true,  dmg was reported in OnPlayerGiveDamage by playerid == issuerid
			// given == false, dmg was reported in OnPlayerTakeDamage by damagedid == playerid
			if (given)
				return 1;

			// sniper bug, we could punish sniper bug in more interesting ways
			MessageBox(damagedid, MSGBOX_TYPE_MIDDLE, "~r~~h~Sniper Bug", "You likely to have Sniper Bug and a relog is needed", 3000);
			va_SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "has been forced to relog for having weapon bugs. {FFFFFF}(Most likely Sniper Bug)", Player[damagedid][Name]);
			SetPreciseTimer("OnPlayerKicked", 500, false, "i", damagedid);
		}
	}
	return 1;
}
