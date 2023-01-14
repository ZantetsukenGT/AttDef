#if defined opws_fix_included_
	#endinput
#endif
#define opws_fix_included_

#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid)
{
	CallLocalFunction(#GOOD_OnPlayerConnect, #i, playerid);
	return 1;
}
