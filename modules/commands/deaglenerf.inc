#if defined _attdef_cmd_deaglenerf
	#endinput
#endif
#define _attdef_cmd_deaglenerf

YCMD: deaglenerf(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "toggle deagle's damage between default damage and custom damage.");
	new str[4], Float: damageValue, bool: shouldNerfDeagle;
	if (sscanf(params, "s[4]F(35.000)", str, damageValue))
		return UsageDeagleNerf(playerid);

	switch (YHash(str, false))
	{
		case _I<off>: shouldNerfDeagle = false;
		case _I<on>: shouldNerfDeagle = true;
		default: return UsageDeagleNerf(playerid);
	}
	return DoDeagleNerf(playerid, shouldNerfDeagle, damageValue);
}

static UsageDeagleNerf(playerid)
{
	if (ShouldNerfDeagle)
		return SendUsageMessage(
			playerid,
			va_return("/deaglenerf [off | on [optional new damage, default if empty: 35, Min: 0.5, Max: 46.2, " COL_PRIM "current: " COL_USAGE "%0.3f{FFFFFF}]]", DeagleNerfValue));
	return SendUsageMessage(playerid, "/deaglenerf [off | on [optional new damage, default if empty: 35, Min: 0.5, Max: 46.2, " COL_PRIM "current: " COL_USAGE "off{FFFFFF}]]");
}

DoDeagleNerf(playerid, bool: shouldNerfDeagle, Float: damageValue)
{
	if (!shouldNerfDeagle)
	{
		if (!ShouldNerfDeagle)
			return SendErrorMessage(playerid, "Deagle nerf is already off.");
		ShouldNerfDeagle = shouldNerfDeagle;
		return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has set {FFFFFF}deagle's damage " COL_PRIM "to its {FFFFFF}default" COL_PRIM ".", Player[playerid][Name]);
	}
	if (damageValue > 46.200)
		return SendErrorMessage(playerid, "This value is higher than the default, are you even nerfing it?");
	if (damageValue < 0.500)
		return SendErrorMessage(playerid, "This value is too low, even bare fists do more damage.");
	new bool: oldBoolean = ShouldNerfDeagle;
	new Float: oldValue = DeagleNerfValue;
	ShouldNerfDeagle = shouldNerfDeagle;
	DeagleNerfValue	 = damageValue;
	if (oldBoolean)
		return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has set {FFFFFF}deagle's damage " COL_PRIM "to " COL_USAGE "%0.3f" COL_PRIM ", previous value: " COL_USAGE "%0.3f", Player[playerid][Name], damageValue, oldValue);
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has set {FFFFFF}deagle's damage " COL_PRIM "to " COL_USAGE "%0.3f{FFFFFF}", Player[playerid][Name], damageValue);
}
