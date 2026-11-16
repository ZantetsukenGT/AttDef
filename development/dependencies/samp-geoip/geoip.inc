// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_geoip
	#undef _inc_geoip
#endif
// custom include-guard to ensure we don't duplicate
#if defined _geoip_included
	#endinput
#endif
#define _geoip_included

#include <a_samp>
#tryinclude <logger>
#include <YSI_Coding\y_hooks>

#if !defined _logger_included
	#define Logger_Dbg(%1);
	#define Logger_Err(%1);
#endif

#if !defined MAX_GEOIP_STATUS
	#define MAX_GEOIP_STATUS (8)
#endif

#if !defined MAX_GEOIP_MESSAGE
	#define MAX_GEOIP_MESSAGE (15)
#endif

#if !defined MAX_GEOIP_COUNTRY_NAME
	#define MAX_GEOIP_COUNTRY_NAME (128)
#endif

#if !defined MAX_GEOIP_COUNTRY_CODE
	#define MAX_GEOIP_COUNTRY_CODE (4)
#endif

// E_GEO_DATA matches the ip-api response object, minus the IP address itself
enum E_GEO_DATA {
	bool:E_GEO_READY,					// false if response hasn't arrived yet
	E_GEO_STATUS[MAX_GEOIP_STATUS],		// "status": "success", "fail",
	E_GEO_MESSAGE[MAX_GEOIP_MESSAGE],	// "message": "private range", "reserved range", "invalid query",
	E_GEO_NAME[MAX_GEOIP_COUNTRY_NAME],	// "country": "United States",
	E_GEO_CODE[MAX_GEOIP_COUNTRY_CODE],	// "countryCode": "US",
	bool:E_GEO_PROXY,					// "proxy": true
	bool:E_GEO_HOSTING					// "hosting": true
}

static GeoData[MAX_PLAYERS][E_GEO_DATA];

forward OnGeoResponse(playerid, response_code, data[]);
forward OnGeoDataReady(playerid);

// -
// API
// -

// IsGeoDataReady checks if geo IP data for a player is ready to read yet.
stock bool:IsGeoDataReady(playerid) {
	if(!IsPlayerConnected(playerid)) {
		return false;
	}
	return GeoData[playerid][E_GEO_READY];
}

stock GetPlayerIPSuccess(playerid, &success) {
	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	if(!GeoData[playerid][E_GEO_READY]) {
		return 2;
	}

	success = GeoData[playerid][E_GEO_STATUS][0] == 's';
	return 0;
}

stock GetPlayerIPMessage(playerid, output[], const len = sizeof(output)) {
	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	if(!GeoData[playerid][E_GEO_READY]) {
		return 2;
	}

	if(GeoData[playerid][E_GEO_STATUS][0] == 's') {
		return 3;
	}

	output[0] = EOS;
	strcat(output, GeoData[playerid][E_GEO_MESSAGE], len);
	return 0;
}

stock GetPlayerCountryCode(playerid, output[], const len = sizeof(output)) {
	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	if(!GeoData[playerid][E_GEO_READY]) {
		return 2;
	}

	output[0] = EOS;
	strcat(output, GeoData[playerid][E_GEO_CODE], len);
	return 0;
}

stock GetPlayerCountryName(playerid, output[], const len = sizeof(output)) {
	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	if(!GeoData[playerid][E_GEO_READY]) {
		return 2;
	}

	output[0] = EOS;
	strcat(output, GeoData[playerid][E_GEO_NAME], len);
	return 0;
}

stock GetPlayerIPBlock(playerid, &block) {
	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	if(!GeoData[playerid][E_GEO_READY]) {
		return 2;
	}

	if (GeoData[playerid][E_GEO_PROXY]) {
		block = 1;
	} else if (GeoData[playerid][E_GEO_HOSTING]) {
		block = 2;
	}
	else {
		block = 0;
	}
	return 0;
}


// -
// Internal
// -

static ResetState(playerid)
{
	GeoData[playerid][E_GEO_READY] = false;
	GeoData[playerid][E_GEO_STATUS][0] = EOS;
	GeoData[playerid][E_GEO_MESSAGE][0] = EOS;
	GeoData[playerid][E_GEO_NAME][0] = EOS;
	GeoData[playerid][E_GEO_CODE][0] = EOS;
	GeoData[playerid][E_GEO_PROXY] = false;
	GeoData[playerid][E_GEO_HOSTING] = false;
}

