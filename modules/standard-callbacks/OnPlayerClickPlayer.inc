#if defined _attdef_OnPClickP
	#endinput
#endif
#define _attdef_OnPClickP

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	ShowPlayerDialog(
		playerid, PLAYERCLICK_DIALOG, DIALOG_STYLE_LIST, va_return("Clicked ID: %d", clickedplayerid),
		"Getinfo\nAKA\nSpec\nAdd\nRemove\nReadd\nGunmenu\nGo\nGet\nSlap\nMute\nUnmute\nKick\nBan", "Select", "Cancel");
	LastClickedPlayer[playerid] = clickedplayerid;
	return 1;
}
