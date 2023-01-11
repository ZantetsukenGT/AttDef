#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_player
	#endinput
#endif
#define _attdef_mod_player

/*
	Player related
*/

#include "modules/gunmenu.inc"
#include "modules/this_core.inc"

#define SAVE_SLOTS MAX_PLAYERS

// - Player Variables -
enum PlayerVariables {
	//added by zyph
	Float: DmPosX,
	Float: DmPosY,
	Float: DmPosZ,
	Float: DmAngle,
	//end added by zyph
	Name[MAX_PLAYER_NAME],
	NameWithoutTag[MAX_PLAYER_NAME],
	bool: Logged,
	bool: IgnoreSpawn,
	bool: InDM,
	bool: InDuel,
	bool: Playing,
	bool: WasInCP,
	bool: Spectating,
	bool: BeingSpeced,
	bool: WasInBase,
	bool: TextDrawOnScreen,
	bool: Spawned,
	bool: IsAFK,
	bool: AskingForHelp,
	bool: Mute,
	bool: ToAddInRound,
	bool: blockedall,
	bool: FakePacketRenovation,
	bool: TempNetcheck,
	bool: WeaponBinding,
	bool: HasDeathQuote,
	bool: PlayerMarkers,
	bool: HadParachuteBeforeFreeze,
	GunmenuModdingType,
	GunmenuModdingIndex,
	bool: NetCheck,
	bool: FPSCheck,
	bool: PLCheck,
	bool: PingCheck,
	NetCheckTimeoutTimestamp,
	challengerid,
	duelweap1,
	duelweap2,
	DuelRequestedArena,
	Float: Duel_X,
	Float: Duel_Y,
	Duel_Interior,
	Duel_Size,
	Duel_GangZone,
	DuelsWon,
	DuelsLost,
	LastMsgr,
	blockedid,
	FightStyle,

	IsSpectatingID,
	Level,
	ChatChannel,
	Weather,
	Time,
	Team,
	WasInTeam,
	TeamBeforeDuel,
	DLlast,
	FPS,
	DMReadd,
	RoundKills,
	RoundDeaths,
	Float: RoundDamage,
	TotalKills,
	TotalDeaths,
	Float: TotalDamage,
	WeaponPicked,
	OutOfArena,
	PacketKick,
	PingKick,
	FPSKick,
	ACKick,
	LastVehicle,
	LastTimeSynced,
	TimesSpawned,
	VWorld,
	lastChat,
	LastAskLeader,
	RoundPlayed,
	shotsHit,
	Float: Accuracy,
	Float: TotalAccuracy,
	TotalshotsHit,
	TotalBulletsFired,
	RconTry,
	PauseCount,
	SpectatingRound,
	SpectatingType,
	HitSound,
	GetHitSound,
	LastEditWepLimit,
	LastEditWeaponSlot,
	bool: ToGiveParachute,
	bool: OnGunmenu,
	GunmenuStyle,
	bool: InDeathCamera,
	RequestedClass,
	RoundTDStyle,

	Text3D: InfoLabel,
	Text3D: DamageLabel,
	DamageBubbleTick
}

// Save variables. Used to reload players and restore their variables.
enum save_vars {
	pName[24],
	pNameWithoutTag[24],
	gHealth,
	gArmour,
	pTeam,
	pInterior,
	pVWorld,
	Float: pCoords[4],
	Float: RDamage,
	Float: TDamage,
	RKills,
	TKills,
	RDeaths,
	TDeaths,
	WeaponsPicked,
	RoundID,
	TPlayed,
	iAccuracy,
	tshotsHit,
	tBulletsShot,
	bool: WasCrashedInStart,
	bool: ToBeAdded,
	bool: CheckScore,
	bool: PauseWait,
	bool: sWasInBase,
	pVehicleID,
	pSeatID,
	HadParachute,
	SavedGrenadeAmmo,
	bool: HadGunmenuGun[MAX_GUNMENU_GUNS]
}

// Used for ranking players
enum rankingEnum
{
	player_Score,
	player_Overall,
	player_Team,
	player_Kills,
	player_Deaths,
	player_TPlayed,
	player_HP,
	player_Acc,
	player_ID
}

new Player[MAX_PLAYERS][PlayerVariables];
new SaveVariables[SAVE_SLOTS][save_vars];
new Iterator: PlayersInVehicles<MAX_PLAYERS>;
