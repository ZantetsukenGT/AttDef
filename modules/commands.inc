#if defined _attdef_cmds
	#endinput
#endif
#define _attdef_cmds

/* y_commands_impl.inc
enum e_COMMAND_ERRORS
{
	The majority of these are even - odd numbers return "1" not "0".
	COMMAND_ZERO_RET      = 0 , // The command returned 0.
	COMMAND_OK            = 1 , // Called corectly.
	COMMAND_UNDEFINED     = 2 , // Command doesn't exist.
	COMMAND_DENIED        = 3 , // Can't use the command.
	COMMAND_HIDDEN        = 4 , // Can't use the command don't let them know it exists.
	COMMAND_NO_PLAYER     = 6 , // Used by a player who shouldn't exist.
	COMMAND_DISABLED      = 7 , // All commands are disabled for this player.
	COMMAND_BAD_PREFIX    = 8 , // Used "/" instead of "#", or something similar.
	COMMAND_INVALID_INPUT = 10, // Didn't type "/something".
	COMMAND_SILENT        = 11, // Just end.  Don't call the command or print anything.
}
*/

public e_COMMAND_ERRORS: OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS: success)
{
	// Skip spam check on shortcut commands
	if (strcmp(cmdtext, "/rb", true) && strcmp(cmdtext, "/ra", true) && strfind(cmdtext, "/cmdhelp", true) == -1)
	{
		new currentTick = GetTickCount();
		if (AntiSpam && currentTick - Player[playerid][lastChat] < 500)
		{
			SendErrorMessage(playerid, "Please wait.");
			return COMMAND_DENIED;
		}
		Player[playerid][lastChat] = currentTick;
	}

	if (success == COMMAND_UNDEFINED)
	{
		SendErrorMessage(playerid, va_return("Unknown command: %s. Check /cmds, /acmds or /cmdhelp for more info!", cmdtext));
		return COMMAND_DENIED;
	}
	// AFK players are not supposed to use any command
	if (Player[playerid][IsAFK])
	{
		if (!strcmp(cmdtext, "/back", true))
			return COMMAND_OK;
		else
		{
			SendErrorMessage(playerid, "Can't use any command during AFK mode. Type /back");
			return COMMAND_DENIED;
		}
	}
	// Normal players should not use any command while in duel
	if (Player[playerid][InDuel])
	{
		if (!strcmp(cmdtext, "/rq", true))
			return COMMAND_OK;
		else if (Player[playerid][Level] < 1 && !IsPlayerAdmin(playerid))
		{
			SendErrorMessage(playerid, "Can't use any command in duel. Type /rq to quit duel.");
			return COMMAND_DENIED;
		}
	}
	// Players need to spawn first in order to use commands
	if (Player[playerid][Team] == NON)
	{
		SendErrorMessage(playerid, "You need to spawn to be able to use commands.");
		return COMMAND_DENIED;
	}
	if (success == COMMAND_DENIED)
	{
		SendErrorMessage(playerid, "Your level is not high enough to use this command!");
		return COMMAND_DENIED;
	}
	return COMMAND_OK;
}

