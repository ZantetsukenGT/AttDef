#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_messagebox
	#endinput
#endif
#define _attdef_mod_messagebox

/*
	MessageBox script
*/

// Message box types

enum MessageBoxType {
	PlayerText: MSGBOX_TYPE_TOP,
	PlayerText: MSGBOX_TYPE_MIDDLE,
	PlayerText: MSGBOX_TYPE_BOTTOM
}

enum MsgBoxStruct {
	PlayerText: caption_TD[MessageBoxType],
	PlayerText: info_TD[MessageBoxType],
	MsgBoxtimer[MessageBoxType]
}

new MsgBoxData[MAX_PLAYERS][MsgBoxStruct];
