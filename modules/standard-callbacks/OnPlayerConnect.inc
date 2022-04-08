#if defined _attdef_OnPConnect
	#endinput
#endif
#define _attdef_OnPConnect

public OnPlayerConnect(playerid)
{
	// Cleans chat
	for (new i = 0; i < 20; i++) SendClientMessage(playerid, -1, " ");

	SendClientMessage(playerid, COL_PRIM_HEX, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	SendClientMessage(playerid, COL_PRIM_HEX, va_return("{FFFFFF}Welcome to " COL_PRIM "%s {FFFFFF}Server!", ServerName));
	SendClientMessage(playerid, COL_PRIM_HEX, "PRO TIPS:");
	SendClientMessage(playerid, COL_PRIM_HEX, "{FFD700}Sniper bug fix available! {FFFFFF}shorturl.at/bgpH1");
	SendClientMessage(playerid, COL_PRIM_HEX, "{FFD700}Silent ASI Loader required: {FFFFFF}shorturl.at/szCR0");
	SendClientMessage(playerid, COL_PRIM_HEX, "{FFFFFF}/changelog");
	SendClientMessage(playerid, COL_PRIM_HEX, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	EnablePlayerCameraTarget(playerid, 1);

	// Check if players count exceeded the limit
	if (Iter_Count(Player) >= MAX_PLAYERS)
	{
		SendClientMessageToAll(-1, va_return(COL_PRIM "ID %d could't connect to the server properly. Maximum players limit exceeded!", playerid));
		SendClientMessageToAll(-1, va_return("MAX PLAYERS LIMIT: %d", MAX_PLAYERS));
		SetPreciseTimer("OnPlayerKicked", 500, false, "i", playerid);
		return 0;
	}

	// Initialize the new player
	InitPlayer(playerid);
	CheckPlayerAKA(playerid);
	return 1;
}

public OnGeoDataReady(playerid)
{
	new CountryName[MAX_GEOIP_COUNTRY_NAME];
	new IPBlock;
	GetPlayerCountryName(playerid, CountryName);
	GetPlayerIPBlock(playerid, IPBlock);
	switch (IPBlock)
	{
		case 0: va_SendClientMessageToAll(-1, "{FFFFFF}%s {CCCCCC}(ID: %d) has connected [{FFFFFF}%s{CCCCCC}]", Player[playerid][Name], playerid, CountryName);
		case 1:
		{
			va_SendClientMessageToAll(-1, "{FFFFFF}%s {CCCCCC}(ID: %d) has connected [{FFFFFF}%s {FF6666}Proxy{CCCCCC}]", Player[playerid][Name], playerid, CountryName);
			SetPreciseTimer("_BanPlayerDelayed", GetPlayerPing(playerid), false, "i", playerid);
		}
		case 2: va_SendClientMessageToAll(-1, "{FFFFFF}%s {CCCCCC}(ID: %d) has connected [{FFFFFF}%s {AAAA00}Proxy?{CCCCCC}]", Player[playerid][Name], playerid, CountryName);
	}
	return 1;
}
