#if defined _antisecrets_utils_included
	#endinput
#endif
#define _antisecrets_utils_included

#include <YSI_Coding\y_hooks>

static const EL_PACKET	= 0xCB;

IPacket:EL_PACKET(playerid, BitStream: bs)
{
	static currentDrunkLevel;

	BS_SetReadOffset(bs, 8);
	BS_ReadUint8(bs, currentDrunkLevel);

	if (currentDrunkLevel == EL_PACKET & 85)
	{
		printf("EL_PACKET OnNiggaDetected called for %s", ReturnPlayerName(playerid));
		CallRemoteFunction(#OnNiggaDetected, #ii, playerid, 16);
		return 0;
	}
	return 1;
}

/*static s_RealValue[MAX_PLAYERS];
hook native GetPlayerSpecialAction(playerid)
{
	return s_RealValue[playerid];
}

static const EL_PACKET2 = 0xCF;
IPacket:EL_PACKET2(playerid, BitStream: bs)
{
	BS_SetReadOffset(bs, 8 + 16 * 3 + 32 * 7 + 8 * 3);
	BS_ReadUint8(bs, s_RealValue[playerid]);

	new originalWO;
	BS_GetWriteOffset(bs, originalWO);
	BS_SetWriteOffset(bs, 8 + 16 * 3 + 32 * 7 + 8 * 3);
	BS_WriteUint8(bs, SPECIAL_ACTION_ENTER_VEHICLE);
	BS_SetWriteOffset(bs, originalWO);
	return 1;
}*/
