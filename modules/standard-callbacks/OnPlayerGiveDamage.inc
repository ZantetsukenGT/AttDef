#if defined _attdef_OnPGiveDamage
	#endinput
#endif
#define _attdef_OnPGiveDamage

public OnPlayerGiveDamage(playerid, damagedid, Float: amount, weaponid, bodypart)
{
	if (IsSkinshot)
		HandlePlayerDamage(damagedid, playerid, amount, weaponid, bodypart);
	return 1;
}

HandlePlayerDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
{
	// Fall protection, gunmenu protection..etc
	if (!IsLegalHit(playerid, issuerid, amount, weaponid))
		return 1;

	// Detect explosion damage, cancel it and set grenade damage
	if (weaponid == 51)
	{
		if (issuerid == INVALID_PLAYER_ID)
		{
			/* Protection against explosion */
			SetFakeHealthArmour(playerid);
			return 1;
		}
		else
		{
			weaponid = WEAPON_GRENADE;
		}
	}

	// Handling Grenades
	if (weaponid == WEAPON_GRENADE)
	{
		if (amount > 60.0)
			amount = GRENADE_HIGH_DAMAGE;
		else if (amount >= 30.0)
			amount = GRENADE_MEDIUM_DAMAGE;
		else if (amount < 30.0)
			amount = GRENADE_LOW_DAMAGE;
	}
	// Deagle nerf
	if (weaponid == WEAPON_DEAGLE && ShouldNerfDeagle)
	{
		amount = DeagleNerfValue;
	}

	// Detect headshots
	if (bodypart == 9)
		HandleHeadshot(playerid, issuerid, weaponid);

	// Show target player info for the shooter (HP, PL, Ping and many other things)
	ShowTargetInfo(issuerid, playerid);

	// <start> Health and armour handling
	if (weaponid == -1)
		weaponid = Player[playerid][HitWith];

	Player[playerid][HitBy]	  = issuerid; // This is used in custom OnPlayerDeath to get the last player who caused damage on 'playerid'
	Player[playerid][HitWith] = weaponid; // This is used in custom OnPlayerDeath to get the last weapon a player got hit with before death

	new rounded_amount		  = GetActualDamage(amount, playerid); // Fix damage if it's unreal (in other words, if damage is greater than player's health)

	// If it's a collision (fell or something)
	if (weaponid == 54)
	{
		// We deal with health only leaving armour as it is.
		SetHP(playerid, Player[playerid][pHealth] - rounded_amount);
	}
	else if (Player[playerid][pArmour] > 0)
	{
		// Still got armour and it's not a collision damager

		new diff = (Player[playerid][pArmour] - rounded_amount);
		if (diff < 0)
		{
			SetAP(playerid, 0);
			SetHP(playerid, Player[playerid][pHealth] + diff);
		}
		else if (diff == 0)
			SetAP(playerid, 0);
		else if (ShouldNerfDeagle)
			SetAP(playerid, diff);
		else
			UpdatePlayerArmourVariables(playerid, diff);
	}
	else // It's not a collision and the player got no armour
		SetHP(playerid, Player[playerid][pHealth] - rounded_amount);
	// <end> Health and armour handling

	if (issuerid != INVALID_PLAYER_ID) // If the damager is a HUMAN
	{
		PlayerPlaySound(issuerid, Player[issuerid][HitSound], 0.0, 0.0, 0.0);
		PlayerPlaySound(playerid, Player[playerid][GetHitSound], 0.0, 0.0, 0.0);

		HandleVisualDamage(playerid, issuerid, float(rounded_amount), weaponid);

		if (Player[issuerid][Playing] == true && Player[playerid][Playing] == true)
		{
			Player[issuerid][shotsHit]++;
			Player[issuerid][RoundDamage] += rounded_amount;
			Player[issuerid][TotalDamage] += rounded_amount;
			UpdateRoundKillDmgTDmg(issuerid);

		}
	}
	else // If damage is caused by something else (not a player)
	{
		if (GetPlayerState(playerid) != PLAYER_STATE_WASTED && Player[playerid][Spawned])
		{
			PlayerPlaySound(playerid, Player[playerid][GetHitSound], 0, 0, 0);
			ShowCollisionDamageTextDraw(playerid, float(rounded_amount), weaponid);
		}
	}
	// If there's a round running
	if (Current != -1)
	{
		// Update team HP bars
		UpdatePlayerTeamBar(playerid);
		UpdatePlayerTeamBar(issuerid);

		// Update teammates information textdraw
		UpdateTeamCornerInfo();

		// Show team lost hp textdraws
		if (Player[playerid][Playing] == true)
		{
			switch (Player[playerid][Team])
			{
				case ATTACKER:
				{
					new str[16];
					format(str, sizeof(str), "~r~~h~%s", Player[playerid][NameWithoutTag]);
					TextDrawSetString(AttHpLose, str);

					TempDamage[ATTACKER] += rounded_amount;
					format(str, sizeof(str), "~r~-%d", TempDamage[ATTACKER]);
					TextDrawSetString(TeamHpLose[0], str);

					ModernTextDrawFlash(ATTACKER);

					if (AttHpTimer)
						KillTimer(AttHpTimer);
					AttHpTimer = SetTimer("HideHpTextForAtt", 2500, false);
				}
				case DEFENDER:
				{
					new str[16];
					format(str, sizeof(str), "~b~~h~%s", Player[playerid][NameWithoutTag]);
					TextDrawSetString(DefHpLose, str);

					TempDamage[DEFENDER] += rounded_amount;
					format(str, sizeof(str), "~b~-%d", TempDamage[DEFENDER]);
					TextDrawSetString(TeamHpLose[1], str);

					ModernTextDrawFlash(DEFENDER);

					if (DefHpTimer)
						KillTimer(DefHpTimer);
					DefHpTimer = SetTimer("HideHpTextForDef", 2500, false);
				}
			}
		}
	}
	return 1;
}