hook OnPlayerConnect(playerid) {
	new addr[16];
	GetPlayerIp(playerid, addr);
	
	if (strequal(addr, "127.0.0.1")) {
		return 1;
	}

	_geoip_doRequest(addr, playerid);
	return 1;
}

hook OnPlayerDisconnect(playerid, reason) {
	ResetState(playerid);
	return 1;
}

_geoip_doRequest(const addr[16], playerid) {
	Logger_Dbg("geoip", "requesting ip data", Logger_S("addr", addr), Logger_I("playerid", playerid));

	new requestAddress[88];
	format(requestAddress, sizeof(requestAddress), "ip-api.com/json/%s?fields=status,message,country,countryCode,proxy,hosting", addr);
	HTTP(playerid, HTTP_GET, requestAddress, "", "OnGeoResponse");
}

hook OnGeoResponse(playerid, response_code, data[]) {
	Logger_Dbg("geoip", "received ip data", Logger_I("playerid", playerid), Logger_I("response_code", response_code));

	if(response_code != 200) {
		Logger_Err("ip-api response status code was not OK", Logger_I("response_code", response_code));
#if !defined _logger_included
		printf("ip-api response status code was not OK: response_code %d", response_code);
#endif
		return 1;
	}

	if(!IsPlayerConnected(playerid)) {
		return 1;
	}

	Logger_Dbg("geoip", "determined target player for ip data", Logger_I("playerid", playerid));

	//{
	//  "status": "fail",
	//  "message": "private range",
	//}

	//{
	//  "status": "success",
	//  "country": "Canada",
	//  "countryCode": "CA",
	//  "proxy": false,
	//  "hosting": false
	//}

	ResetState(playerid);

	GeoData[playerid][E_GEO_READY] = true;
	
	static startIndex, endIndex;

	startIndex = strfind(data, "\"status\":\"") + 10;
	endIndex = strfind(data, "\",", false, startIndex);
	strmid(GeoData[playerid][E_GEO_STATUS], data, startIndex, endIndex);

	if (!strcmp(GeoData[playerid][E_GEO_STATUS], "fail"))
	{
		startIndex = strfind(data, "\"message\":\"", false, endIndex) + 11;
		endIndex = strfind(data, "\"}", false, startIndex);
		strmid(GeoData[playerid][E_GEO_MESSAGE], data, startIndex, endIndex);
	}
	else
	{
		startIndex = strfind(data, "\"country\":\"", false, endIndex) + 11;
		endIndex = strfind(data, "\",", false, startIndex);
		strmid(GeoData[playerid][E_GEO_NAME], data, startIndex, endIndex);
		
		startIndex = strfind(data, "\"countryCode\":\"", false, endIndex) + 15;
		endIndex = strfind(data, "\",", false, startIndex);
		strmid(GeoData[playerid][E_GEO_CODE], data, startIndex, endIndex);
		
		startIndex = strfind(data, "\"proxy\":", false, endIndex) + 8;
		GeoData[playerid][E_GEO_PROXY] = data[startIndex] == 't';
		
		startIndex = strfind(data, "\"hosting\":", false, startIndex) + 10;
		GeoData[playerid][E_GEO_HOSTING] = data[startIndex] == 't';
	}

	Logger_Dbg("geoip", "extracted ip data for player", Logger_S("status", GeoData[playerid][E_GEO_STATUS]), Logger_S("message", GeoData[playerid][E_GEO_MESSAGE]), Logger_I("country", GeoData[playerid][E_GEO_NAME]), Logger_S("code", GeoData[playerid][E_GEO_CODE]), Logger_I("proxy", GeoData[playerid][E_GEO_PROXY]), Logger_S("hosting", GeoData[playerid][E_GEO_HOSTING]));

	CallLocalFunction("OnGeoDataReady", "d", playerid);
	return 1;
}

#if !defined _logger_included
	#undef Logger_Dbg
	#undef Logger_Err
#endif
