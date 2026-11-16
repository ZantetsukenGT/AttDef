#include "geoip"

main() {
    Logger_ToggleDebug("geoip", true);
}

public OnPlayerCommandText(playerid, cmdtext[]) {
    if(!strcmp(cmdtext, "/ip")) {
        if(!IsGeoDataReady(playerid)) {
            SendClientMessage(playerid, -1, "Data not ready yet...");
            return 1;
        }

        new
            code[MAX_GEOIP_COUNTRY_CODE],
            name[MAX_GEOIP_COUNTRY_NAME],
            block,
            str[128];

        GetPlayerCountryCode(playerid, code);
        GetPlayerCountryName(playerid, name);
        GetPlayerIPBlock(playerid, block);

        format(str, sizeof str,
            "Country: %s (%s), Block: %d",
            name, code, asn, isp, block);
        
        SendClientMessage(playerid, -1, str);

        return 1;
    }

    return 0;
}
