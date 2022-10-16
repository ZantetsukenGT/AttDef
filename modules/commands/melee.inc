#if defined _attdef_cmd_melee
	#endinput
#endif
#define _attdef_cmd_melee

YCMD: melee(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display the melee weapon menu.");
	if (!MeleeAllowed)
		return SendErrorMessage(playerid, "Melee weapons menu is disabled.");
	if (Current == -1)
		return SendErrorMessage(playerid, "Round is not active.");
	if (!Player[playerid][Playing])
		return SendErrorMessage(playerid, "You are not playing.");
	if (RCArena)
		return SendErrorMessage(playerid, "You cannot get gunmenu in RC arenas");
	if (ElapsedTime > 30 || Player[playerid][Team] == REFEREE)
		return SendErrorMessage(playerid, "Too late to show yourself melee weapons menu.");

	ShowPlayerMeleeWeaponsMenu(playerid);

	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has displayed melee weapons menu (/melee).", Player[playerid][Name]);
}
