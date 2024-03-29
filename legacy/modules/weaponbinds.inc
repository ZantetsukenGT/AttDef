#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_weaponbinds
	#endinput
#endif
#define _attdef_mod_weaponbinds

/*
	Weapon key binds system
*/

#define MAX_WEAPON_BINDS				 5 // Maximum allowed weapon key binds

// The primary key that is used with combination of other secondary keys...
#define WEAPON_BIND_PRIMARY_KEY_VALUE	 KEY_SPRINT		   // value
#define WEAPON_BIND_PRIMARY_KEY_TEXT	 "~k~~PED_SPRINT~" // gametext
#define WEAPON_BIND_PRIMARY_KEY_TEXT_ALT "SPRINT"		   // alternative text

#define WEAPON_BIND_TEXTDRAW_STRING_SIZE (MAX_WEAPON_BINDS * 73 + 16)
#define WEAPON_BIND_DIALOG_STRING_SIZE	 (MAX_WEAPON_BINDS * 40 + 45)

enum WeaponBindData_STRUCT {
	ModifyingWeaponBindIndex,		 // which index the player is coding/modifying
	BindKeyWeapon[MAX_WEAPON_BINDS], // the weapon id for this key bind
	PlayerText: WeaponBindTextDraw,	 // textdraw that shows key binds
	bool: WeaponBindTDShown			 // is the textdraw shown?
}

// Secondary keys values
new const WeaponBindKeyValue[MAX_WEAPON_BINDS]
	= { KEY_WALK, KEY_CROUCH, KEY_YES, KEY_NO, KEY_CTRL_BACK };

// Secondary keys gametexts
new const WeaponBindKeyText[MAX_WEAPON_BINDS][23]	 = { "~k~~SNEAK_ABOUT~", "~k~~PED_DUCK~", "~k~~CONVERSATION_YES~", "~k~~CONVERSATION_NO~", "~k~~GROUP_CONTROL_BWD~" };

// Secondary keys alternative texts
new const WeaponBindKeyText_ALT[MAX_WEAPON_BINDS][7] = { "WALK", "CROUCH", "YES", "NO", "H" };

new WeaponBindData[MAX_PLAYERS][WeaponBindData_STRUCT];
