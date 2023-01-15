#if defined fake_ping_included_
	#endinput
#endif
#define fake_ping_included_

#include <Pawn.RakNet>
#include <YSI_Coding\y_hooks>

static const UPDATE_SCORES_PINGS = 155;
static s_FakePing[MAX_PLAYERS];
static s_LastUpdateTick;

hook OnScriptInit()
{
	s_LastUpdateTick = GetTickCount() - 3001;
	return 1;
}

static UpdateFakePings()
{
	for (new i = 0, limit = Iter_Count(Player); i < limit; i++) { s_FakePing[i] = RandomMinMax(0, 0x10000) | 0x4000; }
}

ORPC:UPDATE_SCORES_PINGS(playerid, BitStream: bs)
{
	new current = GetTickCount();
	if (current - s_LastUpdateTick > 3000)
	{
		s_LastUpdateTick = current;
		UpdateFakePings();
	}
	new originalWO;
	BS_GetWriteOffset(bs, originalWO);
	for (new i = 0, limit = originalWO / 80; i < limit; ++i)
	{
		BS_SetWriteOffset(bs, 80 * i + 48); // ping offset, ignore player_id and score
		BS_WriteUint16(bs, s_FakePing[i]);
	}
	BS_SetWriteOffset(bs, originalWO);
	return 1;
}
