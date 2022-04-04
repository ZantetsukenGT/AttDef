#if defined _attdef_OnPText
	#endinput
#endif
#define _attdef_OnPText

public OnPlayerText(playerid, text[])
{
	new currentTick = GetTickCount();
	// Anti spam
	if (AntiSpam && currentTick - Player[playerid][lastChat] < 500)
	{
		SendErrorMessage(playerid, "Please wait.");
		return 0;
	}
	Player[playerid][lastChat] = currentTick;

	// Team Chat
	if (text[0] == '!')
	{
		new ChatColor;
		switch (Player[playerid][Team])
		{
			case REFEREE: ChatColor = 0xFFFF90FF;
			case DEFENDER: ChatColor = 0x0088FFFF;
			case ATTACKER: ChatColor = 0xFF2040FF;
			case ATTACKER_SUB: ChatColor = ATTACKER_SUB_COLOR;
			case DEFENDER_SUB: ChatColor = DEFENDER_SUB_COLOR;
			case NON:
			{
				SendErrorMessage(playerid, "You must be part of a team.");
				return 0;
			}
		}
		new ChatString[144];
		format(ChatString, sizeof(ChatString), "@ Team Chat | %s (%d) | %s", Player[playerid][Name], playerid, text[1]);

		foreach (new i : Player)
		{
			if (Player[i][Team] != NON)
			{
				if ((Player[playerid][Team] == ATTACKER || Player[playerid][Team] == ATTACKER_SUB) && (Player[i][Team] == ATTACKER || Player[i][Team] == ATTACKER_SUB))
				{
					SendClientMessage(i, ChatColor, ChatString);
					PlayerPlaySound(i, 1137, 0.0, 0.0, 0.0);
				}
				if ((Player[playerid][Team] == DEFENDER || Player[playerid][Team] == DEFENDER_SUB) && (Player[i][Team] == DEFENDER || Player[i][Team] == DEFENDER_SUB))
				{
					SendClientMessage(i, ChatColor, ChatString);
					PlayerPlaySound(i, 1137, 0.0, 0.0, 0.0);
				}
				if (Player[playerid][Team] == REFEREE && Player[i][Team] == REFEREE && !Player[i][InDuel])
				{
					SendClientMessage(i, ChatColor, ChatString);
					PlayerPlaySound(i, 1137, 0.0, 0.0, 0.0);
				}
			}
		}
		return 0;
	}

	// Admin chat
	if (text[0] == '@' && Player[playerid][Level] > 0)
	{
		new ChatString[144];
		format(ChatString, sizeof(ChatString), "@ Admin Chat | %s (%d) | %s", Player[playerid][Name], playerid, text[1]);
		foreach (new i : Player)
		{
			if (Player[i][Level] > 0)
			{
				SendClientMessage(i, 0x66CC66FF, ChatString);
				PlayerPlaySound(i, 1137, 0.0, 0.0, 0.0);
			}
		}
		return 0;
	}

	// Channel chat
	if (text[0] == '^' && Player[playerid][ChatChannel] != -1)
	{
		new ChatString[144];
		format(ChatString, sizeof(ChatString), "@ Channel Chat | %s | {FFFFFF}%d{FFCC99} | %s", Player[playerid][Name], Player[playerid][ChatChannel], text[1]);

		foreach (new i : Player)
		{
			if (Player[i][ChatChannel] == Player[playerid][ChatChannel])
			{
				SendClientMessage(i, 0xFFCC99FF, ChatString);
				PlayerPlaySound(i, 1137, 0.0, 0.0, 0.0);
			}
		}
		return 0;
	}

	if (ChatDisabled)
	{
		SendErrorMessage(playerid, "Main chat is currently disabled.");
		return 0;
	}
	if (Player[playerid][Mute])
	{
		SendErrorMessage(playerid, "You are muted.");
		return 0;
	}

	// Main chat
	new ChatString[144];
	format(ChatString, sizeof(ChatString), "%s%s: {FFFFFF}(%d) %s", GetColor(GetPlayerColor(playerid)), Player[playerid][Name], playerid, text);
	SendClientMessageToAll(-1, ChatString);
	return 0;
}
