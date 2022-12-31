#if defined _attdef_OnARTextUpdate
	#endinput
#endif
#define _attdef_OnARTextUpdate

public OnArmourBarTextUpdate(playerid, health, armour, text[WC_MAX_WEAPON_NAME])
{
#pragma unused playerid, health
	if (!armour)
		return 0;
	format(text, sizeof(text), "%d", armour);
	return 1;
}
