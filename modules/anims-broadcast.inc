#if defined anims_broadcast_included_
	#endinput
#endif
#define anims_broadcast_included_

#include <Pawn.RakNet>
#include <YSI_Coding\y_hooks>

static s_LastAnimIndex[MAX_PLAYERS];

static bool: s_IsStunAnimation[GBUG_MAX_ANIMATIONS char] = { false, ... };
static bool: s_IsPreloaded[MAX_PLAYERS char]			 = { false, ... };
static Stun_SetAcceptableRange(min, max)
{
	for (new i = min; i <= max; i++) { s_IsStunAnimation { i } = true; }
}

hook OnScriptInit()
{
	Stun_SetAcceptableRange(1071, 1086); // DAM_ARML_FRMBK ->DAM_STOMACH_FRMRT
	Stun_SetAcceptableRange(1171, 1171); // HITA_2
	Stun_SetAcceptableRange(1173, 1175); // HIT_BACK ->HIT_FRONT
	Stun_SetAcceptableRange(1177, 1178); // HIT_L & HIT_R
	return 1;
}

hook OnPlayerConnect(playerid)
{
	s_IsPreloaded { playerid } = false;
	return 1;
}

hook OnPlayerSpawn(playerid)
{
	if (!s_IsPreloaded { playerid })
	{
		s_IsPreloaded { playerid } = true;
		ApplyAnimation(playerid, "ped", "null", 0.0, 0, 0, 0, 0, 0, 0);
	}
	return 1;
}

stock bool: Stun_IsPlayerStunned(playerid) { return s_IsStunAnimation { s_LastAnimIndex[playerid] }; }

// skips: packetId(8), ControllerState(16 * 3), pos and quats(32 * 7), hp(8), ar(8), weapon(8),
// specialAction(8), speed&surfing(32 * 6), surfingvehicleId(16)
static const ANIM_READ_OFFSET = 8 + 16 * 3 + 32 * 7 + 8 * 4 + 32 * 6 + 16;
static const Anims_FootSync	  = 207;

IPacket:Anims_FootSync(playerid, BitStream: bs)
{
	BS_SetReadOffset(bs, ANIM_READ_OFFSET);

	new animationId;
	BS_ReadUint16(bs, animationId);

	if (s_LastAnimIndex[playerid] != animationId)
	{
		SendClientMessage(playerid, -1, "new anim id %d, previous %d", animationId, s_LastAnimIndex[playerid]);
		s_LastAnimIndex[playerid] = animationId;

		if (Stun_IsPlayerStunned(playerid))
		{
			SendClientMessage(playerid, -1, "sending new anim");
			new animLib[32], animName[32];
			GetAnimationName(animationId, .animlib = animLib, .animname = animName);
			ApplyAnimation(playerid, animLib, animName, 4.1, 0, 1, 1, 0, 0, 2);
		}
	}
	return 1;
}
