#if defined _attdef_cmd_random
	#endinput
#endif
#define _attdef_cmd_random

#include "commands/ra.inc"
#include "commands/rb.inc"

YCMD: random(playerid, params[], help)
{
	/*if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		return SendErrorMessage(playerid, "You need to be a higher admin level.");*/
	if (help)
		return SendCommandHelpMessage(playerid, "start a random round.");
	if (Current != -1)
		return SendErrorMessage(playerid, "A round is in progress, please wait for it to end.");
	if (!AllowStartBase)
		return SendErrorMessage(playerid, "Please wait.");
	if (isnull(params) || IsNumeric(params))
		return SendUsageMessage(playerid, "/random [base | arena]");

	switch (YHash(params, false))
	{
		case _I<base>: DoRandomBase(playerid);
		case _I<arena>: DoRandomArena(playerid);
		default: return SendUsageMessage(playerid, "/random [base | arena]");
	}
	return 1;
}
