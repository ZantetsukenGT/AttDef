#if defined _attdef_OnPInteriorChange
	#endinput
#endif
#define _attdef_OnPInteriorChange

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	// Update interior for whoever is spectating this player as well
	foreach (new i : PlayerSpectators[playerid])
	{
		SetPlayerInterior(i, newinteriorid);
	}
	return 1;
}
