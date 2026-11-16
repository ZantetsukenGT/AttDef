#if defined _attdef_cmd_vr
	#endinput
#endif
#define _attdef_cmd_vr

YCMD: vr(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "repair your vehicle.");
	if (!IsPlayerInAnyVehicle(playerid))
		return SendErrorMessage(playerid, "You aren't in any vehicle");

	new Float: Pos[3];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);

	if (Player[playerid][Playing])
	{
		if (Pos[0] > BAttackerSpawn[Current][0] + 150 || Pos[0] < BAttackerSpawn[Current][0] - 150 || Pos[1] > BAttackerSpawn[Current][1] + 150
			|| Pos[1] < BAttackerSpawn[Current][1] - 150)
			return SendErrorMessage(playerid, "You are too far from attacker spawn."); //If attacker is too far away from his spawn.
	}
	RepairVehicle(GetPlayerVehicleID(playerid));
	return SendClientMessage(playerid, -1, "Vehicle repaired.");
}
