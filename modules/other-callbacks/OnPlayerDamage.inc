#if defined _attdef_OnPDamage
	#endinput
#endif
#define _attdef_OnPDamage

static bool: ShouldDamagePlayer(playerid, issuerid, Float: amount, weaponid)
{
	if (Player[playerid][IsAFK]) // Players who are in AFK mode should not be damaged
		return false;

	if (Player[playerid][Playing] && Player[playerid][OnGunmenu]) // Players who are picking weapons from gun-menu should not be damaged
		return false;

	switch (weaponid)
	{
		case WEAPON_VEHICLE, WEAPON_HELIBLADES: return false;
		case WEAPON_COLLISION:
		{
			if (amount <= 10 || GetPlayerArmour(playerid) > 0 && SyncAbuse)
				return false;
		}
	}
	// Some checks need to be done if there's a damager and he is playing
	if (issuerid != INVALID_PLAYER_ID && Player[issuerid][Playing])
	{
		// Check whether they are in the same team or not
		if (Player[issuerid][Team] == Player[playerid][Team])
		{
			HandleFriendlyVisualDamage(issuerid, playerid);

			PlayerPlaySound(issuerid, 1135, 0.0, 0.0, 0.0);
			PlayerPlaySound(playerid, 1135, 0.0, 0.0, 0.0);
			return false;
		}
		// If the damaged player is out of the round
		if (!Player[playerid][Playing])
			return false;
		// If it's a referee trying to do damage
		if (Player[issuerid][Team] == REFEREE)
			return false;
	}
	return true;
}

public OnPlayerDamage(&playerid, &Float: amount, &issuerid, &weapon, &bodypart)
{
	// Fall protection, gunmenu protection..etc
	if (!ShouldDamagePlayer(playerid, issuerid, amount, weapon))
		return 0;

	// Damage adjustment
	switch (weapon)
	{
		case WEAPON_EXPLOSION, WEAPON_GRENADE, WEAPON_ROCKETLAUNCHER, WEAPON_HEATSEEKER:
		{
			if (amount > 60.0)
				amount = GRENADE_HIGH_DAMAGE;
			else if (amount >= 30.0)
				amount = GRENADE_MEDIUM_DAMAGE;
			else
				amount = GRENADE_LOW_DAMAGE;
		}
		case WEAPON_COLLISION: //Cancel collision damage for now, just to it test out
		{
			//return 0;
		}
	}

	return 1;
}
