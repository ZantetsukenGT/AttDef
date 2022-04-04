#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_safegametext
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/hooking/' folder."
#endif

#if defined _attdef_impl_safegametext
	#endinput
#endif
#define _attdef_impl_safegametext

/*
	Safe game-text script 
	No more crash due to bad use of '~' character
*/

#include <YSI_Coding\y_hooks>

// Hooked some functions to reject unsafe game-texts.
hook stock GameTextForPlayer(playerid, string[], time, style)
{
	if (!IsSafeGametext(string))
		return -1;
	return continue(playerid, string, time, style);
}

hook stock GameTextForAll(string[], time, style)
{
	if (!IsSafeGametext(string))
		return -1;
	return continue(string, time, style);
}

hook stock Text: TextDrawCreate(Float: x, Float: y, text[])
{
	if (!IsSafeGametext(text))
		return Text: INVALID_TEXT_DRAW;
	return continue(x, y, text);
}

hook stock PlayerText: CreatePlayerTextDraw(playerid, Float: x, Float: y, text[])
{
	if (!IsSafeGametext(text))
		return PlayerText: INVALID_TEXT_DRAW;
	return continue(playerid, x, y, text);
}

hook stock TextDrawSetString(Text: text, string[])
{
	if (!IsSafeGametext(string))
		return -1;
	return continue(text, string);
}

hook stock PlayerTextDrawSetString(playerid, PlayerText: text, string[])
{
	if (!IsSafeGametext(string))
		return -1;
	return continue(playerid, text, string);
}
