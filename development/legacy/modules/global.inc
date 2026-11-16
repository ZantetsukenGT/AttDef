#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_global
	#endinput
#endif
#define _attdef_mod_global

/*
	Global variables
*/

#define MAX_GROUP_ACCESS_PASSWORD_LENGTH 10
#define MAX_GROUP_ACCESS_GROUPS			 5

#define MAX_SERVER_PASS_LENGTH			 21

enum TargetInfoData_STRUCT {
	PlayerText: TargetInfoTD,
	TargetInfoTimer,
	TargetInfoLastTick,
	TargetInfoLastTarget
}

new TargetInfoData[MAX_PLAYERS][TargetInfoData_STRUCT];

new ServerPass[MAX_SERVER_PASS_LENGTH + 9]; // contains "password " plus the password itself
new hostname[64];
new GroupAccessPassword[MAX_GROUP_ACCESS_GROUPS][MAX_GROUP_ACCESS_PASSWORD_LENGTH];
new RequestedGroupPass[MAX_PLAYERS][MAX_GROUP_ACCESS_GROUPS][MAX_GROUP_ACCESS_PASSWORD_LENGTH];

new REPLACE_ToAddID[MAX_PLAYERS]; // replace with dialogs
new ThemeChange_listitem[MAX_PLAYERS char];

new LastClickedPlayer[MAX_PLAYERS];

new ChangingSkinOfTeam[MAX_PLAYERS];

new bool: PlayerOnInterface[MAX_PLAYERS char];
new bool: ChatDisabled = false;
new AnnTimer;
