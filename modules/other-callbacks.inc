#if defined _attdef_other_callbacks
	#endinput
#endif
#define _attdef_other_callbacks

#tryinclude "other-callbacks\OnInvalidWeaponDamage.inc"
#tryinclude "other-callbacks\OnPlayerDamage.inc"
#tryinclude "other-callbacks\OnPlayerDamageDone.inc"
#tryinclude "other-callbacks\OnPlayerDeathFinished.inc"
#tryinclude "other-callbacks\OnPlayerPrepareDeath.inc"
#tryinclude "other-callbacks\OnRejectedHit.inc"
#include "other-callbacks\OnPlayerModelSelection.inc"
#include "other-callbacks\OnScriptUpdate.inc"
