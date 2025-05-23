#if defined _attdef_cmd_speedcap
	#endinput
#endif
#define _attdef_cmd_speedcap

#if !defined pwac_included
	#endinput
#endif

#include <YSI_Coding\y_hooks>

static Float: s_speedcap = 100.0;

// will only work if the player has PWAC installed 
YCMD: speedcap(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "change the global speedcap value.");

	new Float: speedcap;
	if (sscanf(params, "F(100.0)", speedcap))
		return SendUsageMessage(playerid, "/speedcap [sprint speedcap value]");

	return PerformCommandSpeedcap(playerid, speedcap);
}

PerformCommandSpeedcap(playerid, Float: speedcap)
{
	speedcap = speedcap < 1.0 ? 1.0 : speedcap;
	speedcap = speedcap > 100.0 ? 100.0 : speedcap;
	foreach (new i : Player)
	{
		SetPlayerSprintCap(i, speedcap);
	}
	SendClientMessageToAll(-1, "%s " COL_PRIM "has set the sprint speedcap to {FFFFFF}%f", Player[playerid][Name], speedcap);
	s_speedcap = speedcap;
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	SetPlayerSprintCap(playerid, s_speedcap);
	return 1;
}
