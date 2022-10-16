#if !defined _attdef_impl_incl
	#error "Module's implementation file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if !defined _attdef_mod_colors
	#error "Module's header file must be included before its implementation file, it should be located in the 'legacy/modules/' folder."
#endif

#if defined _attdef_impl_colors
	#endinput
#endif
#define _attdef_impl_colors

/*
	Gamemode colors: teams, messages... etc
*/

SetTeamDefaultColors()
{
	TextColor[ATTACKER]		= "{FF0033}";
	TextColor[ATTACKER_SUB] = "{FFAAAA}";
	TextColor[DEFENDER]		= "{3344FF}";
	TextColor[DEFENDER_SUB] = "{AAAAFF}";
	TextColor[REFEREE]		= "{FFFF88}";

	TDC[NON]				= "~p~";
	TDC[ATTACKER]			= "~r~";
	TDC[ATTACKER_SUB]		= "~r~~h~";
	TDC[DEFENDER]			= "~b~";
	TDC[DEFENDER_SUB]		= "~b~~h~";
	TDC[REFEREE]			= "~y~~h~";
}

SaveThemeSettings()
{
	new query[128];
	format(query, sizeof(query), "UPDATE `Configs` SET `Value` = '%q' WHERE `Option` = 'MainTextColour'", MAIN_TEXT_COLOUR);
	db_free_result(db_query(sqliteconnection, query));

	format(query, sizeof(query), "UPDATE `Configs` SET `Value` = %d WHERE `Option` = 'MainBackgroundColour'", MAIN_BACKGROUND_COLOUR);
	db_free_result(db_query(sqliteconnection, query));
}

ChangeTheme(playerid, listitem)
{
	MAIN_TEXT_COLOUR[0] = EOS;
	switch (listitem)
	{
		case 0: // White (Background) & Black (Text)
		{
			strcat(MAIN_TEXT_COLOUR, "~l~");
			MAIN_BACKGROUND_COLOUR = 0xEEEEEE11;
		}
		case 1: // Black (Background) & White (Text)
		{
			strcat(MAIN_TEXT_COLOUR, "~w~");
			MAIN_BACKGROUND_COLOUR = 0x00000044;
		}
		case 2: // White (Background) & Red (Text)
		{
			strcat(MAIN_TEXT_COLOUR, "~r~");
			MAIN_BACKGROUND_COLOUR = 0xEEEEEE11;
		}
		case 3: // Black (Background) & Red (Text)
		{
			strcat(MAIN_TEXT_COLOUR, "~r~");
			MAIN_BACKGROUND_COLOUR = 0x00000044;
		}
		case 4: // White (Background) & Blue (Text)
		{
			strcat(MAIN_TEXT_COLOUR, "~b~");
			MAIN_BACKGROUND_COLOUR = 0xEEEEEE11;
		}
		case 5: // Black (Background) & Blue (Text)
		{
			strcat(MAIN_TEXT_COLOUR, "~b~");
			MAIN_BACKGROUND_COLOUR = 0x00000044;
		}
		case 6: // White (Background) & Green (Text)
		{
			strcat(MAIN_TEXT_COLOUR, "~g~");
			MAIN_BACKGROUND_COLOUR = 0xEEEEEE11;
		}
		case 7: // Black (Background) & Green (Text)
		{
			strcat(MAIN_TEXT_COLOUR, "~g~");
			MAIN_BACKGROUND_COLOUR = 0x00000044;
		}
		case 8: // White (Background) & Purple (Text)
		{
			strcat(MAIN_TEXT_COLOUR, "~p~");
			MAIN_BACKGROUND_COLOUR = 0xEEEEEE11;
		}
		case 9: // Black (Background) & Purple (Text)
		{
			strcat(MAIN_TEXT_COLOUR, "~p~");
			MAIN_BACKGROUND_COLOUR = 0x00000044;
		}
	}
	SaveThemeSettings();
	va_SendClientMessageToAll(-1, "%s has set up a new theme colour. Server is restarting so the changes can take effect.", Player[playerid][Name]);
	SendRconCommand("gmx");
	return 1;
}
