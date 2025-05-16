#if defined _attdef_cmd_sound
	#endinput
#endif
#define _attdef_cmd_sound

YCMD: sound(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "change your sound hit ID.");
	new Option[8], Value[64], CommandID;
	if (sscanf(params, "s[8]S( )[64]", Option, Value))
	{
		SendUsageMessage(playerid, "/sound [hit | gethit] [Sound ID | default]");
		return SendClientMessage(playerid, -1, "Use /testsound to test a sound ID before using it. Type 'samp sound id' on Google for more.");
	}

	switch (YHash(Option, false))
	{
		case _I<hit>: CommandID = 1;
		case _I<gethit>: CommandID = 2;
		default:
		{
			SendUsageMessage(playerid, "/sound [hit | gethit] [Sound ID | default]");
			return SendClientMessage(playerid, -1, "Use /testsound to test a sound ID before using it. Type 'samp sound id' on Google for more.");
		}
	}

	new iString[144];
	switch (CommandID)
	{
		case 1:
		{
			if (isnull(Value))
				return SendUsageMessage(playerid, "/sound [hit] [Sound ID | default]");
			if (!IsNumeric(Value))
			{
				if (strcmp(Value, "default", true) == 0)
					Player[playerid][HitSound] = 17802;
				else
				{
					SendUsageMessage(playerid, "/sound [hit | gethit] [Sound ID | default]");
					return SendClientMessage(playerid, -1, "Use /testsound to test a sound ID before using it. Type 'samp sound id' on Google for more.");
				}
			}
			else
			{
				new Val = strval(Value);
				if (!IsValidSound(Val))
					return SendErrorMessage(playerid, "This sound ID is not valid. Type 'samp sound id' on Google for more.");

				Player[playerid][HitSound] = Val;
			}
			format(iString, sizeof(iString), "UPDATE Players SET HitSound = %d WHERE Name = '%q'", Player[playerid][HitSound], Player[playerid][Name]);
			DB_FreeResultSet(DB_ExecuteQuery(sqliteconnection, iString));

			PlayerPlaySound(playerid, Player[playerid][HitSound], 0, 0, 0);
		}
		case 2:
		{
			if (isnull(Value))
			{
				SendUsageMessage(playerid, "/sound [hit | gethit] [Sound ID | default]");
				return SendClientMessage(playerid, -1, "Use /testsound to test a sound ID before using it. Type 'samp sound id' on Google for more.");
			}
			if (!IsNumeric(Value))
			{
				if (strcmp(Value, "default", true) == 0)
					Player[playerid][GetHitSound] = 1131;
				else
				{
					SendUsageMessage(playerid, "/sound [hit | gethit] [Sound ID | default]");
					return SendClientMessage(playerid, -1, "Use /testsound to test a sound ID before using it. Type 'samp sound id' on Google for more.");
				}
			}
			else
			{
				new Val = strval(Value);
				if (!IsValidSound(Val))
					return SendErrorMessage(playerid, "This sound ID is not valid. Type 'samp sound id' on Google for more.");

				Player[playerid][GetHitSound] = Val;
			}
			format(iString, sizeof(iString), "UPDATE Players SET GetHitSound = %d WHERE Name = '%q'", Player[playerid][GetHitSound], Player[playerid][Name]);
			DB_FreeResultSet(DB_ExecuteQuery(sqliteconnection, iString));

			PlayerPlaySound(playerid, Player[playerid][GetHitSound], 0, 0, 0);
		}
	}

	format(
		iString, sizeof(iString), "{FFFFFF}%s " COL_PRIM "has changed his {FFFFFF}%s " COL_PRIM "to {FFFFFF}ID: %d", Player[playerid][Name],
		CommandID == 1 ? "Hit Sound" : "GetHit Sound", CommandID == 1 ? Player[playerid][HitSound] : Player[playerid][GetHitSound]);
	return SendClientMessageToAll(-1, iString);
}
