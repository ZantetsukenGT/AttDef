#if defined _attdef_OnScriptUpdate
	#endinput
#endif
#define _attdef_OnScriptUpdate

// OnScriptUpdate - interval: 1000 ms
task OnScriptUpdate[1000]()
{
	// Update Vehicle Information
	if (VehicleHealthTextdraw)
	{
		foreach (new i : PlayersInVehicles)
		{
			new vID = GetPlayerVehicleID(i);
			new vModelID = GetVehicleModel(vID);
			if (vModelID) //race condition: does the vehicle still exist
			{
				new Float: vHealth;
				GetVehicleHealth(vID, vHealth);
				va_PlayerTextDrawSetString(i, VInfo[i], "~w~%s ~r~%.0f%%", aVehicleNames[vModelID - 400], vHealth / 10);
			}
		}
	}
	return 1;
}
