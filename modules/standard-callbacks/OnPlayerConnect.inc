#if defined _attdef_OnPConnect
	#endinput
#endif
#define _attdef_OnPConnect

hook GOOD_OnPlayerConnect(playerid)
{
	// Cleans chat
	for (new i = 0; i < 99; i++) SendClientMessage(playerid, -1, " ");

	SendClientMessage(playerid, COL_PRIM_HEX, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	SendClientMessage(playerid, COL_PRIM_HEX, "{FFFFFF}Welcome to " COL_PRIM "%s {FFFFFF}Server!", ServerName);
	SendClientMessage(playerid, COL_PRIM_HEX, "PRO TIPS:");
	SendClientMessage(playerid, COL_PRIM_HEX, "{FFD700}You can use F2 to access PWAC settings!");
	SendClientMessage(playerid, COL_PRIM_HEX, "{FFFFFF}/changelog");
	SendClientMessage(playerid, COL_PRIM_HEX, "{FFFFFF}Past, present and future.");
	SendClientMessage(playerid, COL_PRIM_HEX, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	return 1;
}

hook OnPlayerConnect(playerid)
{
	EnablePlayerCameraTarget(playerid, 1);

	// Initialize the new player
	InitPlayer(playerid);
	CheckPlayerAKA(playerid);
	return 1;
}
