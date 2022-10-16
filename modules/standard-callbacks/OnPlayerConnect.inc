#if defined _attdef_OnPConnect
	#endinput
#endif
#define _attdef_OnPConnect

public OnPlayerConnect(playerid)
{
	// Cleans chat
	for (new i = 0; i < 20; i++) SendClientMessage(playerid, -1, " ");

	SendClientMessage(playerid, COL_PRIM_HEX, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	va_SendClientMessage(playerid, COL_PRIM_HEX, "{FFFFFF}Welcome to " COL_PRIM "%s {FFFFFF}Server!", ServerName);
	SendClientMessage(playerid, COL_PRIM_HEX, "PRO TIPS:");
	SendClientMessage(playerid, COL_PRIM_HEX, "{FFD700}Sniper bug fix available! {FFFFFF}shorturl.at/bgpH1");
	SendClientMessage(playerid, COL_PRIM_HEX, "{FFD700}Silent ASI Loader required: {FFFFFF}shorturl.at/szCR0");
	SendClientMessage(playerid, COL_PRIM_HEX, "{FFFFFF}/changelog");
	SendClientMessage(playerid, COL_PRIM_HEX, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	EnablePlayerCameraTarget(playerid, 1);

	// Check if players count exceeded the limit
	if (Iter_Count(Player) >= MAX_PLAYERS)
	{
		va_SendClientMessageToAll(-1, COL_PRIM "ID %d could't connect to the server properly. Maximum players limit exceeded!", playerid);
		va_SendClientMessageToAll(-1, "MAX PLAYERS LIMIT: %d", MAX_PLAYERS);
		SetTimerEx("OnPlayerKicked", 500, false, "i", playerid);
		return 0;
	}

	// Initialize the new player
	InitPlayer(playerid);
	CheckPlayerAKA(playerid);
	return 1;
}

