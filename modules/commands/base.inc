#if defined _attdef_cmd_base
	#endinput
#endif
#define _attdef_cmd_base

YCMD: base(playerid, params[], help)
{
	//if(Player[playerid][Level] < 5 && !IsPlayerAdmin(playerid)) return SendErrorMessage(playerid,"You need to be level 5 or rcon admin.");
	if (help)
		return SendCommandHelpMessage(playerid, "create a new base.");
	if (Current != -1)
		return SendErrorMessage(playerid, "Can't use this command while round is active.");

	new Params[2][64], BaseName[128], iString[256], CommandID;
	if (sscanf(params, "s[64]S( )[64]S( )[64]", Params[0], Params[1], BaseName))
		return SendUsageMessage(playerid, "/base [create | att | def | cp | name | delete]");

	new usageMessage[28], updateQuery[127], finishedMessage[21];
	switch (YHash(Params[0], false))
	{
		case _I<create>: CommandID = 1;
		case _I<att>:
		{
			strcat(usageMessage, "/base att [Base ID]");
			strcat(updateQuery, "AttSpawn = '%q'");
			strcat(finishedMessage, "Attacker position");
			CommandID = 2;
		}
		case _I<def>:
		{
			strcat(usageMessage, "/base def [Base ID]");
			strcat(updateQuery, "DefSpawn = '%q'");
			strcat(finishedMessage, "Defender position");
			CommandID = 3;
		}
		case _I<cp>:
		{
			strcat(usageMessage, "/base cp [Base ID]");
			strcat(updateQuery, "CPSpawn = '%q', Interior = %d");
			strcat(finishedMessage, "CP/Interior position");
			CommandID = 4;
		}
		case _I<name>:
		{
			strcat(usageMessage, "/base name [Base ID] [Name]");
			strcat(updateQuery, "Name = '%q'");
			strcat(finishedMessage, "base Name");
			CommandID = 5;
		}
		case _I<delete>:
		{
			strcat(usageMessage, "/base delete [Base ID]");
			CommandID = 6;
		}
		default: return SendUsageMessage(playerid, "/base [create | att | def | cp | name | delete]");
	}

	switch (CommandID)
	{
		case 1:
		{
			if (TotalBases > MAX_BASES)
				return SendErrorMessage(playerid, "Too many bases already created. You can use /loadbases to create this base in another set.");

			new BaseID = FindFreeBaseSlot();
			format(iString, sizeof(iString), "INSERT INTO `%q` (ID, AttSpawn, CPSpawn, DefSpawn, Interior, Name) VALUES (%d, 0, 0, 0, 0, 'No Name')", CurrentBaseSet, BaseID);
			db_free_result(db_query(sqliteconnection, iString));

			LoadBases();

			format(
				iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has created base ID: {FFFFFF}%d " COL_PRIM "| in base set: {FFFFFF}%s", Player[playerid][Name], BaseID,
				CurrentBaseSet);
			return SendClientMessageToAll(-1, iString);
		}
	}

	if (isnull(Params[1]) || !IsNumeric(Params[1]))
		return SendUsageMessage(playerid, usageMessage);
	if (CommandID == 5 && isnull(BaseName))
		return SendUsageMessage(playerid, usageMessage);

	new baseid;
	baseid = strval(Params[1]);

	if (baseid > MAX_BASES)
		return SendErrorMessage(playerid, "That base doesn't exist.");
	if (!BExist[baseid])
		return SendErrorMessage(playerid, "That base doesn't exist.");

	// the queries here are already escaped with %q, don't panic if you see a %s
	switch (CommandID)
	{
		case 5: format(iString, sizeof(iString), "UPDATE `%q` SET %s WHERE ID = %d", CurrentBaseSet, va_return(updateQuery, BaseName), baseid);
		case 6:
		{
			format(iString, sizeof(iString), "DELETE FROM `%q` WHERE ID = %d", CurrentBaseSet, baseid);
			db_free_result(db_query(sqliteconnection, iString));

			BExist[baseid] = false;

			LoadBases();

			format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has deleted {FFFFFF}Base ID: %d from base set: %s", Player[playerid][Name], baseid, CurrentBaseSet);
			return SendClientMessageToAll(-1, iString);
		}
		default:
		{
			new Float: P[3],
				CoordenatesXYZ[128];
			GetPlayerPos(playerid, P[0], P[1], P[2]);
			format(CoordenatesXYZ, sizeof(CoordenatesXYZ), "%.0f,%.0f,%.0f", P[0], P[1], P[2]);

			if (CommandID == 4)
				format(iString, sizeof(iString), "UPDATE `%q` SET %s WHERE ID = %d", CurrentBaseSet, va_return(updateQuery, CoordenatesXYZ, GetPlayerInterior(playerid)), baseid);
			else
				format(iString, sizeof(iString), "UPDATE `%q` SET %s WHERE ID = %d", CurrentBaseSet, va_return(updateQuery, CoordenatesXYZ), baseid);
		}
	}
	db_free_result(db_query(sqliteconnection, iString));

	LoadBases();

	format(iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has configured the %s for {FFFFFF}Base ID: %d", Player[playerid][Name], finishedMessage, baseid);
	return SendClientMessageToAll(-1, iString);
}
