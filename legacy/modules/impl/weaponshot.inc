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
	if (!WC_IsPlayerSpawned(playerid) || IsPlayerDying(playerid))
		return;
	new bool: wasPlaying = Player[playerid][Playing];
	SetPlayerHealth(playerid, amount);
	UpdatePlayerHPAPVariables(playerid, wasPlaying);
}

SetAP(playerid, Float: amount)
{
	if (!WC_IsPlayerSpawned(playerid) || IsPlayerDying(playerid))
		return;
	SetPlayerArmour(playerid, amount);
	UpdatePlayerHPAPVariables(playerid, Player[playerid][Playing]);
}

UpdatePlayerHPAPVariables(playerid, bool: WasPlaying)
{
	new Float: armour = GetPlayerArmour(playerid);
	new Float: health = GetPlayerHealth(playerid);

	if (WasPlaying)
	{
		if (Player[playerid][Team] == ATTACKER)
			SetPlayerScore(playerid, floatround(health + armour));
		else
			SetPlayerScore(playerid, -floatround(health + armour));
	}
}

InitPlayerVisualDamage(playerid)
{
	FriendlyDamageTimer[playerid] = 0;
}

forward HideFriendlyVisualDmg(playerid);
public HideFriendlyVisualDmg(playerid)
{
	FriendlyDamageTimer[playerid] = 0;
	PlayerTextDrawSetString(playerid, FriendlyDamage[playerid][0], "_");
	PlayerTextDrawSetString(playerid, FriendlyDamage[playerid][1], "_");
	return 1;
}

HandleFriendlyVisualDamage(hitterid, hittedid)
{
	new str[44];
	format(str, sizeof(str), "~y~~h~%s (team-fire)", Player[hittedid][NameWithoutTag]);

	PlayerTextDrawSetString(hitterid, FriendlyDamage[hitterid][0], str);

	if (FriendlyDamageTimer[hitterid])
		DeletePreciseTimer(FriendlyDamageTimer[hitterid]);
	FriendlyDamageTimer[hitterid] = SetPreciseTimer("HideFriendlyVisualDmg", HIDE_DAMAGE_TEXTDRAW_AFTER, false, "i", hitterid);

	// Loop through the array that contains hitter's spectators
	foreach (new i : PlayerSpectators[hitterid])
	{
		PlayerTextDrawSetString(i, FriendlyDamage[i][0], str);

		if (FriendlyDamageTimer[i])
			DeletePreciseTimer(FriendlyDamageTimer[i]);
		FriendlyDamageTimer[i] = SetPreciseTimer("HideFriendlyVisualDmg", HIDE_DAMAGE_TEXTDRAW_AFTER, false, "i", i);
	}

	format(str, sizeof(str), "~y~~h~%s (team-fire)", Player[hitterid][NameWithoutTag]);

	PlayerTextDrawSetString(hittedid, FriendlyDamage[hittedid][1], str);

	if (FriendlyDamageTimer[hittedid])
		DeletePreciseTimer(FriendlyDamageTimer[hittedid]);
	FriendlyDamageTimer[hittedid] = SetPreciseTimer("HideFriendlyVisualDmg", HIDE_DAMAGE_TEXTDRAW_AFTER, false, "i", hittedid);

	// Loop through the array that contains hitter's spectators
	foreach (new i : PlayerSpectators[hittedid])
	{
		PlayerTextDrawSetString(i, FriendlyDamage[i][1], str);

		if (FriendlyDamageTimer[i])
			DeletePreciseTimer(FriendlyDamageTimer[i]);
		FriendlyDamageTimer[i] = SetPreciseTimer("HideFriendlyVisualDmg", HIDE_DAMAGE_TEXTDRAW_AFTER, false, "i", i);
	}
}
