#if !defined OPWS_FIX_USE_BSYNC
	#define OPWS_FIX_USE_BSYNC true
#endif

#if OPWS_FIX_USE_BSYNC

#if defined opws_fix_included_
	#endinput
#endif
#define opws_fix_included_

#else

#if defined opws_fix_no_bsync_included_
	#endinput
#endif
#define opws_fix_no_bsync_included_

#endif

// Credits to Boorz for the original concept

#include <Pawn.RakNet>

#if OPWS_FIX_USE_BSYNC
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_hooks>

new Iterator:StreamedFor[MAX_PLAYERS]<MAX_PLAYERS>;

timer DeferredOnScriptInit[0]()
{
	SetServerRule("lagcomp", "Off");
	return 1;
}

hook OnScriptInit()
{
	defer DeferredOnScriptInit();

	Iter_InitAndClear(StreamedFor);
	for (new i = 0; i != MAX_PLAYERS; ++i)
	{
		if (IsPlayerConnected(i))
		{
			for (new j = 0; j != MAX_PLAYERS; ++j)
			{
				if (IsPlayerStreamedIn(i, j))
				{
					Iter_Add(StreamedFor[i], j);
				}
			}
		}
	}
	return 1;
}

hook OnPlayerStreamIn(playerid, forplayerid)
{
	Iter_Add(StreamedFor[playerid], forplayerid);
	return 1;
}

hook OnPlayerStreamOut(playerid, forplayerid)
{
	Iter_Remove(StreamedFor[playerid], forplayerid);
	return 1;
}

