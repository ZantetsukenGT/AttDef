#if defined _attdef_OnGMInit
	#endinput
#endif
#define _attdef_OnGMInit

public OnGameModeInit()
{
	InitScriptCoreSettings();
	InitScriptSecondarySettings();
	AddToServersDatabase();
	SetTimer("OnScriptUpdate", 1000, true); // Timer that is repeatedly called every second (will be using this for most global stuff)
	return 1;
}
