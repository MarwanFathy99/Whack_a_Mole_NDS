/*
 * Sound.c
 */


#include "Sound.h"

void InitSound()
{
	mmInitDefaultMem((mm_addr) soundbank_bin);			// Initialise sound

	mmLoad(MOD_FLATOUTLIES);							// Load music and effects
	mmLoadEffect(SFX_M16_X);
	mmLoadEffect(SFX_SPLOOGE);
	mmLoadEffect(SFX_BOO);
	mmLoadEffect(SFX_APPLAUSE3);
	mmLoadEffect(SFX_BUZZER_X);

	mmEffect(SFX_M16_X);
	mmStart(MOD_FLATOUTLIES, MM_PLAY_LOOP);				// Play music on loop
	mmSetModuleVolume(0x4f);							// Set volume
}

