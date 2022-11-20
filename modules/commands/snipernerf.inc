#if defined _attdef_cmd_snipernerf
	#endinput
#endif
#define _attdef_cmd_snipernerf

YCMD: snipernerf(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "toggle sniper's damage between default damage and custom damage.");
	new str[4], Float: damageValue, bool: shouldNerfSniper;
	if (sscanf(params, "s[4]F(25.000)", str, damageValue))
		return UsageSniperNerf(playerid);

	switch (YHash(str, false))
	{
		case _I<off>: shouldNerfSniper = false;
		case _I<on>: shouldNerfSniper = true;
		default: return UsageSniperNerf(playerid);
	}
	return DoSniperNerf(playerid, shouldNerfSniper, damageValue);
}

static UsageSniperNerf(playerid)
{
	if (ShouldNerfSniper)
		return SendUsageMessage(
			playerid,
			va_return("/snipernerf [off | on [optional new damage, default if empty: 25, Min: 0.5, Max: 41.25, " COL_PRIM "current: " COL_USAGE "%0.3f{FFFFFF}]]", SniperNerfValue));
	return SendUsageMessage(playerid, "/snipernerf [off | on [optional new damage, default if empty: 25, Min: 0.5, Max: 41.25, " COL_PRIM "current: " COL_USAGE "off{FFFFFF}]]");
}

DoSniperNerf(playerid, bool: shouldNerfSniper, Float: damageValue)
{
	if (!shouldNerfSniper)
	{
		if (!ShouldNerfSniper)
			return SendErrorMessage(playerid, "Sniper nerf is already off.");
		ShouldNerfSniper = shouldNerfSniper;
		return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has set {FFFFFF}sniper's damage " COL_PRIM "to its {FFFFFF}default" COL_PRIM ".", Player[playerid][Name]);
	}
	if (damageValue > 41.250)
		return SendErrorMessage(playerid, "This value is higher than the default, are you even nerfing it?");
	if (damageValue < 0.500)
		return SendErrorMessage(playerid, "This value is too low, even bare fists do more damage.");
	new bool: oldBoolean = ShouldNerfSniper;
	new Float: oldValue = SniperNerfValue;
	ShouldNerfSniper = shouldNerfSniper;
	SniperNerfValue	 = damageValue;
	if (oldBoolean)
		return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has set {FFFFFF}sniper's damage " COL_PRIM "to " COL_USAGE "%0.3f" COL_PRIM ", previous value: " COL_USAGE "%0.3f", Player[playerid][Name], damageValue, oldValue);
	return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has set {FFFFFF}sniper's damage " COL_PRIM "to " COL_USAGE "%0.3f{FFFFFF}", Player[playerid][Name], damageValue);
}