//standard attdef commands
#include "commands/acar.inc"
#include "commands/acmds.inc"
#include "commands/add.inc"
#include "commands/addall.inc"
#include "commands/addme.inc"
#include "commands/admins.inc"
#include "commands/afk.inc"
#include "commands/aka.inc"
#include "commands/alladmins.inc"
#include "commands/allvs.inc"
#include "commands/ann.inc"
#include "commands/antispam.inc"
#include "commands/armourall.inc"
#include "commands/asay.inc"
#include "commands/autobalance.inc"
#include "commands/autopause.inc"
#include "commands/back.inc"
#include "commands/balance.inc"
#include "commands/ban.inc"
#include "commands/banip.inc"
#include "commands/base.inc"
#include "commands/blockpm.inc"
#include "commands/blockpmall.inc"
#include "commands/cc.inc"
#include "commands/cchannel.inc"
#include "commands/changelog.inc"
#include "commands/changename.inc"
#include "commands/changepass.inc"
#include "commands/clearadmcmd.inc"
#include "commands/clearallaka.inc"
#include "commands/cmdhelp.inc"
#include "commands/cmds.inc"
#include "commands/config.inc"
#include "commands/connstats.inc"
#include "commands/cptime.inc"
#include "commands/cr.inc"
#include "commands/credits.inc"
#include "commands/customtitle.inc"
#include "commands/dance.inc"
#include "commands/deathdiss.inc"
#include "commands/defaultskins.inc"
#include "commands/deleteacc.inc"
#include "commands/dm.inc"
#include "commands/dmq.inc"
#include "commands/duel.inc"
#include "commands/end.inc"
#include "commands/explode.inc"
#include "commands/fakepacket.inc"
#include "commands/fightstyle.inc"
#include "commands/fixcp.inc"
#include "commands/fpscheck.inc"
#include "commands/freecam.inc"
#include "commands/freeze.inc"
#include "commands/gamespeed.inc"
#include "commands/get.inc"
#include "commands/getgun.inc"
#include "commands/getpara.inc"
#include "commands/giveallgun.inc"
#include "commands/givemenu.inc"
#include "commands/giveweapon.inc"
#include "commands/gmx.inc"
#include "commands/goto.inc"
#include "commands/gunmenu.inc"
#include "commands/gunmenumod.inc"
#include "commands/gunmenustyle.inc"
#include "commands/heal.inc"
#include "commands/healall.inc"
#include "commands/help.inc"
#include "commands/hud.inc"
#include "commands/int.inc"
#include "commands/jetpack.inc"
#include "commands/kick.inc"
#include "commands/lastplayed.inc"
#include "commands/limit.inc"
#include "commands/loadarenas.inc"
#include "commands/loadbases.inc"
#include "commands/lobby.inc"
#include "commands/lobbyguns.inc"
#include "commands/lock.inc"
#include "commands/mainspawn.inc"
#include "commands/match.inc"
#include "commands/matchtips.inc"
#include "commands/maxpacket.inc"
#include "commands/maxping.inc"
#include "commands/melee.inc"
#include "commands/minfps.inc"
#include "commands/move.inc"
#include "commands/movecam.inc"
#include "commands/mute.inc"
#include "commands/muteall.inc"
#include "commands/netcheck.inc"
#include "commands/netcheckme.inc"
#include "commands/no.inc"
#include "commands/para.inc"
#include "commands/pause.inc"
#include "commands/pauselimit.inc"
#include "commands/pchannel.inc"
#include "commands/permlock.inc"
#include "commands/pingcheck.inc"
#include "commands/playermarkers.inc"
#include "commands/plcheck.inc"
#include "commands/pm.inc"
#include "commands/r.inc"
#include "commands/ra.inc"
#include "commands/random.inc"
#include "commands/randomint.inc"
#include "commands/rb.inc"
#include "commands/readd.inc"
#include "commands/reloaddb.inc"
#include "commands/rem.inc"
#include "commands/remgun.inc"
#include "commands/remove.inc"
#include "commands/replace.inc"
#include "commands/reset.inc"
#include "commands/resetallguns.inc"
#include "commands/resetscores.inc"
#include "commands/rounds.inc"
#include "commands/roundtime.inc"
#include "commands/rq.inc"
#include "commands/rr.inc"
#include "commands/servername.inc"
#include "commands/serverpassword.inc"
#include "commands/serverstats.inc"
#include "commands/setacclevel.inc"
#include "commands/setafk.inc"
#include "commands/setarmour.inc"
#include "commands/setcmdlevel.inc"
#include "commands/sethp.inc"
#include "commands/setlevel.inc"
#include "commands/setscore.inc"
#include "commands/setteam.inc"
#include "commands/settings.inc"
#include "commands/showagain.inc"
#include "commands/skin.inc"
#include "commands/slap.inc"
#include "commands/sound.inc"
#include "commands/spas.inc"
#include "commands/spec.inc"
#include "commands/specoff.inc"
#include "commands/speedcap.inc"
#include "commands/start.inc"
#include "commands/style.inc"
#include "commands/swap.inc"
#include "commands/switch.inc"
#include "commands/sync.inc"
#include "commands/teamname.inc"
#include "commands/teamskin.inc"
#include "commands/testsound.inc"
#include "commands/themes.inc"
#include "commands/time.inc"
#include "commands/togglechat.inc"
#include "commands/tr.inc"
#include "commands/tunfreeze.inc"
#include "commands/unbanip.inc"
#include "commands/unfreeze.inc"
#include "commands/unlock.inc"
#include "commands/unmute.inc"
#include "commands/unmuteall.inc"
#include "commands/unpause.inc"
#include "commands/v.inc"
#include "commands/vc.inc"
#include "commands/view.inc"
#include "commands/voteadd.inc"
#include "commands/voteendmatch.inc"
#include "commands/votekick.inc"
#include "commands/votemenu.inc"
#include "commands/votenetcheck.inc"
#include "commands/votepause.inc"
#include "commands/votereadd.inc"
#include "commands/voterem.inc"
#include "commands/voterr.inc"
#include "commands/voteswitch.inc"
#include "commands/voteunpause.inc"
#include "commands/vr.inc"
#include "commands/vworld.inc"
#include "commands/war.inc"
#include "commands/weaponbinds.inc"
#include "commands/weapondmg.inc"
#include "commands/weather.inc"
#include "commands/xmas.inc"
#include "commands/yes.inc"
