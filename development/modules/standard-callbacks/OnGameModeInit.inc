#if defined _attdef_OnGMInit
	#endinput
#endif
#define _attdef_OnGMInit

public OnGameModeInit()
{
	InitScriptCoreSettings();
	InitScriptSecondarySettings();
	AddToServersDatabase();
	return 1;
}
