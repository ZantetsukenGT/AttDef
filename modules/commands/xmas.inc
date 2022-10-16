#if defined _attdef_cmd_xmas
	#endinput
#endif
#define _attdef_cmd_xmas

YCMD: xmas(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "toggle christmas mode (if filterscript is available)");
	if (isnull(params))
		return SendUsageMessage(playerid, "/xmas [on / off]");

	switch (YHash(params, false))
	{
		case _I<on>:
		{
			SendRconCommand("loadfs xmas");
			return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has attempted to load {FFFFFF}Xmas filterscript" COL_PRIM ".", Player[playerid][Name]);
		}
		case _I<off>:
		{
			SendRconCommand("unloadfs xmas");
			return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has attempted to unload {FFFFFF}Xmas filterscript" COL_PRIM ".", Player[playerid][Name]);
		}
	}
	return SendUsageMessage(playerid, "/xmas [on / off]");
}
