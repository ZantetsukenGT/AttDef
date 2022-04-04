#if defined _attdef_cmd_gunmenu
	#endinput
#endif
#define _attdef_cmd_gunmenu

YCMD: gunmenu(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display the weapon menu.");
	if (Current == -1)
		return SendErrorMessage(playerid, "Round is not active.");
	if (!Player[playerid][Playing])
		return SendErrorMessage(playerid, "You are not playing.");
	if (RCArena)
		return SendErrorMessage(playerid, "You cannot get gunmenu in RC arenas");
	if (ElapsedTime <= 30 && Player[playerid][Team] != REFEREE)
	{
		ShowPlayerGunmenu(playerid, 0);

		new iString[128];
		format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has displayed gunmenu (/gunmenu).", Player[playerid][Name]);
		return SendClientMessageToAll(-1, iString);
	}
	return SendErrorMessage(playerid, "Too late to show yourself weapon menu.");
}
