#if defined _attdef_cmd_changelog
	#endinput
#endif
#define _attdef_cmd_changelog

YCMD: changelog(playerid1, params[], help)
{
	if (help)
		return SendCommandHelpMessage(playerid1, "display a list of gamemode updates");

	inline InlineShowChanges(playerid, dialogid, response, listitem, string: inputtext[])
	{
#pragma unused playerid, dialogid, response, listitem, inputtext
	}
	inline InlineVersionSelect(playerid, dialogid, response, listitem, string: inputtext[])
	{
#pragma unused playerid, dialogid, inputtext
		if (!response)
			return 1;
		new str[4095];
		switch (listitem)
		{
			case 0:
			{
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC "\n  1.38.0 Features and fixes");
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nAdded weapon-config.");
				strcat(str, "{CCCCCC}\nFPS independent lagshoot.");
				strcat(str, "{CCCCCC}\nAdded several samp patches for gameplay integrity.");
				strcat(str, "{CCCCCC}\nDamage modification for most weapons available through " COL_PRIM "/" COL_SEC "weapondmg");
				strcat(str, "{CCCCCC}\nGeneral improvements and fixes.");
				strcat(str, COL_PRIM"\n\nPRO TIPS:");
				strcat(str, COL_SEC "\n{FFD700}Sniper bug fix available! " COL_SEC "shorturl.at/bgpH1");
				strcat(str, COL_SEC "\n{FFD700}Silent ASI Loader required: " COL_SEC "shorturl.at/szCR0");
				strcat(str, COL_PRIM"\n\nif you find any bug please let me know");
				strcat(str, "{CCCCCC}\nAll the updates from this changelog have been coded by " COL_PRIM "Shooter (Zantetsuken#2220)");
			}
			case 1:
			{
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC "\n  1.37.11 Features and fixes");
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nImproved performance for some internals.");
				strcat(str, "{CCCCCC}\nUpdated third party libraries and services.");
				strcat(str, "{CCCCCC}\nFixed some known errors.");
				strcat(str, "{CCCCCC}\nweapon-config is not present, but will be introduced in v1.38.");
				strcat(str, COL_PRIM"\n\nPRO TIPS:");
				strcat(str, COL_SEC "\n{FFD700}Sniper bug fix available! " COL_SEC "shorturl.at/bgpH1");
				strcat(str, COL_SEC "\n{FFD700}Silent ASI Loader required: " COL_SEC "shorturl.at/szCR0");
				strcat(str, COL_PRIM"\n\nif you find any bug please let me know");
				strcat(str, "{CCCCCC}\nAll the updates from this changelog have been coded by " COL_PRIM "Shooter (Zantetsuken#2220)");
			}
			case 2:
			{
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC "\n  1.37.10 (Performance Update) Features and fixes");
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nReplacing someone should set its correct skin now.");
				strcat(str, "{CCCCCC}\nFPS counter will not double or drop randomly.");
				strcat(str, "{CCCCCC}\nCommands now can make use of either " COL_SEC "Player Names/ID's.");
				strcat(str, "{CCCCCC}\nRestored all the original arenas, bases, and DMs; take a look at the " COL_PRIM "/" COL_SEC "loadbases {CCCCCC}command.");
				strcat(str, "{CCCCCC}\nFixed some rare crashes and known errors.");
				strcat(str, "{CCCCCC}\nPerformance should be overall better on less powerful servers.");
				strcat(str, "{CCCCCC}\nweapon-config is not present, but will be introduced in v1.38.");
				strcat(str, COL_PRIM"\n\nPRO TIPS:");
				strcat(str, COL_SEC "\n{FFD700}Sniper bug fix available! " COL_SEC "shorturl.at/bgpH1");
				strcat(str, COL_SEC "\n{FFD700}Silent ASI Loader required: " COL_SEC "shorturl.at/szCR0");
				strcat(str, COL_PRIM"\n\nif you find any bug please let me know");
				strcat(str, "{CCCCCC}\nAll the updates from this changelog have been coded by " COL_PRIM "Shooter (Zantetsuken#2220)");
			}
			case 3:
			{
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC "\n  1.37.9 Features and fixes");
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nFixed no round timer bug, cp bug, etc.");
				strcat(str, "{CCCCCC}\nOther minimal fixes related to timers.");
				strcat(str, COL_PRIM"\n\nPRO TIPS:");
				strcat(str, COL_SEC "\n{FFD700}Sniper bug fix available! " COL_SEC "shorturl.at/bgpH1");
				strcat(str, COL_SEC "\n{FFD700}Silent ASI Loader required: " COL_SEC "shorturl.at/szCR0");
				strcat(str, COL_PRIM"\n\nif you find any bug please let me know");
				strcat(str, "{CCCCCC}\nAll the updates from this changelog have been coded by " COL_PRIM "Shooter (Zantetsuken#2220)");
			}
			case 4:
			{
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC "\n  1.37.8 Features and fixes");
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nAdded " COL_PRIM "/" COL_SEC "deaglenerf {CCCCCC} to configure deagle dmg.");
				strcat(str, "{CCCCCC}\nAdded " COL_PRIM "/" COL_SEC "snipernerf {CCCCCC} to configure sniper dmg.");
				strcat(str, "{CCCCCC}\nRound timer is now reduced properly (sadly timer bug is still around).");
				strcat(str, "{CCCCCC}\nReplacing a player now sets the correct skin.");
				strcat(str, COL_PRIM"\n\nPRO TIPS:");
				strcat(str, COL_SEC "\n{FFD700}Sniper bug fix available! " COL_SEC "shorturl.at/bgpH1");
				strcat(str, COL_SEC "\n{FFD700}Silent ASI Loader required: " COL_SEC "shorturl.at/szCR0");
				strcat(str, COL_PRIM"\n\nif you find any bug please let me know");
				strcat(str, "{CCCCCC}\nAll the updates from this changelog have been coded by " COL_PRIM "Shooter (Zantetsuken#2220)");
			}
			case 5:
			{
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC "\n  1.37.7 Features and fixes");
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nMore bug fixes.");
				strcat(str, "{CCCCCC}\nSeveral optimizations.");
				strcat(str, "{CCCCCC}\nRestored parachute removal.");
				strcat(str, COL_PRIM"\n\nPRO TIPS:");
				strcat(str, COL_SEC "\n{FFD700}Sniper bug fix available! " COL_SEC "shorturl.at/bgpH1");
				strcat(str, COL_SEC "\n{FFD700}Silent ASI Loader required: " COL_SEC "shorturl.at/szCR0");
				strcat(str, COL_PRIM"\n\nif you find any bug please let me know");
				strcat(str, "{CCCCCC}\nAll the updates from this changelog have been coded by " COL_PRIM "Shooter (Zantetsuken#2220)");
			}
			case 6:
			{
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC "\n  1.37.6 Features and fixes");
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nLong lived bug fixes.");
				strcat(str, COL_PRIM"\n\nPRO TIPS:");
				strcat(str, COL_SEC "\n{FFD700}Sniper bug fix available! " COL_SEC "shorturl.at/bgpH1");
				strcat(str, COL_SEC "\n{FFD700}Silent ASI Loader required " COL_SEC "shorturl.at/szCR0");
				strcat(str, COL_PRIM"\n\nif you find any bug please let me know");
				strcat(str, "{CCCCCC}\nAll the updates from this changelog have been coded by " COL_PRIM "Shooter (Zantetsuken#2220)");
			}
			case 7:
			{
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC "\n  1.37.5 (no anticheats) Features and fixes");
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nMinor fixes and optimizations.");
				strcat(str, "{CCCCCC}\nDisabled most anticheats, bound to be reintroduced with improvements in the future.");
				strcat(str, COL_PRIM"\n\nPRO TIPS:");
				strcat(str, COL_SEC "\n{FFD700}Sniper bug fix available! " COL_SEC "shorturl.at/bgpH1");
				strcat(str, COL_SEC "\n{FFD700}Silent ASI Loader required " COL_SEC "shorturl.at/szCR0");
				strcat(str, COL_PRIM"\n\nif you find any bug please let me know");
				strcat(str, "{CCCCCC}\nAll the updates from this changelog have been coded by " COL_PRIM "Shooter (Zantetsuken#2220)");
			}
			case 8:
			{
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC "\n  1.37.5 Features and fixes");
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nbcrypt (working since older versions but not publicly stated).");
				strcat(str, "{CCCCCC}\nFixed ra, randomint, rb and autostart's potential infinite loop.");
				strcat(str, "{CCCCCC}\nRemoved all geoip.db functionality in favor of IPHub.");
				strcat(str, "{CCCCCC}\nAdjusted visuals and some new dialogs here and there.");
				strcat(str, "{CCCCCC}\nNo longer shows someone's IP to everyone on " COL_PRIM "/" COL_SEC "banip {CCCCCC}and " COL_PRIM "/" COL_SEC "unbanip{CCCCCC}.");
				strcat(str, COL_PRIM"\n\nMod to make the high ping backpack invisible");
				strcat(str, COL_SEC "\nhttps://tinyurl.com/53fabkj3");
				strcat(str, COL_PRIM"\n\nif you find any bug please let me know");
				strcat(str, "{CCCCCC}\nAll the updates from this changelog have been coded by " COL_PRIM "Shooter (Zantetsuken#2220)");
			}
			case 9:
			{
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC "\n  1.37.4 Features and fixes");
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				//strcat(str, "{CCCCCC}\nAddressed high risk security concerns.");
				strcat(str, "{CCCCCC}\nImproved round ending.");
				strcat(str, "{CCCCCC}\nSpectators can no longer sync.");
				strcat(str, COL_PRIM"\n\nMod to make the high ping backpack invisible");
				strcat(str, COL_SEC "\nhttps://tinyurl.com/53fabkj3");
				strcat(str, COL_PRIM"\n\nif you find any bug please let me know");
				strcat(str, "{CCCCCC}\nAll the updates from this changelog have been coded by " COL_PRIM "Shooter (Zantetsuken#2220)");
			}
			case 10:
			{
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC "\n  1.37.3 Features and fixes");
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nAdjusted random spawn values.");
				strcat(str, "{CCCCCC}\nAdded face direction to lobby spawn (requested).");
				strcat(str, "{CCCCCC}\nPlanes and helicopters will no longer fall when round is unpaused.");
				strcat(str, "{CCCCCC}\nRelaxed some anticheat punishments.");
				strcat(str, "{CCCCCC}\nFixed textdraws and added missing ones.");
				strcat(str, "{CCCCCC}\nAbusing sync at the start of a round is no longer possible.");
				strcat(str, "{CCCCCC}\nFixed a bug in " COL_PRIM "/" COL_SEC "config {CCCCCC}dialog.");
				strcat(str, "{CCCCCC}\nAdjusted chat clear size.");
				strcat(str, "{CCCCCC}\nA starting round can now be ended before or during its countdown.");
				strcat(str, "{CCCCCC}\nMore optimized timers and internal stuff.");
				strcat(str, COL_PRIM"\n\nMod to make the high ping backpack invisible");
				strcat(str, COL_SEC "\nhttps://tinyurl.com/53fabkj3");
				strcat(str, COL_PRIM"\n\nif you find any bug please let me know");
				strcat(str, "{CCCCCC}\nAll the updates from this changelog have been coded by " COL_PRIM "Shooter (Zantetsuken#2220)");
			}
			case 11:
			{
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC "\n  1.37.2 Features and fixes");
				strcat(str, COL_PRIM "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nFixed some commands and internal behaviors.");
				strcat(str, "{CCCCCC}\nImproved readability in some dialogs.");
				strcat(str, "{CCCCCC}\nImproved consistency in error/warning messages.");
				strcat(str, COL_PRIM"\n\nMod to make the high ping backpack invisible");
				strcat(str, COL_SEC "\nhttps://tinyurl.com/53fabkj3");
				strcat(str, COL_PRIM"\n\nif you find any bug please let me know");
				strcat(str, "{CCCCCC}\nAll the updates from this changelog have been coded by " COL_PRIM "Shooter (Zantetsuken#2220)");
			}
			case 12:
			{
				strcat(str, COL_PRIM"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC"\n  1.37.1 Features and fixes");
				strcat(str, COL_PRIM"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nDisabled switching to ugmp arenas for now.");
				strcat(str, "{CCCCCC}\nFixed " COL_PRIM "/" COL_SEC "changelog {CCCCCC}dialog style.");
				strcat(str, COL_PRIM"\n\nMod to make the high ping backpack invisible");
				strcat(str, COL_SEC "\nhttps://tinyurl.com/53fabkj3");
				strcat(str, COL_PRIM"\n\nif you find any bug please let me know");
				strcat(str, "{CCCCCC}\nAll the updates from this changelog have been coded by " COL_PRIM "Shooter (Zantetsuken#2220)");
			}
			case 13:
			{
				strcat(str, COL_PRIM"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC"\n  1.37.0 Features and fixes");
				strcat(str, COL_PRIM"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nRefactored the entire project for greater maintainability and quality of life");
				strcat(str, "{CCCCCC}\nUpgraded dependencies, standardized the project with sampctl and added semantic versioning");
				strcat(str, "{CCCCCC}\nReplaced all the gamemode timers for extremely precise ones.");
				strcat(str, "{CCCCCC}\nMinor technical improvements, fixes and optimizations, it was not the focus in this release but it will on future releases");
				strcat(str, "{CCCCCC}\nAdded more map bug blocks");
				strcat(str, "{CCCCCC}\nReverted to legacy, default theme colors");
				strcat(str, "{CCCCCC}\nRevised cmd levels and removed legacy league system");
				strcat(str, COL_PRIM"\n\nMod to make the high ping backpack invisible");
				strcat(str, COL_SEC "\nhttps://tinyurl.com/53fabkj3");
				strcat(str, COL_PRIM"\n\nif you find any bug please let me know");
				strcat(str, "{CCCCCC}\nAll the updates from this changelog have been coded by " COL_PRIM "Shooter (Zantetsuken#2220)");
			}
			case 14:
			{
				strcat(str, COL_PRIM"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC"\n   1.36 Features and fixes");
				strcat(str, COL_PRIM"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nAdded anti-proxy");
				strcat(str, "{CCCCCC}\nAdded backpacks for 200+ ping");
				strcat(str, "{CCCCCC}\nAdded team-stun cancellation");
				strcat(str, "{CCCCCC}\nRemoved some breakable and abusable objects");
				strcat(str, "{CCCCCC}\nFixed map bugs");
				strcat(str, "{CCCCCC}\nUpdated DM respawn");
				strcat(str, "{CCCCCC}\nAuto parachute remover - will remove the parachute as soon as the player starts running");
				strcat(str, "{CCCCCC}\nParachute opening animation skip - when parachuting LMB will put you straight into a fall animation");
				strcat(str, "{CCCCCC}\nVehicle Collisions temporary disablement on base start");
				strcat(str, "{CCCCCC}\nAdded level 5 chat / clan-chat (* text)");
				strcat(str, "{CCCCCC}\nPress F to Pay Respects (after someone's round death)");
				strcat(str, "{CCCCCC}\nCreated new theme system");
				strcat(str, COL_PRIM"\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC"\n	         Commands");
				strcat(str, COL_PRIM"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_PRIM"\n/" COL_SEC"tunfreeze {CCCCCC}- level 1 (unfreezes players for 500ms) - to be used on players frozen in mid-air");
				strcat(str, COL_PRIM"\n/" COL_SEC"backpacks {CCCCCC}- level 5 (toggles 200+ ping backpacks)");
				strcat(str, COL_PRIM"\n/" COL_SEC"teamstun {CCCCCC}- level 4 (toggles team-stun cancellation)");
				strcat(str, COL_PRIM"\n/" COL_SEC"floorbug {CCCCCC}- level 5 (toggles anti-floorbug)");
				strcat(str, COL_PRIM"\n/" COL_SEC"servername {CCCCCC}- level 5 (changes the welcome message server name)");
				strcat(str, COL_PRIM"\n/" COL_SEC"clanchannel {CCCCCC}- level 5 (changes * level 5/clan-chat channel name)");
				strcat(str, COL_PRIM"\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, COL_SEC"\n	   Anti-Cheat scripts");
				strcat(str, COL_PRIM"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
				strcat(str, "{CCCCCC}\nSpeed limiter (vehicle) | land vehicles are unable to reach higher velocity than infernus with nitro does");
				strcat(str, "{CCCCCC}\nAnti floorbug | less than 3 warnings - message and animation reset | 3 warnings - kill (in round)");
				strcat(str, "{CCCCCC}\nSpeed limiter (on foot) | less than 3 warnings - message and animation reset | 3 warnings - kill (in round)");
				strcat(str, "{CCCCCC}\nAnti vehicle speed hack | accelerating too fast will kill the driver (in round)");
				strcat(str, "{CCCCCC}\nAnti macro scripts (4) | if 0 chance of false positives - will instantly kill (in round)");
				strcat(str, "{CCCCCC}\nAnti esc after stun | warning message (in round)");
				strcat(str, "{CCCCCC}\nOther existing scripts will not be disclosed to decrease likelihood of bypassing");
				strcat(str, COL_PRIM"\n\nMod to make the high ping backpack invisible");
				strcat(str, COL_SEC "\nhttps://tinyurl.com/53fabkj3");
				strcat(str, "{CCCCCC}\n\nAll the updates from this changelog have been coded by " COL_PRIM "zyph");
			}
		}
		Dialog_ShowCallback(playerid1, using inline InlineShowChanges, DIALOG_STYLE_MSGBOX, va_return("%s gamemode " COL_PRIM "updates", GM_NAME), str, "OK", "");
	}
	Dialog_ShowCallback(
		playerid1, using inline InlineVersionSelect, DIALOG_STYLE_LIST, COL_SEC "Select a gamemode version to see the introduced changes", "1.38.0\n1.37.11\n1.37.10\n1.37.9\n1.37.8\n1.37.7\n1.37.6\n1.37.5 (no anticheats)\n1.37.5\n1.37.4\n1.37.3\n1.37.2\n1.37.1\n1.37.0\n1.36", "Select",
		"Cancel");
	return 1;
}
