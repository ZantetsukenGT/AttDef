#if defined _attdef_cmd_getpara
	#endinput
#endif
#define _attdef_cmd_getpara

YCMD: getpara(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "give you a parachute.");

	GivePlayerWeapon(playerid, WEAPON_PARACHUTE, 1);
	return SendClientMessage(playerid, -1, "Parachute given.");
}
