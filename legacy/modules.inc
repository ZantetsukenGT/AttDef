#if defined _attdef_modules
	#endinput
#endif
#define _attdef_modules

// this file is an attempt to neatly centralize modules includes into the gamemode

// there were efforts to smartly couple both header and implementation files within one single include
// but there are too many circular dependencies between the modules, so implementation files go after the headers
#if defined _attdef_header_incl
	#undef _attdef_header_incl
#endif
#define _attdef_header_incl

// Att-Def' core modules modules
#include "modules/antimacro.inc"
#include "modules/colors.inc"
#include "modules/commands.inc"
#include "modules/common.inc"
#include "modules/config.inc"
#include "modules/database.inc"
#include "modules/deathcam.inc"
#include "modules/dialogs.inc"
#include "modules/duel.inc"
#include "modules/fields.inc"
#include "modules/fightstyle.inc"
#include "modules/freecam.inc"
#include "modules/global.inc"
#include "modules/gunmenu.inc"
#include "modules/longarrays.inc"
#include "modules/mapicons.inc"
#include "modules/match.inc"
#include "modules/messagebox.inc"
#include "modules/player.inc"
#include "modules/spectate.inc"
#include "modules/teamhpbars.inc"
#include "modules/teaminfotd.inc"
#include "modules/textdraws.inc"
#include "modules/this_core.inc"
#include "modules/vote.inc"
#include "modules/weaponbinds.inc"
#include "modules/weaponshot.inc"

#undef _attdef_header_incl

// there were efforts to smartly couple both header and implementation files within one single include
// but there are too many circular dependencies between the modules, so implementation files go after the headers
#if defined _attdef_impl_incl
	#undef _attdef_impl_incl
#endif
#define _attdef_impl_incl

// modules that consists of hooking must go first
#include "modules/impl/hooking/commonhooking.inc"

// Att-Def' core modules modules
#include "modules/impl/antimacro.inc"
#include "modules/impl/colors.inc"
#include "modules/impl/commands.inc"
#include "modules/impl/common.inc"
#include "modules/impl/config.inc"
#include "modules/impl/database.inc"
#include "modules/impl/deathcam.inc"
#include "modules/impl/dialogs.inc"
#include "modules/impl/match.inc"
#include "modules/impl/duel.inc"
#include "modules/impl/fields.inc"
#include "modules/impl/fightstyle.inc"
#include "modules/impl/freecam.inc"
#include "modules/impl/global.inc"
#include "modules/impl/gunmenu.inc"
#include "modules/impl/messagebox.inc"
#include "modules/impl/player.inc"
#include "modules/impl/spectate.inc"
#include "modules/impl/teamhpbars.inc"
#include "modules/impl/teaminfotd.inc"
#include "modules/impl/textdraws.inc"
#include "modules/impl/this_core.inc"
#include "modules/impl/vote.inc"
#include "modules/impl/weaponbinds.inc"
#include "modules/impl/weaponshot.inc"

#undef _attdef_impl_incl
