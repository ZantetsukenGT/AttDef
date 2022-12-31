#if defined _attdef_OnHPTextUpdate
	#endinput
#endif
#define _attdef_OnHPTextUpdate

public OnHealthBarTextUpdate(playerid, health, armour, text[WC_MAX_WEAPON_NAME])
{
#pragma unused playerid, armour
	format(text, sizeof(text), "%d", health);
	return 1;
}
