#if defined _attdef_OnPClickMap
	#endinput
#endif
#define _attdef_OnPClickMap

public OnPlayerClickMap(playerid, Float: fX, Float: fY, Float: fZ)
{
	if (Player[playerid][Level] >= 1 && !Player[playerid][Playing] && !Player[playerid][InDM] && !Player[playerid][InDuel] && !Player[playerid][Spectating])
		SetPlayerPosFindZ(playerid, fX, fY, fZ);
	return 1;
}
