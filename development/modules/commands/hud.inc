#if defined _attdef_cmd_hud
	#endinput
#endif
#define _attdef_cmd_hud

YCMD: hud(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "toggle aspects of HUD");
	new toggleStr[4], hudid;
	if (sscanf(params, "is[4]", hudid, toggleStr))
	{
		SendUsageMessage(playerid, "/hud [HUD ID] [on / off]");
		return SendClientMessage(playerid, -1, "" COL_PRIM "Note: {FFFFFF}HUD IDs are (-1 = ALL) (0 = spectators) (1 = net stats) (2 = hp percent)");
	}

	if (hudid < -1 || hudid == MAX_PLAYER_INTERFACE_ASPECTS)
		return SendErrorMessage(playerid, "Invalid HUD ID");

	new bool: toggle;
	switch (YHash(toggleStr, false))
	{
		case _I<on>: toggle = true;
		case _I<off>: toggle = false;
		default:
		{
			SendUsageMessage(playerid, "/hud [HUD ID] [on / off]");
			return SendClientMessage(playerid, -1, COL_PRIM "Note: {FFFFFF}HUD IDs are (-1 = ALL) (0 = spectators) (1 = net stats) (2 = hp percent)");
		}
	}

	TogglePlayerInterface(playerid, toggle, hudid);
	return 1;
}
