#if defined _attdef_OnRejectedHit
	#endinput
#endif
#define _attdef_OnRejectedHit

public OnRejectedHit(playerid, hit[E_REJECTED_HIT])
{
	if (hit[e_Reason] == HIT_OUT_OF_RANGE)
	{
		new output[144];
		format(output, sizeof(output), "(%s -> %s) %s", ReturnWeaponName(hit[e_Weapon]), hit[e_Name], g_HitRejectReasons[hit[e_Reason]]);
		format(output, sizeof(output), output, hit[e_Info1], hit[e_Info2]);
		SendClientMessage(playerid, 0xEE5454FF, "Rejected hit: %s", output);
		PlayerPlaySound(playerid, 1054, 0, 0, 0);
	}
	return 1;
}
