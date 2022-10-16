#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_commands
	#endinput
#endif
#define _attdef_mod_commands

/*
	Commands
*/

#define MAX_ADMIN_LEVELS 6									 // (0 = user, 1, 2, 3, 4, 5)
new Group: AdminGroups[MAX_ADMIN_LEVELS];					 // A group for each level
new Iterator: CommandsLevel[MAX_COMMANDS]<MAX_ADMIN_LEVELS>; // iterator array of commands ID with level
