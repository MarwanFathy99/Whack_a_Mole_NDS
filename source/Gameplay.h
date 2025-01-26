/*
 * Gameplay.h
 */

#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <nds.h>
#include <stdio.h>
#include <maxmod9.h>
#include "soundbank.h"
#include "soundbank_bin.h"
#include "Graphics.h"
#include "Sound.h"

#define HOLES		7
#define MAX_MISSES	3
#define MAX_WAIT	3
#define MAX_HITS	20

void InitGame();
void InitTimer();
void ISR0();
void CheckHitTouch(int x, int y);
void CheckHitButton(u16 button);
void newMole();

#endif /* GAMEPLAY_H_ */
