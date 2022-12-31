#if defined _attdef_cmd_gunmenumod
	#endinput
#endif
#define _attdef_cmd_gunmenumod

YCMD: gunmenumod(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "put you in gunmenu modification mode.");
	return ShowPlayerGunmenuModification(playerid);
}

ShowPlayerGunmenuModification(playerid1)
{
	inline InlineGunmenuModifySet(playerid, dialogid, response, listitem, string: inputtext[])
	{
#pragma unused dialogid, listitem
		if (!response)
			return 1;
		new idx = Player[playerid][GunmenuModdingIndex];
		switch (Player[playerid][GunmenuModdingType])
		{
			case GUNMENU_MOD_TYPE_WEAPON:
			{
				new weaponID = GetWeaponID(inputtext);
				if (!IsValidWeapon(weaponID))
				{
					SendErrorMessage(playerid, "Invalid weapon", MSGBOX_TYPE_BOTTOM);
					Dialog_ShowCallback(
						playerid, using inline InlineGunmenuModifySet, DIALOG_STYLE_INPUT, "Changing weapon...",
						va_return("Current weapon: %s\n\nType new weapon name below to change!", ReturnWeaponName(GunmenuData[idx][GunID])), "Set", "Cancel");
					return 1;
				}
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has changed gunmenu index: {FFFFFF}%d " COL_PRIM "from [%s] to [%s]", Player[playerid][Name], idx,
					ReturnWeaponName(GunmenuData[idx][GunID]), ReturnWeaponName(weaponID));
				db_free_result(db_query(sqliteconnection, va_return("UPDATE `Gunmenu` SET `Weapon`=%d WHERE `Weapon`=%d", weaponID, GunmenuData[idx][GunID])));
				GunmenuData[idx][GunID] = weaponID;
			}
			case GUNMENU_MOD_TYPE_LIMIT:
			{
				new limit = strval(inputtext);
				if (limit < 0)
				{
					SendErrorMessage(playerid, "Selection limit cannot be less than 0", MSGBOX_TYPE_BOTTOM);
					Dialog_ShowCallback(
						playerid, using inline InlineGunmenuModifySet, DIALOG_STYLE_INPUT, "Changing limit...",
						va_return("Current limit of %s: %d\n\nType new limit value below to change!", ReturnWeaponName(GunmenuData[idx][GunID]), GunmenuData[idx][GunLimit]), "Set",
						"Cancel");
					return 1;
				}
				va_SendClientMessageToAll(
					-1, "%s " COL_PRIM "has changed {FFFFFF}%s " COL_PRIM "limit to {FFFFFF}%d", Player[playerid][Name], ReturnWeaponName(GunmenuData[idx][GunID]), limit);
				db_free_result(db_query(sqliteconnection, va_return("UPDATE `Gunmenu` SET `Limit`=%d WHERE `Weapon`=%d", limit, GunmenuData[idx][GunID])));
				GunmenuData[idx][GunLimit] = limit;
			}
			case GUNMENU_MOD_TYPE_AMMO:
			{
				new ammo = strval(inputtext);
				if (ammo < 1 || ammo > 9999)
				{
					SendErrorMessage(playerid, "Weapon ammo must be equal to or between 1 and 9999", MSGBOX_TYPE_BOTTOM);
					Dialog_ShowCallback(
						playerid, using inline InlineGunmenuModifySet, DIALOG_STYLE_INPUT, "Changing ammo...",
						va_return("Current ammo of %s: %d\n\nType new ammo value below to change!", ReturnWeaponName(GunmenuData[idx][GunID]), GunmenuData[idx][GunAmmo]), "Set",
						"Cancel");
					return 1;
				}
				va_SendClientMessageToAll(
					-1,
					"%s " COL_PRIM "has changed {FFFFFF}%s " COL_PRIM "ammo to {FFFFFF}%d", Player[playerid][Name], ReturnWeaponName(GunmenuData[idx][GunID]), ammo);
				db_free_result(db_query(sqliteconnection, va_return("UPDATE `Gunmenu` SET `Ammo`=%d WHERE `Weapon`=%d", ammo, GunmenuData[idx][GunID])));
				GunmenuData[idx][GunAmmo] = ammo;
			}
		}
	}

	inline InlineGunmenuModifySub(playerid, dialogid, response, listitem, string: inputtext[])
	{
#pragma unused dialogid, inputtext
		if (!response)
		{
			ShowPlayerGunmenuModification(playerid);
			return 1;
		}
		new idx = Player[playerid][GunmenuModdingIndex];
		switch (listitem)
		{
			case 0:
			{
				Player[playerid][GunmenuModdingType] = GUNMENU_MOD_TYPE_WEAPON;
				Dialog_ShowCallback(
					playerid, using inline InlineGunmenuModifySet, DIALOG_STYLE_INPUT, "Changing weapon...",
					va_return("Current weapon: %s\n\nType new weapon name below to change!", ReturnWeaponName(GunmenuData[idx][GunID])), "Set", "Cancel");
			}
			case 1:
			{
				Player[playerid][GunmenuModdingType] = GUNMENU_MOD_TYPE_LIMIT;
				Dialog_ShowCallback(
					playerid, using inline InlineGunmenuModifySet, DIALOG_STYLE_INPUT, "Changing limit...",
					va_return("Current limit of %s: %d\n\nType new limit value below to change!", ReturnWeaponName(GunmenuData[idx][GunID]), GunmenuData[idx][GunLimit]), "Set",
					"Cancel");
			}
			case 2:
			{
				Player[playerid][GunmenuModdingType] = GUNMENU_MOD_TYPE_AMMO;
				Dialog_ShowCallback(
					playerid, using inline InlineGunmenuModifySet, DIALOG_STYLE_INPUT, "Changing ammo...",
					va_return("Current ammo of %s: %d\n\nType new ammo value below to change!", ReturnWeaponName(GunmenuData[idx][GunID]), GunmenuData[idx][GunAmmo]), "Set", "Cancel");
			}
		}
	}
	inline InlineGunmenuModifyMain(playerid, dialogid, response, listitem, string: inputtext[])
	{
#pragma unused dialogid, inputtext
		if (!response)
			return 1;
		Player[playerid][GunmenuModdingIndex] = listitem;
		Dialog_ShowCallback(
			playerid, using inline InlineGunmenuModifySub, DIALOG_STYLE_LIST, va_return("Modifying: %s", ReturnWeaponName(GunmenuData[listitem][GunID])), "Weapon\nLimit\nAmmo",
			"Select", "Back");
	}

	new str[GUNMENU_LIMIT_DIALOG_SIZE];
	strcat(str, "Weapon\tAmmo\tLimit");
	for (new i = 0; i < MAX_GUNMENU_GUNS; i++)
	{
		strcat(str, va_return("\n{50EB50}%s\t%d\t%d", ReturnWeaponName(GunmenuData[i][GunID]), GunmenuData[i][GunAmmo], GunmenuData[i][GunLimit]));
	}
	Dialog_ShowCallback(playerid1, using inline InlineGunmenuModifyMain, DIALOG_STYLE_TABLIST_HEADERS, "Gunmenu Modification Mode", str, "Modify", "Cancel");
	return 1;
}
