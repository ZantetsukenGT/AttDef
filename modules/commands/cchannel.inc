#if defined _attdef_cmd_cchannel
	#endinput
#endif
#define _attdef_cmd_cchannel

YCMD: cchannel(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "enable you to join a chat channel.");
	new Channel;
	if (sscanf(params, "i", Channel))
	{
		if (Player[playerid][ChatChannel] == -1)
			return SendUsageMessage(playerid, "/cchannel [Channel ID]");

		return va_SendClientMessage(playerid, -1, COL_PRIM "Current chat channel ID: {FFFFFF}%d" COL_PRIM ". To join another one use /cchannel [Channel ID]", Player[playerid][ChatChannel]);
	}

	if (Channel < -1)
		return SendErrorMessage(playerid, "Invalid channel ID (Disable: -1, Min: 0, Max: " #MAX_CHANNELS ")");

	if (Player[playerid][ChatChannel] == Channel)
	{
		if (Channel == -1)
			return SendErrorMessage(playerid, "You are not in any chat channel.");
		return SendErrorMessage(playerid, "You are already in this chat channel ID.");
	}

	new previousChannel			  = Player[playerid][ChatChannel];
	Player[playerid][ChatChannel] = Channel;

	db_free_result(db_query(sqliteconnection, va_return("UPDATE Players SET ChatChannel = %d WHERE Name = '%q'", Channel, Player[playerid][Name])));

	new str[144];
	if (previousChannel != -1)
	{
		format(str, sizeof(str), "%s " COL_PRIM "has left your {FFFFFF}chat channel" COL_PRIM ".", Player[playerid][Name]);
		foreach (new i : Player)
		{
			if (Player[i][ChatChannel] == previousChannel && playerid != i)
				SendClientMessage(i, -1, str);
		}
	}
	if (Channel == -1)
		return SendClientMessage(playerid, -1, COL_PRIM "You've exited from chat channels, to join another one channel, type {FFFFFF}/cchannel" COL_PRIM ".");

	format(str, sizeof(str), "%s " COL_PRIM "has joined your {FFFFFF}chat channel" COL_PRIM ".", Player[playerid][Name]);
	foreach (new i : Player)
	{
		if (Player[i][ChatChannel] == Channel && playerid != i)
			SendClientMessage(i, -1, str);
	}

	format(str, sizeof(str), COL_PRIM "You've joined the chat channel ID: {FFFFFF}%d" COL_PRIM ", to know who else is here, type {FFFFFF}/pchannel" COL_PRIM ". Use ^ symbol to chat!", Channel);
	return SendClientMessage(playerid, -1, str);
}
