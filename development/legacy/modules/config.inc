#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_config
	#endinput
#endif
#define _attdef_mod_config

/*
	Gamemode configuration
*/

#include "modules/this_core.inc"

new MainWeather;		 // Server start up weather
new MainTime;			 // Server start up time
new ConfigCPTime;		 // CP time
new ConfigRoundTime;	 // Round time
new Float: MainSpawn[4]; // Main spawn position and facing angle
new MainInterior;		 // Main spawn interior
new WeatherLimit		   = 50;
new TimeLimit			   = 50;
new GAME_SPEED			   = 1000;

new Float: Max_Packetloss;
new Max_Ping;
new Min_FPS;

new bool: DeadBodies				  = false;
new bool: DeathCamera				  = true;
new bool: ShowHPBars				  = true;
new bool: AntiSpam					  = true;
new bool: LobbyGuns					  = true;
new bool: ServerLocked				  = false;
new bool: PermLocked				  = false;
new bool: CPInArena					  = false;
new bool: AntiMacros				  = true;
new bool: MeleeAllowed				  = false;
new bool: AutoRoundStarter			  = false;
new bool: RandomDeathMessages		  = false;
new bool: SightseeingInClassSelection = false;
new bool: VehicleHealthTextdraw		  = false;
new bool: SyncAbuse					  = true;
new bool: ScreenFlashing			  = true;
new bool: DefendersWithVehicles		  = false;

new RoundHP							  = 100;
new RoundAR							  = 100;

new Skin[MAX_TEAMS];
