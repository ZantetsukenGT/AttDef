#if defined _attdef_OnPSelectObject
	#endinput
#endif
#define _attdef_OnPSelectObject

public OnPlayerSelectObject(playerid, type, objectid, modelid, Float: fX, Float: fY, Float: fZ)
{
	if (Player[playerid][OnGunmenu] && type == SELECT_OBJECT_PLAYER_OBJECT)
	{
		new gunmenuIndex = -1;
		for (new i = 0; i != MAX_GUNMENU_GUNS; i++)
		{
			if (GunmenuData[i][GunPlayerObject][playerid] == objectid)
			{
				gunmenuIndex = i;
				break;
			}
		}
		if (gunmenuIndex != -1)
		{
			if (GunmenuData[gunmenuIndex][GunMovingRoute][playerid] == GUN_MOVING_ROUTE_TOPLAYER)
			{
				// object is already moving to player, so we cancel this
				return 1;
			}
		}
		OnPlayerSelectGunmenuObject(playerid, objectid, modelid);
		return 1;
	}
	return 1;
}
