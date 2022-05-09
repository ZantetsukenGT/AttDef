#if defined _attdef_OnPDamageDone
	#endinput
#endif
#define _attdef_OnPDamageDone

public OnPlayerDamageDone(playerid, Float: amount, issuerid, weapon, bodypart)
{
	if (issuerid != INVALID_PLAYER_ID) // If the damager is a HUMAN
	{
		// Detect headshots
		if (bodypart == 9)
			HandleHeadshot(playerid, issuerid, weapon);

		// Show target player info for the shooter (HP, PL, Ping and many other things)
		ShowTargetInfo(issuerid, playerid);

		if (Player[issuerid][Playing] && Player[playerid][Playing])
		{
			Player[issuerid][shotsHit]++;
			Player[issuerid][RoundDamage] += amount;
			Player[issuerid][TotalDamage] += amount;
			UpdateRoundKillDmgTDmg(issuerid);
		}
	}
	UpdatePlayerHPAPVariables(playerid, Player[playerid][Playing]);

	// If there's a round running
	if (Current != -1)
	{
		// Update team HP bars
		UpdatePlayerTeamBar(playerid);
		UpdatePlayerTeamBar(issuerid);

		// Update teammates information textdraw
		UpdateTeamCornerInfo();
		
		// Update damaged team information textdraws
		UpdateTeamHP(Player[playerid][Team]);

		// Show team lost hp textdraws
		if (Player[playerid][Playing])
		{
			switch (Player[playerid][Team])
			{
				case ATTACKER:
				{
					TextDrawSetString(AttHpLose, va_return("~r~~h~%s", Player[playerid][NameWithoutTag]));

					TempDamage[ATTACKER] += amount;
					TextDrawSetString(TeamHpLose[0], va_return("~r~-%d", TempDamage[ATTACKER]));

					ModernTextDrawFlash(ATTACKER);

					if (AttHpTimer)
						DeletePreciseTimer(AttHpTimer);
					AttHpTimer = SetPreciseTimer("HideHpTextForAtt", 2500, false);
				}
				case DEFENDER:
				{
					TextDrawSetString(DefHpLose, va_return("~b~~h~%s", Player[playerid][NameWithoutTag]));

					TempDamage[DEFENDER] += amount;
					TextDrawSetString(TeamHpLose[1], va_return("~b~-%d", TempDamage[DEFENDER]));

					ModernTextDrawFlash(DEFENDER);

					if (DefHpTimer)
						DeletePreciseTimer(DefHpTimer);
					DefHpTimer = SetPreciseTimer("HideHpTextForDef", 2500, false);
				}
			}
		}
	}
	return 1;
}

/*
This is used to make sure a head-shot is legit and successful
then announce it. This function has return values as well.
Returns 0 on failure (illegal/rejected headshots) and returns 1 on success.
*/
static HandleHeadshot(playerid, issuerid, weaponid)
{
	switch (weaponid)
	{
		case WEAPON_SNIPER, WEAPON_RIFLE, WEAPON_DEAGLE:
		{
			MessageBox(issuerid, MSGBOX_TYPE_TOP, "~g~~h~Headshot", "_", 2000);
			if (Player[playerid][Playing] && Player[issuerid][Playing]
				&& !IsTeamTheSame(Player[playerid][Team], Player[issuerid][Team]))
			{
				new weapon_name[32];
				WC_GetWeaponName(weaponid, weapon_name);
				va_SendClientMessageToAll(-1, "{FFFFFF}%s " COL_PRIM "has landed a hit on {FFFFFF}%s's " COL_PRIM "head " COL_PRIM "({FFFFFF}%s" COL_PRIM ")",
					Player[issuerid][Name], Player[playerid][Name], weapon_name);
			}
		}
	}
	return 1;
}
