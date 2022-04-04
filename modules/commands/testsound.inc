#if defined _attdef_cmd_testsound
	#endinput
#endif
#define _attdef_cmd_testsound

YCMD: testsound(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "test a sound ID.");
	if (isnull(params) || !IsNumeric(params))
		return SendUsageMessage(playerid, "/testsound [Sound ID]");

	new Val = strval(params);
	if (!IsValidSound(Val))
		return SendErrorMessage(playerid, "This sound ID is not valid. Type 'samp sound id' on Google for more.");

	return PlayerPlaySound(playerid, Val, 0, 0, 0);
}
