/*
 * Marwan Ibrahim, SCIPER: 283419
 * January 2021
 */

#include <nds.h>
#include <stdio.h>
#include "Gameplay.h"

int main(void) {
    consoleDemoInit();
    InitGame();

    while(1)
    {
    	scanKeys();

    	u16 keys = keysDown();

    	if(keys & KEY_START)
    	{
    		InitTimer();															// Start the timer
    	}

    	if(keys & KEY_TOUCH)														// If the screen is touched check for hit
    	{
    		touchPosition touch;
    		touchRead(&touch);
    		CheckHitTouch(touch.px, touch.py);
    	}

    	if((keys & KEY_A) || (keys & KEY_B) || (keys & KEY_X) || (keys & KEY_Y)		// If any of the gameplay keys is pressed
    	   || (keys & KEY_LEFT) || (keys & KEY_RIGHT) || (keys & KEY_UP)			// check if it's a hit or not
    	   || (keys & KEY_DOWN))
    			CheckHitButton(keys);

    	swiWaitForVBlank();
    }
}
