#if defined _attdef_OnHPTextUpdate
	#endinput
#endif
#define _attdef_OnHPTextUpdate

public OnHealthBarTextUpdate(playerid, PlayerText: text)
{
	new Float: armour = GetPlayerArmour(playerid);
	if (armour == 0.0)
	{
		new Float: health = GetPlayerHealth(playerid);
		va_PlayerTextDrawSetString(playerid, text, "%.1f", health);
	}
	else
		PlayerTextDrawSetString(playerid, text, "PROTECTED");
}
