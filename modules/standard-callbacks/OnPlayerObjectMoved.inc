#if defined _attdef_OnPObjectMoved
	#endinput
#endif
#define _attdef_OnPObjectMoved

public OnPlayerObjectMoved(playerid, objectid)
{
	if (!Player[playerid][OnGunmenu] || !Iter_Contains(PlayerGunObjects[playerid], objectid))
		return 1;

	new gunmenuIndex = -1;
	for (new i = 0; i < MAX_GUNMENU_GUNS; i++)
	{
		if (GunmenuData[i][GunPlayerObject][playerid] == objectid)
		{
			gunmenuIndex = i;
			break;
		}
	}
	if (gunmenuIndex == -1)
		return 1;

	new Float: x;
	new Float: y;
	new Float: z;
	switch (GunmenuData[gunmenuIndex][GunMovingRoute][playerid])
	{
		case GUN_MOVING_ROUTE_UP: // was moving up
		{
			// move it down
			GetPlayerObjectPos(playerid, objectid, x, y, z);
			MovePlayerObject(playerid, objectid, x, y, z - GUNMENU_OBJECT_Z_CHANGES, GUNMENU_OBJECT_Z_MOVE_SPEED, -25.0, -25.0, -45.0);
			GunmenuData[gunmenuIndex][GunMovingRoute][playerid] = GUN_MOVING_ROUTE_DOWN;
		}
		case GUN_MOVING_ROUTE_DOWN: // was moving down
		{
			// move it up
			GetPlayerObjectPos(playerid, objectid, x, y, z);
			MovePlayerObject(playerid, objectid, x, y, z + GUNMENU_OBJECT_Z_CHANGES, GUNMENU_OBJECT_Z_MOVE_SPEED, 25.0, 25.0, 45.0);
			GunmenuData[gunmenuIndex][GunMovingRoute][playerid] = GUN_MOVING_ROUTE_UP;
		}
		case GUN_MOVING_ROUTE_TOPLAYER: // was moving towards player
		{
			// successful selection
			OnGunObjectMovedToPlayer(playerid, objectid, gunmenuIndex);
		}
	}
	return 1;
}
