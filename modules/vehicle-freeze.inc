#if defined vehicle_freeze_included_
	#endinput
#endif
#define vehicle_freeze_included_

#include <YSI_Coding\y_hooks>

static enum (<<= 1)
{
	FREEZE_PAUSE = 1,
	FREEZE_GUNMENU
}

static Iterator: s_RoundVehicles<MAX_VEHICLES>;
static Iterator: s_FrozenVehicles<MAX_VEHICLES>;
static s_FreezeFlags[MAX_VEHICLES char] = { 0, ... };
static s_FreezeTimers[MAX_VEHICLES]		= { 0, ... };
static Float: s_VehicleSpeed[MAX_VEHICLES][3];

stock FreezeV_CreateVehicle(bool: isForRound, vehicletype, Float: x, Float: y, Float: z, Float: rotation, color1, color2, respawn_delay, addsiren = 0)
{
	new ret = CreateVehicle(vehicletype, x, y, z, rotation, color1, color2, respawn_delay, addsiren);
	if (ret && ret != INVALID_VEHICLE_ID)
	{
		if (isForRound)
		{
			Iter_Add(s_RoundVehicles, ret);
		}
	}
	return ret;
}

hook FreezeV_Timer(vehicleid, Float: x, Float: y, Float: z)
{
	SetVehiclePos(vehicleid, x, y, z);
	return 1;
}

static stock FreezeV_AddFlag(vehicleid, flag)
{
	if (s_FreezeFlags { vehicleid } == 0)
	{
		new Float: x,
			Float: y,
			Float: z;
		GetVehiclePos(vehicleid, x, y, z);
		GetVehicleVelocity(vehicleid, s_VehicleSpeed[vehicleid][0], s_VehicleSpeed[vehicleid][1], s_VehicleSpeed[vehicleid][2]);
		s_FreezeTimers[vehicleid] = SetTimerEx("FreezeV_Timer", 50, true, "ifff", vehicleid, x, y, z);
		Iter_Add(s_FrozenVehicles, vehicleid);
	}
	s_FreezeFlags { vehicleid } |= flag;
}

static stock FreezeV_RemoveFlag(vehicleid, flag)
{
	if (s_FreezeFlags { vehicleid } && (s_FreezeFlags { vehicleid } &= ~flag) == 0)
	{
		KillTimer(s_FreezeTimers[vehicleid]);
		SetVehicleVelocity(vehicleid, s_VehicleSpeed[vehicleid][0], s_VehicleSpeed[vehicleid][1], s_VehicleSpeed[vehicleid][2]);
		Iter_Remove(s_FrozenVehicles, vehicleid);
	}
}

stock FreezeV_PauseRound()
{
	foreach (new vehicleid : s_RoundVehicles) { FreezeV_AddFlag(vehicleid, FREEZE_PAUSE); }
}

stock FreezeV_UnpauseRound()
{
	foreach (new vehicleid : s_FrozenVehicles) { FreezeV_RemoveFlag(vehicleid, FREEZE_PAUSE); }
}

stock FreezeV_GunmenuOpen(vehicleid) { FreezeV_AddFlag(vehicleid, FREEZE_GUNMENU); }

stock FreezeV_GunmenuClose(vehicleid) { FreezeV_RemoveFlag(vehicleid, FREEZE_GUNMENU); }

stock FreezeV_DestroyAll()
{
	foreach (new vehicleid : s_FrozenVehicles)
	{
		FreezeV_RemoveFlag(vehicleid, FREEZE_PAUSE | FREEZE_GUNMENU);
	}
	Iter_Clear(s_FrozenVehicles);
	foreach (new vehicleid : s_RoundVehicles) { DestroyVehicle(vehicleid); }
	Iter_Clear(s_RoundVehicles);
}
