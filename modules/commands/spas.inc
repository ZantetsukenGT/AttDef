#if defined _attdef_cmd_spas
	#endinput
#endif
#define _attdef_cmd_spas

YCMD: spas(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "toggle spas selection in gunmenu.");
	// Find the index of Spas in gunmenu
	new idx = -1;
	for (new i = 0; i < MAX_GUNMENU_GUNS; i++)
	{
		if (GunmenuData[i][GunID] == WEAPON_SHOTGSPA)
		{
			idx = i;
			break;
		}
	}
	if (idx == -1)
		return SendErrorMessage(playerid, "Spas doesn't exist in the gunmenu.");
	if (GunmenuData[idx][GunLimit] <= 0)
	{
		GunmenuData[idx][GunLimit] = 1;
		db_free_result(db_query(sqliteconnection, va_return("UPDATE `Gunmenu` SET `Limit`=1 WHERE `Weapon`=%d", GunmenuData[idx][GunID])));
		return va_SendClientMessageToAll(-1, "%s " COL_PRIM "has changed {FFFFFF}Spas " COL_PRIM "limit to {FFFFFF}1", Player[playerid][Name]);
	}

	va_SendClientMessageToAll(-1, "%s " COL_PRIM "has changed {FFFFFF}Spas " COL_PRIM "limit to {FFFFFF}0", Player[playerid][Name]);
	db_free_result(db_query(sqliteconnection, va_return("UPDATE `Gunmenu` SET `Limit`=0 WHERE `Weapon`=%d", GunmenuData[idx][GunID])));
	GunmenuData[idx][GunLimit] = 0;
	if (Current == -1)
		return 1;

	// If there's a round in progress
	// Loop through all players who are in round
	foreach (new i : PlayersInRound)
	{
		// The following code checks if this player (i) has this gun (spas)
		if (GunmenuData[idx][HasGun][i])
		{
			// Show them gunmenu
			ShowPlayerGunmenu(i, 0);
			va_SendClientMessageToAll(-1, "%s " COL_PRIM "was automatically shown the gunmenu because they had Spas.", Player[i][Name]);
		}
	}
	return 1;
}
