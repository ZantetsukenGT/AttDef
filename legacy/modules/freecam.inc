#if !defined _attdef_header_incl
	#error "Module's header file include is not allowed here, include it in the correct section of the 'legacy/modules.inc' file."
#endif

#if defined _attdef_mod_freecam
	#endinput
#endif
#define _attdef_mod_freecam

/*
	Free camera script
*/

enum noclipenum {
	cameramode,
	flyobject,
	noclipcammode,
	lrold,
	udold,
	lastmove,
	Float: accelmul,
	bool: camfrozen,
	bool: FlyMode
}

new noclipdata[MAX_PLAYERS][noclipenum];

#define MOVE_SPEED		   100.0
#define ACCEL_RATE		   0.03

#define CAMERA_MODE_NONE   0
#define CAMERA_MODE_FLY	   1

#define NOT_MOVING		   0
#define MOVE_FORWARD	   1
#define MOVE_BACK		   2
#define MOVE_LEFT		   3
#define MOVE_RIGHT		   4
#define MOVE_FORWARD_LEFT  5
#define MOVE_FORWARD_RIGHT 6
#define MOVE_BACK_LEFT	   7
#define MOVE_BACK_RIGHT	   8
