#if defined _attdef_cmd_credits
	#endinput
#endif
#define _attdef_cmd_credits

YCMD: credits(playerid, params[], help)
{
	return ShowPlayerDialog(
		playerid, DIALOG_NO_RESPONSE, DIALOG_STYLE_MSGBOX, COL_PRIM "Gamemode Credits",
		"{FFFFFF}Attack-Defend Gamemode Creators: " COL_PRIM "062_ & Whitetiger & Khalid and Beijind\n{FFFFFF}UGMP Bases & Arenas & Gamemode: " COL_PRIM "Volk & Chillax & Excision & cYs & Shooter",
		"Okay", "");
}
