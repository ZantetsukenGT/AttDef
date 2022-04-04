#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_common
	#endinput
#endif
#define _attdef_mod_common

/*
	Common stuff
*/

// Common shortcuts
#define MAX_DEADBODY_LABELS		_: MAX_3DTEXT_GLOBAL

#define PRESSED(%0)				(newkeys & (%0) == (%0) && oldkeys & (%0) != (%0))
#define RELEASED(%0)			(newkeys & (%0) != (%0) && oldkeys & (%0) == (%0))
#define HOLDING(%0)				(newkeys & (%0) == (%0))

#define ShiftRGBAToRGB(%0)		((%0) >>> 8)

#define MAX_LOWFPS_WARNINGS		7
#define MAX_PACKETLOSS_WARNINGS 15
#define MAX_HIGHPING_WARNINGS	10

new Iterator: DeadBodyActors<MAX_ACTORS>;
new Iterator: DeadBodyLabels<MAX_DEADBODY_LABELS>;