// skips: 11 boolean bits, 2 int8, 1 int16, 3 floats, 7 ints32
static const LAGCOMP_WRITE_OFFSET = 11 * 1 + 2 * 8 + 1 * 16 + 3 * 32 + 7 * 32;
static const INITGAME_ORPC		  = 139;
ORPC:INITGAME_ORPC(playerid, BitStream: bs)
{
	PR_SendRPC(bs, playerid, INITGAME_ORPC, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED);

	new originalWO;
	BS_GetWriteOffset(bs, originalWO);
	BS_SetWriteOffset(bs, LAGCOMP_WRITE_OFFSET);

	BS_WriteValue(bs, PR_UINT8, 0);

	BS_SetWriteOffset(bs, originalWO);

	PR_SendRPC(bs, playerid, INITGAME_ORPC, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED);
	CallLocalFunction(#GOOD_OnPlayerConnect, #i, playerid);
	return 0;
}

static const BULLET_SYNC = 206;
static SendBS(playerid, bData[PR_BulletSync])
{
	new BitStream:bs = BS_New();
	BS_WriteValue(
		bs,
		PR_UINT8, BULLET_SYNC,
		PR_UINT16, playerid,
		PR_UINT8, bData[PR_hitType],
		PR_UINT16, bData[PR_hitId],
		PR_FLOAT3, bData[PR_origin],
		PR_FLOAT3, bData[PR_hitPos],
		PR_FLOAT3, bData[PR_offsets],
		PR_UINT8, bData[PR_weaponId]
	);

	foreach (new i : StreamedFor[playerid])
	{
		PR_SendPacket(bs, i);
	}
	BS_Delete(bs);
}

IPacket:BULLET_SYNC(playerid, BitStream: bs)
{
	new bData[PR_BulletSync];
	BS_SetReadOffset(bs, 8);
	BS_ReadBulletSync(bs, bData);

	if (bData[PR_weaponId] == 34)
	{
		// Discard since we will use a different method to send sniper bullet sync packets
		return 0;
	}

	bData[PR_hitType]	 = BULLET_HIT_TYPE_NONE;
	bData[PR_hitId]		 = 0xFFFF;

	// set offsets to whatever hitPos is for `BULLET_HIT_TYPE_NONE` to work
	new Float: fPosX	 = bData[PR_hitPos][0];
	new Float: fPosY	 = bData[PR_hitPos][1];
	new Float: fPosZ	 = bData[PR_hitPos][2];
	bData[PR_offsets][0] = fPosX;
	bData[PR_offsets][1] = fPosY;
	bData[PR_offsets][2] = fPosZ;

	SendBS(playerid, bData);
	return 0;
}
#endif

static s_AimData[MAX_PLAYERS][PR_AimSync];

static const AIM_SYNC = 203;
IPacket:AIM_SYNC(playerid, BitStream: bs)
{
	BS_SetReadOffset(bs, 8);
	BS_ReadAimSync(bs, s_AimData[playerid]);
    if(s_AimData[playerid][PR_camMode] == 7)
	{
		// makes sniper bug notification trigger more reliably
		s_AimData[playerid][PR_camPos][0] += s_AimData[playerid][PR_camFrontVec][0] * 0.42;
		s_AimData[playerid][PR_camPos][1] += s_AimData[playerid][PR_camFrontVec][1] * 0.42;
		s_AimData[playerid][PR_camPos][2] += s_AimData[playerid][PR_camFrontVec][2] * 0.42;
		BS_SetWriteOffset(bs, 8);
		BS_WriteAimSync(bs, s_AimData[playerid]);
	}
	return 1;
}

#if OPWS_FIX_USE_BSYNC
#if !defined WEAPON_SLOT
	#define WEAPON_SLOT: _:
	#define WEAPON_SLOT_LONG_RIFLE 6
#endif

static const WEAPON_SYNC = 204;
IPacket:WEAPON_SYNC(playerid, BitStream: bs)
{
	static sniperAmmo[MAX_PLAYERS] = { 0, ... };
	new weaponData[PR_WeaponsUpdate];

	BS_SetReadOffset(bs, 8);
	BS_ReadWeaponsUpdate(bs, weaponData);

	if (weaponData[PR_slotUpdated][WEAPON_SLOT_LONG_RIFLE] &&
		weaponData[PR_slotWeaponId][WEAPON_SLOT_LONG_RIFLE] == WEAPON_SNIPER)
	{
		if (weaponData[PR_slotWeaponAmmo][WEAPON_SLOT_LONG_RIFLE] == sniperAmmo[playerid] - 1)
		{
			new bData[PR_BulletSync];

			bData[PR_hitType]	 = BULLET_HIT_TYPE_NONE;
			bData[PR_hitId]		 = 0xFFFF;

			new Float: fOriginX	 = s_AimData[playerid][PR_camPos][0];
			new Float: fOriginY	 = s_AimData[playerid][PR_camPos][1];
			new Float: fOriginZ	 = s_AimData[playerid][PR_camPos][2];

			bData[PR_origin][0]	 = fOriginX;
			bData[PR_origin][1]	 = fOriginY;
			bData[PR_origin][2]	 = fOriginZ;

			// set offsets to whatever hitPos is for `BULLET_HIT_TYPE_NONE` to work
			new Float: fPosX	 = fOriginX + s_AimData[playerid][PR_camFrontVec][0] * 300.0;
			new Float: fPosY	 = fOriginY + s_AimData[playerid][PR_camFrontVec][1] * 300.0;
			new Float: fPosZ	 = fOriginZ + s_AimData[playerid][PR_camFrontVec][2] * 300.0;
			bData[PR_hitPos][0]	 = fPosX;
			bData[PR_hitPos][1]	 = fPosY;
			bData[PR_hitPos][2]	 = fPosZ;
			bData[PR_offsets][0] = fPosX;
			bData[PR_offsets][1] = fPosY;
			bData[PR_offsets][2] = fPosZ;

			bData[PR_weaponId]	 = WEAPON_SNIPER;

			SendBS(playerid, bData);
		}
		sniperAmmo[playerid] = weaponData[PR_slotWeaponAmmo][WEAPON_SLOT_LONG_RIFLE];
	}
	return 1;
}
#endif
