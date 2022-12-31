#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_weaponbinds
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/' folder."
#endif

#if defined _attdef_impl_weaponbinds
	#endinput
#endif
#define _attdef_impl_weaponbinds

/*
	Weapon key binds system
*/

InitPlayerWeaponBind(playerid)
{
	// Load default weapon key binds
	WeaponBindData[playerid][BindKeyWeapon][0] = WEAPON_SNIPER;
	WeaponBindData[playerid][BindKeyWeapon][1] = WEAPON_DEAGLE;
	WeaponBindData[playerid][BindKeyWeapon][2] = WEAPON_SHOTGUN;
	WeaponBindData[playerid][BindKeyWeapon][3] = WEAPON_SHOTGSPA;
	WeaponBindData[playerid][BindKeyWeapon][4] = WEAPON_M4;
}

// Creates a player-textdraw that shows weapon key binds
CreatePlayerWeaponBindTextDraw(playerid)
{
	WeaponBindData[playerid][WeaponBindTextDraw] = CreatePlayerTextDraw(playerid, 491.000000, 25.000000, "_");
	PlayerTextDrawAlignment(playerid, WeaponBindData[playerid][WeaponBindTextDraw], 3);
	PlayerTextDrawBackgroundColor(playerid, WeaponBindData[playerid][WeaponBindTextDraw], MAIN_BACKGROUND_COLOUR);
	PlayerTextDrawFont(playerid, WeaponBindData[playerid][WeaponBindTextDraw], 2);
	PlayerTextDrawLetterSize(playerid, WeaponBindData[playerid][WeaponBindTextDraw], 0.169999, 0.900000);
	PlayerTextDrawColor(playerid, WeaponBindData[playerid][WeaponBindTextDraw], -1);
	PlayerTextDrawSetOutline(playerid, WeaponBindData[playerid][WeaponBindTextDraw], 0);
	PlayerTextDrawSetProportional(playerid, WeaponBindData[playerid][WeaponBindTextDraw], 1);
	PlayerTextDrawSetShadow(playerid, WeaponBindData[playerid][WeaponBindTextDraw], 0);
	WeaponBindData[playerid][WeaponBindTDShown] = false;
}

// Updates the player-textdraw with the correct key bind values
UpdatePlayerWeaponBindTextDraw(playerid)
{
	new str[WEAPON_BIND_TEXTDRAW_STRING_SIZE];
	//format(str, sizeof str, "[Gun binds]");
	for (new i = 0; i < MAX_WEAPON_BINDS; i++)
	{
		format(str, sizeof str, "%s~n~%s+%s = %s", str, WEAPON_BIND_PRIMARY_KEY_TEXT, WeaponBindKeyText[i], ReturnWeaponName(WeaponBindData[playerid][BindKeyWeapon][i]));
	}
	PlayerTextDrawSetString(playerid, WeaponBindData[playerid][WeaponBindTextDraw], str);
}

// Hides the weapon binds textdraw
forward HidePlayerWeaponBindTextDraw(playerid);
public HidePlayerWeaponBindTextDraw(playerid)
{
	PlayerTextDrawHide(playerid, WeaponBindData[playerid][WeaponBindTextDraw]);
	WeaponBindData[playerid][WeaponBindTDShown] = false;
	return 1;
}

// Shows the weapon binds textdraw
ShowPlayerWeaponBindTextDraw(playerid, time)
{
	if (WeaponBindData[playerid][WeaponBindTDShown])
		return;

	UpdatePlayerWeaponBindTextDraw(playerid);
	PlayerTextDrawShow(playerid, WeaponBindData[playerid][WeaponBindTextDraw]);
	WeaponBindData[playerid][WeaponBindTDShown] = true;
	SetTimerEx("HidePlayerWeaponBindTextDraw", time, false, "i", playerid);
}

// Shows the weapon key bind coder dialog
ShowPlayerWeaponBindDialog(playerid)
{
	new str[WEAPON_BIND_DIALOG_STRING_SIZE];
	format(str, sizeof str, "Key combination\tWeapon\n");
	format(str, sizeof str, Player[playerid][WeaponBinding] ? "%s{CC0000}Disable\n" : "%s{33CC00}Enable\n", str);
	for (new i = 0; i < MAX_WEAPON_BINDS; i++)
	{
		format(str, sizeof str, "%s%s+%s\t%s\n", str, WEAPON_BIND_PRIMARY_KEY_TEXT_ALT, WeaponBindKeyText_ALT[i], ReturnWeaponName(WeaponBindData[playerid][BindKeyWeapon][i]));
	}
	return ShowPlayerDialog(playerid, DIALOG_WEAPONBIND_MAIN, DIALOG_STYLE_TABLIST_HEADERS, "Weapon Binds", str, "Modify", "Cancel");
}

// Checks keys to see if a bind key combination exists in it
// Usually placed under OnPlayerKeyStateChange
CheckKeysForWeaponBind(playerid, newkeys, oldkeys)
{
	if (!Player[playerid][WeaponBinding])
		return false;

	if (GetPlayerVehicleID(playerid))
		return false;

	if (!HOLDING(WEAPON_BIND_PRIMARY_KEY_VALUE))
		return false;

	for (new i = 0; i != MAX_WEAPON_BINDS; i++)
	{
		if (PRESSED(WeaponBindKeyValue[i]))
		{
			SetPlayerArmedWeapon(playerid, WeaponBindData[playerid][BindKeyWeapon][i]);
			return true;
		}
	}
	return false;
}
