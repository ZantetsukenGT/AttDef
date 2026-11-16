#if defined _attdef_cmd_settings
	#endinput
#endif
#define _attdef_cmd_settings

YCMD: settings(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display server settings");

	new string[144];
	SendClientMessage(playerid, -1, COL_PRIM "Server settings:");
	format(string, sizeof(string), "{FFFFFF}CP Time = " COL_PRIM "%d {FFFFFF}seconds | Round Time = " COL_PRIM "%d {FFFFFF}minutes", ConfigCPTime, ConfigRoundTime);

	SendClientMessage(playerid, -1, string);
	format(
		string, sizeof(string), "{FFFFFF}Attacker Skin = " COL_PRIM "%d {FFFFFF}| Defender Skin = " COL_PRIM "%d {FFFFFF}| Referee Skin = " COL_PRIM "%d", Skin[ATTACKER],
		Skin[DEFENDER], Skin[REFEREE]);

	SendClientMessage(playerid, -1, string);
	format(string, sizeof(string), "{FFFFFF}Min FPS = " COL_PRIM "%d {FFFFFF}| Max Ping = " COL_PRIM "%d {FFFFFF}| Max Packetloss = " COL_PRIM "%.2f", Min_FPS, Max_Ping,
		   Float: Max_Packetloss);

	SendClientMessage(playerid, -1, string);
	format(
		string, sizeof(string), "{FFFFFF}Auto-Balance = %s {FFFFFF}| Anti-Spam = %s", AutoBal ? "{66FF66}Enabled" : "{FF6666}Disabled",
		AntiSpam ? "{66FF66}Enabled" : "{FF6666}Disabled");

	SendClientMessage(playerid, -1, string);
	format(
		string, sizeof(string), "{FFFFFF}Auto-Pause = %s {FFFFFF}| Guns in Lobby = %s", AutoPause ? "{66FF66}Enabled" : "{FF6666}Disabled",
		LobbyGuns ? "{66FF66}Enabled" : "{FF6666}Disabled");

	SendClientMessage(playerid, -1, string);
	format(
		string, sizeof(string), "{FFFFFF}Antimacros = %s {FFFFFF}| Death camera = %s", AntiMacros ? "{66FF66}Enabled" : "{FF6666}Disabled",
		DeathCamera ? "{66FF66}Enabled" : "{FF6666}Disabled");

	SendClientMessage(playerid, -1, string);
	format(
		string, sizeof(string), "{FFFFFF}Melee weapons menu = %s {FFFFFF}| Dead bodies = %s", MeleeAllowed ? "{66FF66}Enabled" : "{FF6666}Disabled",
		DeadBodies ? "{66FF66}Enabled" : "{FF6666}Disabled");

	SendClientMessage(playerid, -1, string);
	format(string, sizeof(string), "{FFFFFF}CP in arenas = %s {FFFFFF}", CPInArena ? "{66FF66}Enabled" : "{FF6666}Disabled");

	return SendClientMessage(playerid, -1, string);
}
