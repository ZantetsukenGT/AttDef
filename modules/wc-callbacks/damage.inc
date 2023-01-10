#if defined _attdef_OnPDamage
	#endinput
#endif
#define _attdef_OnPDamage

static bool: ShouldDamagePlayer(&playerid, &issuerid, &Float: amount, &weaponid)
{
	if (Player[playerid][IsAFK]) // Players who are in AFK mode should not be damaged
		return false;
	if (Player[playerid][Playing] && Player[playerid][OnGunmenu]) // Players who are picking weapons from gun-menu should not be damaged
		return false;
	if (GetPlayerState(playerid) == PLAYER_STATE_SPECTATING) // don't damage spectators
		return false;

	switch (weaponid)
	{
		case WEAPON_VEHICLE, WEAPON_HELIBLADES: return false;
		case WEAPON_COLLISION:
		{
			new anim = GetPlayerAnimationIndex(playerid);
			// apply death when the player splats with a parachute
			if (958 <= anim <= 979)
				return true;
			if (amount <= 10.0 || GetAP(playerid))
				return false;
		}
	}
	// Some checks need to be done if there's a damager
	if (issuerid != INVALID_PLAYER_ID)
	{
		// Reject damage if one is playing and the other is not
		if (Player[playerid][Playing] != Player[issuerid][Playing])
		{
			HandleFriendlyVisualDamage(issuerid, playerid, .rejected = true);

			PlayerPlaySound(issuerid, 1135, 0.0, 0.0, 0.0);
			PlayerPlaySound(playerid, 1135, 0.0, 0.0, 0.0);
			return false;
		}

		// If they are not playing, just allow the dmg
		if (!Player[playerid][Playing])
			return true;

		// Check whether they are in the same team or not
		if (Player[issuerid][Team] == Player[playerid][Team])
		{
			HandleFriendlyVisualDamage(issuerid, playerid);

			PlayerPlaySound(issuerid, 1135, 0.0, 0.0, 0.0);
			PlayerPlaySound(playerid, 1135, 0.0, 0.0, 0.0);
			return false;
		}
		// If it's a referee trying to do damage
		if (Player[issuerid][Team] == REFEREE)
		{
			HandleFriendlyVisualDamage(issuerid, playerid, .rejected = true);

			PlayerPlaySound(issuerid, 1135, 0.0, 0.0, 0.0);
			PlayerPlaySound(playerid, 1135, 0.0, 0.0, 0.0);
			return false;
		}
	}
	return true;
}

public OnPlayerDamage(&playerid, &Float: amount, &issuerid, &weapon, &bodypart)
{
	if (amount <= 0.0005) // any damage dealing 0.0 must be applied or bugs will occur
		return 1;
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
	}
	return 1;
}
