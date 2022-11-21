#if defined _OnGeoDataReady_included
	#endinput
#endif
#define _OnGeoDataReady_included

public OnGeoDataReady(playerid)
{
	new IPSuccess;
	GetPlayerIPSuccess(playerid, IPSuccess);
	if (IPSuccess)
	{
		new CountryName[MAX_GEOIP_COUNTRY_NAME];
		new IPBlock;
		GetPlayerCountryName(playerid, CountryName);
		GetPlayerIPBlock(playerid, IPBlock);
		switch (IPBlock)
		{
			case 0: va_SendClientMessageToAll(-1, "%s {CCCCCC}(ID: %d) has connected [{FFFFFF}%s{CCCCCC}]", Player[playerid][Name], playerid, CountryName);
			case 1: va_SendClientMessageToAll(-1, "%s {CCCCCC}(ID: %d) has connected [{FFFFFF}%s {FF6666}Proxy{CCCCCC}]", Player[playerid][Name], playerid, CountryName);
			case 2: va_SendClientMessageToAll(-1, "%s {CCCCCC}(ID: %d) has connected [{FFFFFF}%s " COL_WARNING "Proxy?{CCCCCC}]", Player[playerid][Name], playerid, CountryName);
		}
	}
	else
	{
		new IPMessage[MAX_GEOIP_MESSAGE];
		GetPlayerIPMessage(playerid, IPMessage);
		va_SendClientMessageToAll(-1, "%s {CCCCCC}(ID: %d) has connected [{FFFFFF}%s " COL_WARNING "Proxy?{CCCCCC}]", Player[playerid][Name], playerid, IPMessage);
	}
	return 1;
}
