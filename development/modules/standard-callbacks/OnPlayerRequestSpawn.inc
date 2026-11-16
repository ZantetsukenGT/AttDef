#if defined _attdef_OnPRequestSpawn
	#endinput
#endif
#define _attdef_OnPRequestSpawn

public OnPlayerRequestSpawn(playerid)
{
	if (!Player[playerid][Spawned])
	{
		CallLocalFunction("OnPlayerRequestClass", "ii", playerid, 0);
		return 0;
	}
	return 1;
}
