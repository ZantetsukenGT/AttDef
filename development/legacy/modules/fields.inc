#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_fields
	#endinput
#endif
#define _attdef_mod_fields

/*
	Fields related: bases, arenas... etc
*/

#define MAX_BASES		   300
#define MAX_ARENAS		   300
#define MAX_DMS			   100

#define MAX_MAP_FIELD_NAME 64

// - Base Variables -
new Iterator: CurrentBases<MAX_BASES>;
new BInterior[MAX_BASES];
new Float: BAttackerSpawn[MAX_BASES][3];
new Float: BDefenderSpawn[MAX_BASES][3];
new Float: BCPSpawn[MAX_BASES][3];
new BName[MAX_BASES][MAX_MAP_FIELD_NAME];
new CurrentBaseSet[32] = "NewBulletproofBases";

// - Arena Variables -
new Iterator: CurrentArenas<MAX_ARENAS>;
new AInterior[MAX_ARENAS];
new Float: AAttackerSpawn[MAX_ARENAS][3];
new Float: ADefenderSpawn[MAX_ARENAS][3];
new Float: ACPSpawn[MAX_ARENAS][3];
new AName[MAX_ARENAS][MAX_MAP_FIELD_NAME];
new Float: AMax[MAX_ARENAS][2];
new Float: AMin[MAX_ARENAS][2];
new CurrentArenaSet[32] = "Arenas";

// - DM Variables -
new Iterator: CurrentDMs<MAX_DMS>;
new Float: DMSpawn[MAX_DMS][4];
new DMInterior[MAX_DMS];
new DMWeapons[MAX_DMS][3];
