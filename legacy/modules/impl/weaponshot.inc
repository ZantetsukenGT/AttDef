#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_weaponshot
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/' folder."
#endif

#if defined _attdef_impl_weaponshot
	#endinput
#endif
#define _attdef_impl_weaponshot

SetHP(playerid, Float: amount)
{
	new bool: wasPlaying = Player[playerid][Playing];
	SetPlayerHealth(playerid, amount);
	UpdatePlayerHPAPVariables(playerid, wasPlaying);
}

SetAP(playerid, Float: amount)
{
	SetPlayerArmour(playerid, amount);
	UpdatePlayerHPAPVariables(playerid, Player[playerid][Playing]);
}

UpdatePlayerHPAPVariables(playerid, bool: WasPlaying)
{
	new Float: health = GetPlayerArmour(playerid) + GetPlayerHealth(playerid);

	if (WasPlaying)
	{
		SetPlayerScore(playerid, health < 1.000 ? floatround(health, floatround_ceil) : floatround(health));
	}
}

GetHP(playerid)
{
	new Float: health = GetPlayerHealth(playerid);
	return floatround(health, health < 1.000 ? floatround_ceil : floatround_round);
}

GetAP(playerid)
{
	new Float: armour = GetPlayerArmour(playerid);
	return floatround(armour, armour < 1.000 ? floatround_ceil : floatround_round);
}

forward HideFriendlyVisualDmg(playerid);
public HideFriendlyVisualDmg(playerid)
{
	FriendlyDamageTimer[playerid] = 0;
	PlayerTextDrawSetString(playerid, FriendlyDamage[playerid][0], "_");
	PlayerTextDrawSetString(playerid, FriendlyDamage[playerid][1], "_");
	return 1;
}

HandleFriendlyVisualDamage(hitterid, hittedid, bool: rejected = false)
{
	new str[44];
	if (rejected)
		format(str, sizeof str, "~y~~h~%s (rejected-fire)", Player[hittedid][NameWithoutTag]);
	else
		format(str, sizeof str, "~y~~h~%s (team-fire)", Player[hittedid][NameWithoutTag]);

	PlayerTextDrawSetString(hitterid, FriendlyDamage[hitterid][0], str);

	if (FriendlyDamageTimer[hitterid])
		KillTimer(FriendlyDamageTimer[hitterid]);
	FriendlyDamageTimer[hitterid] = SetTimerEx("HideFriendlyVisualDmg", HIDE_DAMAGE_TEXTDRAW_AFTER, false, "i", hitterid);

	// Loop through the array that contains hitter's spectators
	foreach (new i : PlayerSpectators[hitterid])
	{
		PlayerTextDrawSetString(i, FriendlyDamage[i][0], str);

		if (FriendlyDamageTimer[i])
			KillTimer(FriendlyDamageTimer[i]);
		FriendlyDamageTimer[i] = SetTimerEx("HideFriendlyVisualDmg", HIDE_DAMAGE_TEXTDRAW_AFTER, false, "i", i);
	}

	if (rejected)
		format(str, sizeof str, "~y~~h~%s (rejected-fire)", Player[hitterid][NameWithoutTag]);
	else
		format(str, sizeof str, "~y~~h~%s (team-fire)", Player[hitterid][NameWithoutTag]);

	PlayerTextDrawSetString(hittedid, FriendlyDamage[hittedid][1], str);

	if (FriendlyDamageTimer[hittedid])
		KillTimer(FriendlyDamageTimer[hittedid]);
	FriendlyDamageTimer[hittedid] = SetTimerEx("HideFriendlyVisualDmg", HIDE_DAMAGE_TEXTDRAW_AFTER, false, "i", hittedid);

	// Loop through the array that contains hitter's spectators
	foreach (new i : PlayerSpectators[hittedid])
	{
		PlayerTextDrawSetString(i, FriendlyDamage[i][1], str);

		if (FriendlyDamageTimer[i])
			KillTimer(FriendlyDamageTimer[i]);
		FriendlyDamageTimer[i] = SetTimerEx("HideFriendlyVisualDmg", HIDE_DAMAGE_TEXTDRAW_AFTER, false, "i", i);
	}
}

InitPlayerVisualDamage(playerid)
{
	if (FriendlyDamageTimer[playerid])
	{
		KillTimer(FriendlyDamageTimer[playerid]);
		FriendlyDamageTimer[playerid] = 0;
	}
	Iter_Clear(PlayerDMGBubble<playerid>);
}

// Creates and updates damage label above player's head.
// Note: SetPlayerChatBubble doesn't work as it's line length is too small with color formatting.
SetPlayerDamageBubble(playerid, issuerid, Float: amount, weaponid)
{
	DamageBubbleLastTick[playerid][issuerid] = GetTickCount();
	DamageBubbleWeapon[playerid][issuerid] = weaponid;
	if (Iter_Contains(PlayerDMGBubble<playerid>, issuerid))
		amount += DamageBubbleDMG[playerid][issuerid];
	DamageBubbleDMG[playerid][issuerid] = amount;
	Iter_Add(PlayerDMGBubble<playerid>, issuerid);

	UpdateDamageBubbles(playerid, .force = true);
}

// Updates damage label time.
UpdateDamageBubbles(playerid, bool: force = false)
{
	new currentTick = GetTickCount();

	new bool: needsUpdate = force;
	foreach (new i : PlayerDMGBubble<playerid>)
	{
		if (currentTick - DamageBubbleLastTick[playerid][i] > HIDE_DAMAGE_TEXTDRAW_AFTER)
		{
			needsUpdate = true;
			Iter_Remove(PlayerDMGBubble<playerid>, i);
		}
	}
	if (needsUpdate)
	{
		new str[DAMAGE_BUBBLE_STRING_LENGTH];
		foreach (new i : PlayerDMGBubble<playerid>)
		{
			new pColor[10];
			format(pColor, sizeof(pColor), "%s", TextColor[Player[i][Team]]);
			format(
				str, sizeof(str), "%s%s%s {FFFFFF}/ -%.0f (%s%s{FFFFFF})\n", str, pColor, Player[i][NameWithoutTag], DamageBubbleDMG[playerid][i], pColor,
				ReturnWeaponName(DamageBubbleWeapon[playerid][i]));
		}

		// Movees 3d text down according to lines count
		foreach (new i : PlayerDMGBubble<playerid>)
		{
			format(str, sizeof(str), "\n%s", str);
		}

		// Update Damage Bubble
		Update3DTextLabelText(Player[playerid][DamageLabel], -1, str);
	}
}
