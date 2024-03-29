#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_textdraws
	#endinput
#endif
#define _attdef_mod_textdraws

/*
	All textdraws: Global, per-player and 3D
*/

#include "modules/this_core.inc"
#include "modules/weaponshot.inc"

#define ATTACKER_CHANGES_X			 19.4
#define ATTACKER_CHANGES_Y			 0.0
#define DEFENDER_CHANGES_X			 -79
#define DEFENDER_CHANGES_Y			 0.0

// Player interface

#define MAX_PLAYER_INTERFACE_ASPECTS 2

#define INTERFACE_SPEC				 0
#define INTERFACE_NET				 1

new bool: PlayerInterface[MAX_PLAYERS][MAX_PLAYER_INTERFACE_ASPECTS];

/*
// Match scoreboard textdraws (credits [U]27 aka [U]jay)
new Text: ScoreBoardBoxTD[2];
new Text: RoundsPlayed;
new Text: TeamScoreText;
new Text: TeamAttackerTD;
new Text: TeamDefenderTD;
new Text: MatchVersusTD;
new Text: MatchScoreBoardSprite;
*/

// Scoreboard textdraws
new Text: RoundsPlayed;	 // Shows how many rounds are played out of for example 9 rounds. (Rounds 3/9)
new Text: TeamScoreText; // Shows team name and score (e.g. TeK 3 CZE 3)

// - Global Textdraws -
new Text: AnnTD;
new Text: PauseTD;
new Text: LockServerTD;
new Text: CloseText;
new Text: WarModeText;
new Text: SettingBox;
new Text: AttHpLose;
new Text: DefHpLose;
new Text: TeamHpLose[2];
new Text: EN_AttackerBox;
new Text: EN_DefenderBox;
new Text: EN_CheckPoint;
new Text: CheckpointWarningBox;
new Text: DarkScreen;
new Text: RedDeathScreen;
new Text: GunmenuLimitsTD[MAX_TEAMS];

// - Round Textdraws

new Text: leftRedBG;
new Text: rightBlueBG;
new Text: timerCenterTD,
	Text: timerCircleTD;
new Text: leftTeamData;
new Text: rightTeamData;
new Text: centerTeamNames;
new Text: attackerNameTD,
	Text: defenderNameTD;
new Text: AttDef_RoundStats,
	Text: AttDef_RoundTimer;
new Text: AttDef_ModernRoundStats[10];

// - Result Textdraws - added by Niko_boy // -

new //designer:
	Text: leftBG, Text: rightBG,
	Text: leftUpBG, Text: rightUpBG,
	Text: leftHeader, Text: rightHeader,
	Text: leftULine, Text: rightULine,
	Text: leftUpText, Text: rightUpText,
	Text: leftText, Text: rightText,
	Text: leftTop, //Text: rightTop      ,
	Text: lowerBG, Text: lowerULine,
	Text: topTextScore, Text: teamWonHow,
	//contents:
	Text: leftNames, Text: rightNames,
	Text: leftKills, Text: rightKills,
	Text: leftHP, Text: rightHP,
	Text: leftDeaths, Text: rightDeaths,
	Text: leftDmg, Text: rightDmg,
	Text: leftAcc, Text: rightAcc,
	Text: leftPlayed, Text: rightPlayed;

// - Player Textdraws -

new PlayerText: FPSPingPacket[MAX_PLAYERS];						 // Ping, FPS and Packetloss textdraw on top right corner.
new PlayerText: RoundKillDmgTDmg[MAX_PLAYERS];					 // Shows Kills, Damage and Total Damage on the left hand side of the radar.
new PlayerText: FriendlyDamage[MAX_PLAYERS][2];					 // Shows when your teammate hits you or you hit them
new PlayerText: WhoSpec[MAX_PLAYERS];							 // Shows who is spectating you.
new PlayerText: SpecText[MAX_PLAYERS][4];						 // Shows spectated player info.
new PlayerText: AreaCheckTD[MAX_PLAYERS];						 // Show countdown textdraw when the player is out of arena.
new PlayerText: AreaCheckBG[MAX_PLAYERS];
new PlayerText: DeathText[MAX_PLAYERS][2];
new PlayerText: TD_RoundSpec[MAX_PLAYERS];
new PlayerText: BaseID_VS[MAX_PLAYERS];
new PlayerText: VInfo[MAX_PLAYERS];
new DeathMessageStr[MAX_PLAYERS][32];
