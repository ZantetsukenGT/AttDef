#if defined _attdef_OnPStreamOut
	#endinput
#endif
#define _attdef_OnPStreamOut

public OnPlayerStreamOut(playerid, forplayerid)
{
	if (Player[playerid][Playing])
	{
		if (Player[forplayerid][Team] != Player[playerid][Team])
			SetPlayerMarkerForPlayer(forplayerid, playerid, GetPlayerColor(playerid) & 0xFFFFFF00);
		else
			SetPlayerMarkerForPlayer(forplayerid, playerid, GetPlayerCorrectMarkerCol(playerid, forplayerid) | 0x00000055);
	}
	else if (Player[playerid][InDuel] && Player[forplayerid][InDuel])
		SetPlayerMarkerForPlayer(forplayerid, playerid, GetPlayerColor(playerid) & 0xFFFFFF00);
	else if (!Player[playerid][Playing] && !Player[forplayerid][Playing])
		SetPlayerMarkerForPlayer(forplayerid, playerid, GetPlayerCorrectMarkerCol(playerid, forplayerid) | 0x00000055);
	return 1;
}
