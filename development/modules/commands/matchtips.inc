#if defined _attdef_cmd_matchtips
	#endinput
#endif
#define _attdef_cmd_matchtips

YCMD: matchtips(playerid, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid, "display some guidelines about match mode");
	new str[1561];
	strcat(str, "\n" COL_PRIM "# {FFFFFF}To enable Match-Mode, press 'Y' in lobby or 'H' (shortcut to /match) in round and most textdraws will be clickable.");
	strcat(str, "\nOr use /war if you're in a hurry! Moreover, you can click on match textdraws to set team names, score and etc.");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}Useful match cmds: /teamname, /teamskin, /tr, /cr, /resetscores, /setscore, /roundtime, /cptime, /allvs, /rr");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}To re-select your weapons in a round, type /gunmenu.");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}Type /melee to get melee weapons menu while in a round.");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}Want to differentiate your team-mates on radar? Use /playermarkers");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}Use /weaponbinds to code your own weapon key binds.");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}To change your fight style, you can use the /fightstyle command.");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}You can remove a gun by holding it and typing /remgun.");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}Round can be paused by pressing 'Y' (for admins only).");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}You can request for backup from your team by pressing 'N' in round.");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}You can ask for pausing the round by pressing 'Y' in round.");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}To lead your team press 'H'.");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}If you're lagging, you can request netcheck with /netcheckme.");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}To diss whom you kill, use /deathdiss command.");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}You can change your gunmenu style with /gunmenustyle.");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}Type /sound to change the sound when you hit someone or get hit.");
	strcat(str, "\n" COL_PRIM "# {FFFFFF}Getting distracted by some textdraws? Try /hud");
	return ShowPlayerDialog(playerid, DIALOG_NO_RESPONSE, DIALOG_STYLE_MSGBOX, "" COL_PRIM "Match help & tips", str, "OK", "");
}
