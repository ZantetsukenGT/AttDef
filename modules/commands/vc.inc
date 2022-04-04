#if defined _attdef_cmd_vc
	#endinput
#endif
#define _attdef_cmd_vc

YCMD: vc(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "change your vehicle paint.");
	new color1, color2;
	if (sscanf(params, "ii", color1, color2))
		return SendUsageMessage(playerid, "/vc [colour1] [colour2]");
	if (!GetPlayerVehicleID(playerid))
		return SendErrorMessage(playerid, "You are not in any vehicle!");
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
		return SendErrorMessage(playerid, "You have to be the driver!");
	return ChangeVehicleColor(GetPlayerVehicleID(playerid), color1, color2);
}
