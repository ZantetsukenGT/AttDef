#if defined _attdef_OnARTextUpdate
	#endinput
#endif
#define _attdef_OnARTextUpdate

public OnArmourBarTextUpdate(playerid, PlayerText: text)
{
	new Float: armour = GetPlayerArmour(playerid);
	va_PlayerTextDrawSetString(playerid, text, "%.1f", armour);
}
