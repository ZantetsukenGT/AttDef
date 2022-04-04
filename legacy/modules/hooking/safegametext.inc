#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_safegametext
	#endinput
#endif
#define _attdef_mod_safegametext

#include "modules/this_core.inc"

#if SAFE_GAMETEXT_AUTO_CHECK != 0

/*
	Safe game-text script 
	No more crash due to bad use of '~' character
*/

#else
	#if !defined _attdef_impl_safegametext
		#define _attdef_impl_safegametext
	#endif
#endif
