#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_this_core
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/' folder."
#endif

#if defined _attdef_impl_this_core
	#endinput
#endif
#define _attdef_impl_this_core

/*
	Gamemode core
*/

#include <YSI_Coding\y_hooks>

hook OnPlayerDisconnect(playerid, reason)
{
	// If it's the last player in the server (server is empty now!)
	if (Iter_Count(Player) == 1)
	{
		// Server unlock if the server is not in the middle of something
		if (ServerLocked && !PermLocked && !RoundPaused)
		{
			// Unlock the server
			SendRconCommand("password 0");
			ServerLocked = false;
		}
		// Optimize and clean database
		OptimizeDatabase();
	}
	return 1;
}

InitScriptCoreSettings()
{
	Command_SetDeniedReturn(true);		   //To avoid default unknown command message
	SetAltCommands();
	LoadDatabase();
	UsePlayerPedAnims();				   // Player movement
	AllowInteriorWeapons(1);			   // Allow weapons in interiors
	DisableInteriorEnterExits();		   // Disables entering interiors (e.g. Burger shots)
	EnableStuntBonusForAll(0);			   // If you stunt you won't get any points (Value = 0)
	SetNameTagDrawDistance(DRAW_DISTANCE); // Distance to see other players name and Hp
	EnableVehicleFriendlyFire();		   // Enable friendly fire for team vehicles
	SetGravity(0.008);					   // Gravity
	SetWorldTime(MainTime);				   // Sets server time
	SetWeather(MainWeather);			   // Sets server weather
	return 1;
}

#if defined _YSF_included
CheckServerHostname() { GetConsoleVarAsString("hostname", hostname); }
#else
CheckServerHostname() { GetConsoleVarAsString("name", hostname); }
#endif

InitScriptSecondarySettings()
{
	// Init some global variables
	GameType			 = BASE;
	ServerLastPlayed	 = -1;
	ServerLastPlayedType = -1;
	Current				 = -1;
	LastMatchEndTime	 = 0;

	// Settings
	FixGamemodeText(); // Text that appears on 'Mode' column when you click on a server in samp.exe
	SendRconCommand("mapname Lobby");
#if !defined opws_fix_included_
	#if defined _YSF_included
		IsSkinshot = GetConsoleVarAsInt("lagcompmode") == 1;
	#else
		IsSkinshot = GetConsoleVarAsInt("game.lag_compensation_mode") == 1;
	#endif
#endif
	CheckServerHostname();
	SetTeamDefaultColors();
	SetTeamDefaultNames();
	InitSpectate();
	InitGunmenu();
	InitVoting();

	CreateObject(3095, 268.74, 1884.21, 16.07, 0.00, 0.00, 0.00); // block area 51

	// Match recording (rounds)
	MatchRoundsStarted = 0;
	for (new i = 0; i < 101; i++)
	{
		MatchRoundsRecord[i][round__ID]		   = -1;
		MatchRoundsRecord[i][round__type]	   = -1;
		MatchRoundsRecord[i][round__completed] = false;
	}
	format(MAIN_TEXT_COLOUR, sizeof MAIN_TEXT_COLOUR, "~w~");
	MAIN_BACKGROUND_COLOUR = 0x00000044;

	teamskinlist		   = LoadModelSelectionMenu("skins.txt");
	playerskinlist		   = LoadModelSelectionMenu("skins.txt");
	return 1;
}

AddToServersDatabase()
{
#if defined HTTP_DEST_SERVERLIST
	switch (YHash(hostname, false))
	{
		case _I<Bulletproof Home Test Server>: return;
		case _I<Bulletproof Home Test Server [ACv2 ENABLED]>: return;
	}

	new ServerIP[30];
#if defined _YSF_included
	GetConsoleVarAsString("bind", ServerIP, sizeof(ServerIP));

	new port = GetConsoleVarAsInt("port");
#else
	GetConsoleVarAsString("network.bind", ServerIP, sizeof(ServerIP));

	new port = GetConsoleVarAsInt("network.port");
#endif

	if (!strlen(ServerIP))
		ServerIP = "noip";

	new post[256];
	format(post, sizeof(post), "IP=%s&Port=%d&HostName=%s", ServerIP, port, hostname);
	HTTP(0, HTTP_POST, HTTP_DEST_SERVERLIST, post, "");
#endif
}

FixGamemodeText()
{
	SetGameModeText(va_return("%s v%s", GM_NAME, GM_VERSION));
}
