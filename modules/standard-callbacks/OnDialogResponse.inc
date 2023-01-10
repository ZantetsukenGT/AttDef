#if defined _attdef_OnDResponse
	#endinput
#endif
#define _attdef_OnDResponse

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == DIALOG_NO_RESPONSE)
		return 1;
	switch (dialogid)
	{
		case DIALOG_GUNMENU_MELEE:
		{
			if (response)
			{
				new weap = MeleeWeaponsArray_ID[listitem], ammo = MeleeWeaponsArray_AMMO[listitem];

				if (DoesPlayerHaveWeapon(playerid, weap))
				{
					RemovePlayerWeapon(playerid, weap);
				}
				else
				{
					GivePlayerWeapon(playerid, weap, ammo);
				}
				SetTimerEx("ShowPlayerMeleeWeaponsMenu", GetPlayerPing(playerid) + 200, false, "i", playerid);
			}
			return 1;
		}
		case DIALOG_WEAPONBIND_MAIN:
		{
			if (response)
			{
				if (listitem == 0) // Toggle
				{
					Player[playerid][WeaponBinding] = !Player[playerid][WeaponBinding];
					new str[80];
					format(str, sizeof(str), "UPDATE Players SET WeaponBinding = %d WHERE Name = '%q'", Player[playerid][WeaponBinding], Player[playerid][Name]);
					db_free_result(db_query(sqliteconnection, str));
					return 1;
				}
				new index										   = listitem - 1;
				WeaponBindData[playerid][ModifyingWeaponBindIndex] = index;
				new str[140];
				format(
					str, sizeof str, "Key: %s+%s\nCurrent weapon: %s\n\nType weapon name or ID below to code this key bind for it", WEAPON_BIND_PRIMARY_KEY_TEXT_ALT,
					WeaponBindKeyText_ALT[index], ReturnWeaponName(WeaponBindData[playerid][BindKeyWeapon][index]));
				ShowPlayerDialog(playerid, DIALOG_WEAPONBIND_MODIFY, DIALOG_STYLE_INPUT, "Coding weapon key bind", str, "Code it", "Cancel");
			}
			return 1;
		}
		case DIALOG_WEAPONBIND_MODIFY:
		{
			if (response)
			{
				if (isnull(inputtext))
					return 1;

				new weaponid;
				if (IsNumeric(inputtext))
					weaponid = strval(inputtext);
				else
					weaponid = GetWeaponID(inputtext);

				if (weaponid == 0 || IsValidWeapon(weaponid))
				{
					new index									   = WeaponBindData[playerid][ModifyingWeaponBindIndex];
					WeaponBindData[playerid][BindKeyWeapon][index] = weaponid;
					new str[80];
					format(str, sizeof(str), "UPDATE Players SET WeaponBind%d = %d WHERE Name = '%q'", index, weaponid, Player[playerid][Name]);
					db_free_result(db_query(sqliteconnection, str));
					ShowPlayerWeaponBindTextDraw(playerid, 5000);
				}
			}
			return 1;
		}
		case DIALOG_THEME_CHANGE1:
		{
			if (response)
			{
				ThemeChange_listitem { playerid } = listitem;
				ShowPlayerDialog(
					playerid, DIALOG_THEME_CHANGE2, DIALOG_STYLE_MSGBOX, "Caution: server needs restart",
					"The server needs to be restarted now for the changes to be\ncompletely applied. Restart now or cancel everything?", "Restart", "Cancel");
			}
			return 1;
		}
		case DIALOG_THEME_CHANGE2:
		{
			if (response)
			{
				ChangeTheme(playerid, ThemeChange_listitem { playerid });
			}
			return 1;
		}
		case PLAYERCLICK_DIALOG:
		{
			if (response)
			{
				if (!IsPlayerConnected(LastClickedPlayer[playerid]))
					return SendErrorMessage(playerid, "That player is not connected anymore!");

				switch (listitem)
				{
					case 0:
					{
						new statsSTR[4][300], namee[60], CID, Country[MAX_GEOIP_COUNTRY_NAME], CountryCode[MAX_GEOIP_COUNTRY_CODE], techInfo[200];
						CID = LastClickedPlayer[playerid];

						format(namee, sizeof(namee), "{FF3333}Player {FFFFFF}%s {FF3333}Stats", Player[CID][Name]);
						GetPlayerCountryName(CID, Country);
						GetPlayerCountryCode(CID, CountryCode);

						new TD = Player[CID][TotalDeaths];
						new RD = Player[CID][RoundDeaths];
						new MC = Player[playerid][ChatChannel];
						new YC = Player[CID][ChatChannel];

						format(
							statsSTR[0], sizeof(statsSTR[]),
							COL_PRIM "- {FFFFFF}Country: %s, %s\n\n" COL_PRIM "- {FFFFFF}Round Kills: \t%d\t\t" COL_PRIM "- {FFFFFF}Total Kills: \t\t%d\t\t" COL_PRIM "- {FFFFFF}FPS: \t\t\t%d\n" COL_PRIM "- {FFFFFF}Round Deaths: \t%d\t\t" COL_PRIM "- {FFFFFF}Total Deaths: \t%d\t\t" COL_PRIM "- {FFFFFF}Ping: \t\t\t%d\n",
							Country, CountryCode, Player[CID][RoundKills], Player[CID][TotalKills], GetPlayerFPS(CID), RD, TD, GetPlayerPing(CID));
						format(
							statsSTR[1], sizeof(statsSTR[]),
							COL_PRIM "- {FFFFFF}Round Damage: \t%d\t\t" COL_PRIM "- {FFFFFF}Total Damage:   \t%d\t\t" COL_PRIM "- {FFFFFF}Packet-Loss:   \t%.1f\n\n" COL_PRIM "- {FFFFFF}Player Weather: \t%d\t\t" COL_PRIM "- {FFFFFF}Chat Channel: \t%d\t\t" COL_PRIM "- {FFFFFF}In Round: \t\t%s\n",
							floatround(Player[CID][RoundDamage]), floatround(Player[CID][TotalDamage]), NetStats_PacketLossPercent(CID), Player[CID][Weather], (MC == YC ? YC : -1),
							(Player[CID][Playing] == true ? ("Yes") : ("No")));
						format(
							statsSTR[2], sizeof(statsSTR[]),
							COL_PRIM "- {FFFFFF}Player Time: \t\t%d\t\t" COL_PRIM "- {FFFFFF}DM ID: \t\t%d\t\t" COL_PRIM "- {FFFFFF}Hit Sound: \t\t%d\n" COL_PRIM "- {FFFFFF}Player NetCheck: \t%s\t\t" COL_PRIM "- {FFFFFF}Player Level: \t%d\t\t" COL_PRIM "- {FFFFFF}Get Hit Sound: \t%d\n",
							Player[CID][Time], (Player[CID][DMReadd] > 0 ? Player[CID][DMReadd] : -1), Player[CID][HitSound], (Player[CID][NetCheck] ? ("Enabled") : ("Disabled")),
							Player[CID][Level], Player[CID][GetHitSound]);
						format(
							statsSTR[3], sizeof(statsSTR[]), "" COL_PRIM "- {FFFFFF}Duels Won: \t\t%d\t\t" COL_PRIM "- {FFFFFF}Duels Lost: \t\t%d", Player[CID][DuelsWon],
							Player[CID][DuelsLost]);
						new TotalStr[1400];
						format(TotalStr, sizeof(TotalStr), "%s%s%s%s%s", techInfo, statsSTR[0], statsSTR[1], statsSTR[2], statsSTR[3]);

						ShowPlayerDialog(playerid, DIALOG_CLICK_STATS, DIALOG_STYLE_MSGBOX, namee, TotalStr, "Close", "");
					}
					case 1:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/aka %d", LastClickedPlayer[playerid]));
					}
					case 2:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/spec %d", LastClickedPlayer[playerid]));
					}
					case 3:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/add %d", LastClickedPlayer[playerid]));
					}
					case 4:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/remove %d", LastClickedPlayer[playerid]));
					}
					case 5:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/readd %d", LastClickedPlayer[playerid]));
					}
					case 6:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/givemenu %d", LastClickedPlayer[playerid]));
					}
					case 7:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/goto %d", LastClickedPlayer[playerid]));
					}
					case 8:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/get %d", LastClickedPlayer[playerid]));
					}
					case 9:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/slap %d", LastClickedPlayer[playerid]));
					}
					case 10:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/mute %d No Reason Specified", LastClickedPlayer[playerid]));
					}
					case 11:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/unmute %d", LastClickedPlayer[playerid]));
					}
					case 12:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/kick %d No Reason Specified", LastClickedPlayer[playerid]));
					}
					case 13:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/ban %d No Reason Specified", LastClickedPlayer[playerid]));
					}
				}
			}
			return 1;
		}
		case DIALOG_SERVER_PASS:
		{
			if (response)
			{
				if (isnull(inputtext))
					return 1;
				if (strlen(inputtext) > MAX_SERVER_PASS_LENGTH)
				{
					SendErrorMessage(playerid, "Server password is too long.");
					ShowPlayerDialog(playerid, DIALOG_SERVER_PASS, DIALOG_STYLE_INPUT, "" COL_PRIM "Server Password", "" COL_PRIM "Enter server password below:", "Ok", "Close");
					return 1;
				}
				format(ServerPass, sizeof(ServerPass), "password %s", inputtext);
				SendRconCommand(ServerPass);

				ServerLocked = true;
				PermLocked	 = false;

				new iString[144];
				format(iString, sizeof(iString), "%sServer Pass: ~r~%s", MAIN_TEXT_COLOUR, inputtext);
				TextDrawSetString(LockServerTD, iString);

				format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has locked the server. Password: {FFFFFF}%s", Player[playerid][Name], inputtext);
				SendClientMessageToAll(-1, iString);
			}
			return 1;
		}
		case DIALOG_CURRENT_TOTAL:
		{
			if (isnull(inputtext))
				return 1;
			if (!IsNumeric(inputtext))
			{
				SendErrorMessage(playerid, "You can only use numeric input.");
				ShowPlayerDialog(
					playerid, DIALOG_CURRENT_TOTAL, DIALOG_STYLE_INPUT, "" COL_PRIM "Rounds Dialog", "" COL_PRIM "Enter current round or total rounds to be played:", "Current",
					"Total");
				return 1;
			}

			new Value = strval(inputtext);

			if (Value < 0 || Value > 100)
			{
				SendErrorMessage(playerid, "Current or total rounds can only be between 0 and 100.");
				ShowPlayerDialog(
					playerid, DIALOG_CURRENT_TOTAL, DIALOG_STYLE_INPUT, "" COL_PRIM "Rounds Dialog", "" COL_PRIM "Enter current round or total rounds to be played:", "Current",
					"Total");
				return 1;
			}

			new iString[144];

			if (response)
			{
				CurrentRound = Value;
				format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has changed the current round to: {FFFFFF}%d", Player[playerid][Name], CurrentRound);
				SendClientMessageToAll(-1, iString);
			}
			else
			{
				TotalRounds = Value;
				format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has changed the total rounds to: {FFFFFF}%d", Player[playerid][Name], TotalRounds);
				SendClientMessageToAll(-1, iString);
			}
			UpdateRoundsPlayedTextDraw();
			return 1;
		}
		case DIALOG_TEAM_SCORE:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:
					{
						ShowPlayerDialog(
							playerid, DIALOG_ATT_NAME, DIALOG_STYLE_INPUT, "" COL_PRIM "Attacker Team Name", "" COL_PRIM "Enter {FFFFFF}Attacker " COL_PRIM "Team Name Below:", "Next",
							"Close");
					}
					case 1:
					{
						ShowPlayerDialog(playerid, DIALOG_ATT_SCORE, DIALOG_STYLE_INPUT, "" COL_PRIM "Attacker Team Score", va_return(COL_PRIM "Enter {FFFFFF}%s " COL_PRIM "Team Score Below:", TeamName[ATTACKER]), "Next", "Close");
					}
					case 2:
					{
						TeamScore[ATTACKER] = 0;
						TeamScore[DEFENDER] = 0;
						CurrentRound		= 0;

						UpdateTeamScoreTextDraw();
						UpdateRoundsPlayedTextDraw();
						UpdateTeamNameTextDraw();

						UpdateTeamNamesTextdraw();

						ClearPlayerVariables();

						foreach (new i : Player)
						{
							Player[i][TotalKills]		 = 0;
							Player[i][TotalDeaths]		 = 0;
							Player[i][TotalDamage]		 = 0.0;
							Player[i][RoundPlayed]		 = 0;
							Player[i][TotalBulletsFired] = 0;
							Player[i][TotalshotsHit]	 = 0;
						}

						SendClientMessageToAll(-1, va_return("{FFFFFF}%s " COL_PRIM "has reset the scores.", Player[playerid][Name]));
					}
				}
			}
			return 1;
		}
		case DIALOG_WAR_RESET:
		{
			if (response)
			{
				TeamScore[ATTACKER] = 0;
				TeamScore[DEFENDER] = 0;
				CurrentRound		= 0;

				new DBResult: res	= db_query(sqliteconnection, "SELECT * FROM Configs WHERE Option = 'Total Rounds'");

				new iString[144];

				db_get_field_assoc(res, "Value", iString, sizeof(iString));
				TotalRounds = strval(iString);
				db_free_result(res);

				TeamName[ATTACKER]	   = "Alpha";
				TeamName[ATTACKER_SUB] = "Alpha Sub";
				TeamName[DEFENDER]	   = "Beta";
				TeamName[DEFENDER_SUB] = "Beta Sub";

				UpdateTeamScoreTextDraw();
				UpdateRoundsPlayedTextDraw();
				UpdateTeamNameTextDraw();

				format(iString, sizeof iString, "%sWar Mode: ~r~OFF", MAIN_TEXT_COLOUR);
				TextDrawSetString(WarModeText, iString);

				foreach (new i : Player)
				{
					Player[i][TotalKills]		 = 0;
					Player[i][TotalDeaths]		 = 0;
					Player[i][TotalDamage]		 = 0.0;
					Player[i][RoundPlayed]		 = 0;
					Player[i][TotalBulletsFired] = 0;
					Player[i][TotalshotsHit]	 = 0;
				}

				ClearPlayerVariables();

				HideMatchScoreBoard();

				WarMode = false;

				FixGamemodeText();
				format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has disabled the Match-Mode.", Player[playerid][Name]);
				SendClientMessageToAll(-1, iString);
			}
			return 1;
		}
		case DIALOG_ATT_NAME:
		{
			if (response)
			{
				if (isnull(inputtext))
				{
					ShowPlayerDialog(
						playerid, DIALOG_DEF_NAME, DIALOG_STYLE_INPUT, "" COL_PRIM "Defender Team Name", "" COL_PRIM "Enter {FFFFFF}Defender " COL_PRIM "Team Name Below:", "Ok",
						"Close");
					return 1;
				}
				if (strlen(inputtext) > 6)
				{
					SendErrorMessage(playerid, "Team name is too long.");
					ShowPlayerDialog(
						playerid, DIALOG_ATT_NAME, DIALOG_STYLE_INPUT, "" COL_PRIM "Attacker Team Name", "" COL_PRIM "Enter {FFFFFF}Attacker " COL_PRIM "Team Name Below:", "Next",
						"Close");
					return 1;
				}

				if (strfind(inputtext, "~") != -1)
				{
					return SendErrorMessage(playerid, "~ not allowed.");
				}

				format(TeamName[ATTACKER], 24, inputtext);
				format(TeamName[ATTACKER_SUB], 24, "%s Sub", TeamName[ATTACKER]);

				UpdateTeamScoreTextDraw();
				UpdateRoundsPlayedTextDraw();
				UpdateTeamNameTextDraw();

				UpdateTeamNamesTextdraw();

				new iString[144];
				format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has set attacker team name to: {FFFFFF}%s", Player[playerid][Name], TeamName[ATTACKER]);
				SendClientMessageToAll(-1, iString);

				ShowPlayerDialog(
					playerid, DIALOG_DEF_NAME, DIALOG_STYLE_INPUT, "" COL_PRIM "Defender Team Name", "" COL_PRIM "Enter {FFFFFF}Defender " COL_PRIM "Team Name Below:", "Ok", "Close");
			}
			return 1;
		}
		case DIALOG_DEF_NAME:
		{
			if (response)
			{
				if (isnull(inputtext))
					return 1;
				if (strlen(inputtext) > 6)
				{
					SendErrorMessage(playerid, "Team name is too long.");
					ShowPlayerDialog(
						playerid, DIALOG_DEF_NAME, DIALOG_STYLE_INPUT, "" COL_PRIM "Defender Team Name", "" COL_PRIM "Enter {FFFFFF}Defender " COL_PRIM "Team Name Below:", "Ok",
						"Close");
					return 1;
				}

				if (strfind(inputtext, "~") != -1)
				{
					return SendErrorMessage(playerid, "~ not allowed.");
				}

				format(TeamName[DEFENDER], 24, inputtext);
				format(TeamName[DEFENDER_SUB], 24, "%s Sub", TeamName[DEFENDER]);

				UpdateTeamScoreTextDraw();
				UpdateRoundsPlayedTextDraw();
				UpdateTeamNameTextDraw();

				UpdateTeamNamesTextdraw();

				new iString[144];
				format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has set defender team name to: {FFFFFF}%s", Player[playerid][Name], TeamName[DEFENDER]);
				SendClientMessageToAll(-1, iString);

				WarMode = true;

				format(iString, sizeof iString, "%sWar Mode: ~r~ON", MAIN_TEXT_COLOUR);
				TextDrawSetString(WarModeText, iString);

				ShowMatchScoreBoard();
			}
			return 1;
		}
		case DIALOG_ATT_SCORE:
		{
			if (response)
			{
				new iString[128];
				if (isnull(inputtext))
				{
					format(iString, sizeof(iString), "" COL_PRIM "Enter {FFFFFF}%s " COL_PRIM "Team Score Below:", TeamName[DEFENDER]);
					ShowPlayerDialog(playerid, DIALOG_DEF_SCORE, DIALOG_STYLE_INPUT, "" COL_PRIM "Defender Team Score", iString, "Ok", "Close");
					return 1;
				}
				if (!IsNumeric(inputtext))
				{
					SendErrorMessage(playerid, "Score can only be numerical.");
					format(iString, sizeof(iString), "" COL_PRIM "Enter {FF3333}%s " COL_PRIM "Team Score Below:", TeamName[ATTACKER]);
					ShowPlayerDialog(playerid, DIALOG_ATT_SCORE, DIALOG_STYLE_INPUT, "" COL_PRIM "Attacker Team Score", iString, "Next", "Close");
					return 1;
				}
				new Score = strval(inputtext);

				if (Score < 0 || Score > 100)
				{
					SendErrorMessage(playerid, "Score can only be between 0 and 100.");
					format(iString, sizeof(iString), "" COL_PRIM "Enter {FF3333}%s " COL_PRIM "Team Score Below:", TeamName[ATTACKER]);
					ShowPlayerDialog(playerid, DIALOG_ATT_SCORE, DIALOG_STYLE_INPUT, "" COL_PRIM "Attacker Team Score", iString, "Next", "Close");
					return 1;
				}

				if ((Score + TeamScore[DEFENDER]) >= TotalRounds)
				{
					SendErrorMessage(playerid, "Attacker plus defender score is bigger than or equal to total rounds.");
					format(iString, sizeof(iString), "" COL_PRIM "Enter {FFFFFF}%s " COL_PRIM "Team Score Below:", TeamName[ATTACKER]);
					ShowPlayerDialog(playerid, DIALOG_ATT_SCORE, DIALOG_STYLE_INPUT, "" COL_PRIM "Attacker Team Score", iString, "Next", "Close");
					return 1;
				}

				TeamScore[ATTACKER] = Score;
				CurrentRound		= TeamScore[ATTACKER] + TeamScore[DEFENDER];

				format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has set attacker team score to: {FFFFFF}%d", Player[playerid][Name], TeamScore[ATTACKER]);
				SendClientMessageToAll(-1, iString);

				UpdateTeamScoreTextDraw();
				UpdateRoundsPlayedTextDraw();
				UpdateTeamNameTextDraw();

				format(iString, sizeof(iString), "" COL_PRIM "Enter {FFFFFF}%s " COL_PRIM "Team Score Below:", TeamName[DEFENDER]);
				ShowPlayerDialog(playerid, DIALOG_DEF_SCORE, DIALOG_STYLE_INPUT, "" COL_PRIM "Defender Team Score", iString, "Ok", "Close");
			}
			return 1;
		}
		case DIALOG_DEF_SCORE:
		{
			if (response)
			{
				if (isnull(inputtext))
					return 1;

				new iString[128];
				if (!IsNumeric(inputtext))
				{
					SendErrorMessage(playerid, "Score can only be numerical.");
					format(iString, sizeof(iString), "" COL_PRIM "Enter {FFFFFF}%s " COL_PRIM "Team Score Below:", TeamName[DEFENDER]);
					ShowPlayerDialog(playerid, DIALOG_DEF_SCORE, DIALOG_STYLE_INPUT, "" COL_PRIM "Defender Team Score", iString, "Ok", "Close");
					return 1;
				}

				new Score = strval(inputtext);

				if (Score < 0 || Score > 100)
				{
					SendErrorMessage(playerid, "Score can only be between 0 and 100.");
					format(iString, sizeof(iString), "" COL_PRIM "Enter {FFFFFF}%s " COL_PRIM "Team Score Below:", TeamName[DEFENDER]);
					ShowPlayerDialog(playerid, DIALOG_DEF_SCORE, DIALOG_STYLE_INPUT, "" COL_PRIM "Defender Team Score", iString, "Ok", "Close");
					return 1;
				}

				if ((TeamScore[ATTACKER] + Score) >= TotalRounds)
				{
					SendErrorMessage(playerid, "Attacker plus defender score is bigger than or equal to total rounds.");
					format(iString, sizeof(iString), "" COL_PRIM "Enter {FFFFFF}%s " COL_PRIM "Team Score Below:", TeamName[DEFENDER]);
					ShowPlayerDialog(playerid, DIALOG_DEF_SCORE, DIALOG_STYLE_INPUT, "" COL_PRIM "Defender Team Score", iString, "Ok", "Close");
					return 1;
				}
				TeamScore[DEFENDER] = Score;
				CurrentRound		= TeamScore[ATTACKER] + TeamScore[DEFENDER];

				format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has set defender team score to: {FFFFFF}%d", Player[playerid][Name], TeamScore[DEFENDER]);
				SendClientMessageToAll(-1, iString);

				UpdateTeamScoreTextDraw();
				UpdateRoundsPlayedTextDraw();
				UpdateTeamNameTextDraw();
			}
			return 1;
		}
		case DIALOG_CONFIG_SET_GA:
		{
			if (!response)
				return ShowConfigDialog(playerid);
			switch (listitem)
			{
				case 0:
				{
					ShowPlayerDialog(
						playerid, DIALOG_CONFIG_SET_GA_ALPHA, DIALOG_STYLE_INPUT, "" COL_PRIM "ALPHA PASSWORD", "" COL_PRIM "Set the password or leave empty to clear:", "OK",
						"Cancel");
				}
				case 1:
				{
					ShowPlayerDialog(
						playerid, DIALOG_CONFIG_SET_GA_BETA, DIALOG_STYLE_INPUT, "" COL_PRIM "BETA PASSWORD", "" COL_PRIM "Set the password or leave empty to clear:", "OK", "Cancel");
				}
				case 2:
				{
					ShowPlayerDialog(
						playerid, DIALOG_CONFIG_SET_GA_REF, DIALOG_STYLE_INPUT, "" COL_PRIM "REFEREE PASSWORD", "" COL_PRIM "Set the password or leave empty to clear:", "OK",
						"Cancel");
				}
				case 3:
				{
					ShowPlayerDialog(
						playerid, DIALOG_CONFIG_SET_GA_ASUB, DIALOG_STYLE_INPUT, "" COL_PRIM "ALPHA SUB PASSWORD", "" COL_PRIM "Set the password or leave empty to clear:", "OK",
						"Cancel");
				}
				case 4:
				{
					ShowPlayerDialog(
						playerid, DIALOG_CONFIG_SET_GA_BSUB, DIALOG_STYLE_INPUT, "" COL_PRIM "BETA SUB PASSWORD", "" COL_PRIM "Set the password or leave empty to clear:", "OK",
						"Cancel");
				}
			}
			return 1;
		}
		case DIALOG_CONFIG_SET_GA_ALPHA:
		{
			if (!response)
				return ShowConfigDialog(playerid);
			if (strlen(inputtext) > MAX_GROUP_ACCESS_PASSWORD_LENGTH)
			{
				SendErrorMessage(playerid, "The password you entered is quite long. Try again with a shorter one!", MSGBOX_TYPE_BOTTOM);
				return ShowConfigDialog(playerid);
			}
			format(GroupAccessPassword[0], MAX_GROUP_ACCESS_PASSWORD_LENGTH, "%s", inputtext);
			new str[128];
			format(str, sizeof(str), "%s " COL_PRIM "has changed the alpha group access", Player[playerid][Name]);
			SendClientMessageToAll(-1, str);
			return ShowConfigDialog(playerid);
		}
		case DIALOG_CONFIG_SET_GA_BETA:
		{
			if (!response)
				return ShowConfigDialog(playerid);
			if (strlen(inputtext) > MAX_GROUP_ACCESS_PASSWORD_LENGTH)
			{
				SendErrorMessage(playerid, "The password you entered is quite long. Try again with a shorter one!", MSGBOX_TYPE_BOTTOM);
				return ShowConfigDialog(playerid);
			}
			format(GroupAccessPassword[1], MAX_GROUP_ACCESS_PASSWORD_LENGTH, "%s", inputtext);
			new str[128];
			format(str, sizeof(str), "%s " COL_PRIM "has changed the beta group access", Player[playerid][Name]);
			SendClientMessageToAll(-1, str);
			return ShowConfigDialog(playerid);
		}
		case DIALOG_CONFIG_SET_GA_REF:
		{
			if (!response)
				return ShowConfigDialog(playerid);
			if (strlen(inputtext) > MAX_GROUP_ACCESS_PASSWORD_LENGTH)
			{
				SendErrorMessage(playerid, "The password you entered is quite long. Try again with a shorter one!", MSGBOX_TYPE_BOTTOM);
				return ShowConfigDialog(playerid);
			}
			format(GroupAccessPassword[2], MAX_GROUP_ACCESS_PASSWORD_LENGTH, "%s", inputtext);
			new str[128];
			format(str, sizeof(str), "%s " COL_PRIM "has changed the referee group access", Player[playerid][Name]);
			SendClientMessageToAll(-1, str);
			return ShowConfigDialog(playerid);
		}
		case DIALOG_CONFIG_SET_GA_ASUB:
		{
			if (!response)
				return ShowConfigDialog(playerid);
			if (strlen(inputtext) > MAX_GROUP_ACCESS_PASSWORD_LENGTH)
			{
				SendErrorMessage(playerid, "The password you entered is quite long. Try again with a shorter one!", MSGBOX_TYPE_BOTTOM);
				return ShowConfigDialog(playerid);
			}
			format(GroupAccessPassword[3], MAX_GROUP_ACCESS_PASSWORD_LENGTH, "%s", inputtext);
			new str[128];
			format(str, sizeof(str), "%s " COL_PRIM "has changed the alpha sub group access", Player[playerid][Name]);
			SendClientMessageToAll(-1, str);
			return ShowConfigDialog(playerid);
		}
		case DIALOG_CONFIG_SET_GA_BSUB:
		{
			if (!response)
				return ShowConfigDialog(playerid);
			if (strlen(inputtext) > MAX_GROUP_ACCESS_PASSWORD_LENGTH)
			{
				SendErrorMessage(playerid, "The password you entered is quite long. Try again with a shorter one!", MSGBOX_TYPE_BOTTOM);
				return ShowConfigDialog(playerid);
			}
			format(GroupAccessPassword[4], MAX_GROUP_ACCESS_PASSWORD_LENGTH, "%s", inputtext);
			new str[128];
			format(str, sizeof(str), "%s " COL_PRIM "has changed the beta sub group access", Player[playerid][Name]);
			SendClientMessageToAll(-1, str);
			return ShowConfigDialog(playerid);
		}
		case DIALOG_GROUPACCESS:
		{
			if (!response)
			{
				if (!Player[playerid][Spawned])
				{
					ShowPlayerClassSelection(playerid);
				}
				return 1;
			}
			new groupID = Player[playerid][RequestedClass];

			if (strcmp(inputtext, GroupAccessPassword[groupID]) != 0 || strlen(inputtext) == 0)
			{
				return ShowPlayerDialog(
					playerid, DIALOG_GROUPACCESS, DIALOG_STYLE_INPUT, "Authorization required", "Wrong password.\n\nPlease enter the group password:", "Submit", "Cancel");
			}
			if (Player[playerid][Spawned])
			{
				switch (Player[playerid][RequestedClass])
				{
					case 0:
					{
						SetPlayerColor(playerid, ATTACKER_NOT_PLAYING);
						Player[playerid][Team] = ATTACKER;
					}
					case 1:
					{
						SetPlayerColor(playerid, DEFENDER_NOT_PLAYING);
						Player[playerid][Team] = DEFENDER;
					}
					case 2:
					{
						SetPlayerColor(playerid, REFEREE_COLOR);
						Player[playerid][Team] = REFEREE;
					}
					case 3:
					{
						SetPlayerColor(playerid, ATTACKER_SUB_COLOR);
						Player[playerid][Team] = ATTACKER_SUB;
					}

					case 4:
					{
						SetPlayerColor(playerid, DEFENDER_SUB_COLOR);
						Player[playerid][Team] = DEFENDER_SUB;
					}
				}
				SwitchTeamFix(playerid);
			}
			else
			{
				RequestedGroupPass[playerid][groupID] = "";
				SpawnConnectedPlayer(playerid, groupID + 1);
			}
			return 1;
		}
		case DIALOG_CONFIG_SET_TEAM_SKIN:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, "/teamskin 0");
					}
					case 1:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, "/teamskin 1");
					}
					case 2:
					{
						CallLocalFunction("OnPlayerCommandText", "ds", playerid, "/teamskin 2");
					}
				}
			}
			else
			{
				ShowConfigDialog(playerid);
			}
			return 1;
		}
		case DIALOG_CONFIG_SET_AAD:
		{
			if (response)
			{
				switch (listitem)
				{
					case 0:
					{ // set round health
						ShowPlayerDialog(playerid, DIALOG_CONFIG_SET_ROUND_HEALTH, DIALOG_STYLE_INPUT, "" COL_PRIM "Round Health", "" COL_PRIM "Set round health:", "OK", "");
					}
					case 1:
					{ // set round armour
						ShowPlayerDialog(playerid, DIALOG_CONFIG_SET_ROUND_ARMOUR, DIALOG_STYLE_INPUT, "" COL_PRIM "Round Armour", "" COL_PRIM "Set round armour:", "OK", "");
					}
					case 2:
					{ // Round time
						ShowPlayerDialog(playerid, DIALOG_CONFIG_SET_ROUND_TIME, DIALOG_STYLE_INPUT, "" COL_PRIM "Round Time", "" COL_PRIM "Set round time:", "OK", "Cancel");
					}
					case 3:
					{ // CP time
						ShowPlayerDialog(playerid, DIALOG_CONFIG_SET_CP_TIME, DIALOG_STYLE_INPUT, "" COL_PRIM "CP Time", "" COL_PRIM "Set CP time:", "OK", "Cancel");
					}
				}
			}
			else
			{
				ShowConfigDialog(playerid);
			}
			return 1;
		}
		case DIALOG_CONFIG_SET_ROUND_HEALTH:
		{
			new hp = strval(inputtext);
			if (hp <= 0 || hp > 100)
			{
				SendErrorMessage(playerid, "Health value can be between 0 and 100 maximum.");
				ShowPlayerDialog(playerid, DIALOG_CONFIG_SET_ROUND_HEALTH, DIALOG_STYLE_INPUT, "" COL_PRIM "Round Health", "" COL_PRIM "Set round health:", "OK", "");
				return 1;
			}

			RoundHP = hp;

			new str[128];
			format(str, sizeof(str), "%s " COL_PRIM "has changed the round health to: {FFFFFF}%d", Player[playerid][Name], RoundHP);
			SendClientMessageToAll(-1, str);

			format(str, sizeof(str), "UPDATE `Configs` SET `Value` = '%d,%d' WHERE `Option` = 'RoundHPAR'", RoundHP, RoundAR);
			db_free_result(db_query(sqliteconnection, str));

			ShowConfigDialog(playerid);
			return 1;
		}
		case DIALOG_CONFIG_SET_ROUND_ARMOUR:
		{
			new hp = strval(inputtext);
			if (hp <= 0 || hp > 100)
			{
				SendErrorMessage(playerid, "Armour value can be between 0 and 100 maximum.");
				ShowPlayerDialog(playerid, DIALOG_CONFIG_SET_ROUND_ARMOUR, DIALOG_STYLE_INPUT, "" COL_PRIM "Round Armour", "" COL_PRIM "Set round armour:", "OK", "");
				return 1;
			}

			RoundAR = hp;

			new str[128];
			format(str, sizeof(str), "%s " COL_PRIM "has changed the round armour to: {FFFFFF}%d", Player[playerid][Name], RoundAR);
			SendClientMessageToAll(-1, str);

			format(str, sizeof(str), "UPDATE `Configs` SET `Value` = '%d,%d' WHERE `Option` = 'RoundHPAR'", RoundHP, RoundAR);
			db_free_result(db_query(sqliteconnection, str));

			ShowConfigDialog(playerid);
			return 1;
		}
		case DIALOG_CONFIG_SET_ROUND_TIME:
		{
			if (response)
			{
				CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/roundtime %s", inputtext));
				ShowConfigDialog(playerid);
			}
			else
			{
				ShowConfigDialog(playerid);
			}
			return 1;
		}
		case DIALOG_CONFIG_SET_CP_TIME:
		{
			if (response)
			{
				CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/cptime %s", inputtext));
				ShowConfigDialog(playerid);
			}
			else
			{
				ShowConfigDialog(playerid);
			}
			return 1;
		}
		case DIALOG_CONFIG_SET_MAX_PING:
		{
			if (response)
			{
				CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/maxping %s", inputtext));
				ShowConfigDialog(playerid);
			}
			else
			{
				ShowConfigDialog(playerid);
			}
			return 1;
		}
		case DIALOG_CONFIG_SET_MAX_PACKET:
		{
			if (response)
			{
				CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/maxpacket %s", inputtext));
				ShowConfigDialog(playerid);
			}
			else
			{
				ShowConfigDialog(playerid);
			}
			return 1;
		}
		case DIALOG_CONFIG_SET_MIN_FPS:
		{
			if (response)
			{
				CallLocalFunction("OnPlayerCommandText", "ds", playerid, va_return("/minfps %s", inputtext));
				ShowConfigDialog(playerid);
			}
			else
			{
				ShowConfigDialog(playerid);
			}
			return 1;
		}
		case DIALOG_SWITCH_TEAM:
		{
			if (response)
			{
				new groupID = listitem;
				if (strlen(GroupAccessPassword[groupID]) > 0
					&& (strcmp(RequestedGroupPass[playerid][groupID], GroupAccessPassword[groupID]) != 0 || isnull(RequestedGroupPass[playerid][groupID])))
				{
					Player[playerid][RequestedClass] = listitem;
					ShowPlayerDialog(playerid, DIALOG_GROUPACCESS, DIALOG_STYLE_INPUT, "Authorization required", "Please enter the group password:", "Submit", "Cancel");
					return 1;
				}
				switch (listitem)
				{
					case 0:
					{
						SetPlayerColor(playerid, ATTACKER_NOT_PLAYING);
						Player[playerid][Team] = ATTACKER;
					}
					case 1:
					{
						SetPlayerColor(playerid, DEFENDER_NOT_PLAYING);
						Player[playerid][Team] = DEFENDER;
					}
					case 2:
					{
						SetPlayerColor(playerid, REFEREE_COLOR);
						Player[playerid][Team] = REFEREE;
					}
					case 3:
					{
						SetPlayerColor(playerid, ATTACKER_SUB_COLOR);
						Player[playerid][Team] = ATTACKER_SUB;
					}

					case 4:
					{
						SetPlayerColor(playerid, DEFENDER_SUB_COLOR);
						Player[playerid][Team] = DEFENDER_SUB;
					}
				}
				SwitchTeamFix(playerid);
			}
			return 1;
		}
		case DIALOG_TEAM_SELECTION:
		{
			if (response)
			{
				if (listitem > 0) // Not auto-assign
				{
					new groupID = listitem - 1;
					if (strlen(GroupAccessPassword[groupID]) > 0
						&& (strcmp(RequestedGroupPass[playerid][groupID], GroupAccessPassword[groupID]) != 0 || isnull(RequestedGroupPass[playerid][groupID])))
					{
						Player[playerid][RequestedClass] = listitem;
						ShowPlayerDialog(playerid, DIALOG_GROUPACCESS, DIALOG_STYLE_INPUT, "Authorization required", "Please enter the group password:", "Submit", "Cancel");
						return 1;
					}
				}
				SpawnConnectedPlayer(playerid, listitem);
			}
			else
			{
				ShowPlayerClassSelection(playerid);
			}
			return 1;
		}
		case DIALOG_ROUND_TD_STYLE:
		{
			if (!response)
				return 1;

			HideRoundStats(playerid);

			Player[playerid][RoundTDStyle] = listitem;
			db_free_result(db_query(sqliteconnection, va_return("UPDATE `Players` SET `RoundTDStyle`=%d WHERE `Name`='%q'", Player[playerid][RoundTDStyle], Player[playerid][Name])));

			switch (Player[playerid][RoundTDStyle])
			{
				case 0: SendClientMessage(playerid, -1, "You have switched round textdraws style to: Modern");
				case 1: SendClientMessage(playerid, -1, "You have switched round textdraws style to: Bulletproof");
				case 2: SendClientMessage(playerid, -1, "You have switched round textdraws style to: Simple");
			}

			if (Current != -1)
				ShowRoundStats(playerid);
			return 1;
		}
	}
	return 1;
}
