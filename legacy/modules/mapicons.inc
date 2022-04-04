#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_mapicons
	#endinput
#endif
#define _attdef_mod_mapicons

/*
	Global map icon IDs
*/

enum
{
	ATTACKER_DEATH_ICON,
	DEFENDER_DEATH_ICON,
	ATTACKER_BACKUP_ICON,
	DEFENDER_BACKUP_ICON
}
