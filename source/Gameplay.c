/*
 * Gameplay.c
 */
#include "Gameplay.h"

int no_hit, sec, location, hits = 0;
bool game_start = false;

void InitGame()
{
	InitMainScreen();
	InitSubScreen();
	InitSound();
	newMole();
}

void InitTimer()
{
	TIMER_DATA(0) = TIMER_FREQ_1024(1);									// Timer 0 interrupts every second to check
	TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;			// if max number of misses is reached.

	irqSet(IRQ_TIMER0, &ISR0);

	no_hit = 0;															// Reset all the values
	sec = 0;
	hits = 0;
	game_start = true;
	mmEffect(SFX_BUZZER_X);												// Buzzer to indicate the game has started

	irqEnable(IRQ_TIMER0);												// Start the time
}

void ISR0()
{
	if(no_hit == MAX_MISSES && game_start)
	{
		mmEffect(SFX_BOO);
		irqDisable(IRQ_TIMER0);											// If game is lost, stop the time
		game_start = false;
		no_hit = 0;
		sec = 0;
	}
	else if(sec == MAX_WAIT && game_start)
	{
		sec = 0;														// If wait time is 3 seconds, count on miss
		no_hit++;														// and reset wait time
		newMole();
	}
	else
		sec = (sec + 1) % 4;
}

void newMole()															// New random mole location
{
	sec = 0;
	int i = rand() % HOLES;
	location = i;
	PlaceMole(i);
}

void CheckHitButton(u16 button)
{
	if(game_start)
	{
		switch(location)												// Depending on mole location check if correct key is pressed
		{
			case TL:
				if(button & KEY_UP)
				{
					newMole();
					hits++;
					mmEffect(SFX_SPLOOGE);

					if(hits > MAX_HITS)
					{
						mmEffect(SFX_APPLAUSE3);						// If the game is won play applause and stop the game
						game_start = false;
					}
				}
				break;

			case TR:
				if(button & KEY_X)
				{
					newMole();
					hits++;
					mmEffect(SFX_SPLOOGE);

					if(hits > MAX_HITS)
					{
						game_start = false;
						mmEffect(SFX_APPLAUSE3);
					}
				}
				break;

			case L:
				if(button & KEY_LEFT)
				{
					newMole();
					hits++;
					mmEffect(SFX_SPLOOGE);

					if(hits > MAX_HITS)
					{
						mmEffect(SFX_APPLAUSE3);
						game_start = false;
					}
				}
				break;

			case M:
				if((button & KEY_RIGHT) || (button & KEY_Y))
				{
					newMole();
					hits++;
					mmEffect(SFX_SPLOOGE);

					if(hits > MAX_HITS)
					{
						mmEffect(SFX_APPLAUSE3);
						game_start = false;
					}
				}
				break;

			case R:
				if(button & KEY_A)
				{
					newMole();
					hits++;
					mmEffect(SFX_SPLOOGE);

					if(hits > MAX_HITS)
					{
						game_start = false;
						mmEffect(SFX_APPLAUSE3);
					}
				}
				break;

			case BL:
				if(button & KEY_DOWN)
				{
					newMole();
					hits++;
					mmEffect(SFX_SPLOOGE);

					if(hits > MAX_HITS)
					{
						game_start = false;
						mmEffect(SFX_APPLAUSE3);
					}
				}
				break;

			case BR:
				if(button & KEY_B)
				{
					newMole();
					hits++;
					mmEffect(SFX_SPLOOGE);

					if(hits > MAX_HITS)
					{
						game_start = false;
						mmEffect(SFX_APPLAUSE3);
					}
				}
				break;

			default:
				break;
		}
	}
}

void CheckHitTouch(int x, int y)
{
	if(game_start)
	{
		switch(location)
		{
			case TL:
				if((x >= TBLCOL * 8) && (x <= (TBLCOL + 2) * 8) &&			// Detect if touch coordinates are correct depending
				   (y >= TOPROW * 8) && (y <= (TOPROW + 1) * 8))			// on mole location
					{
						newMole();
						hits ++;
						mmEffect(SFX_SPLOOGE);

						if(hits > MAX_HITS)
						{
							game_start = false;
							mmEffect(SFX_APPLAUSE3);
						}
					}
				break;

			case TR:
				if((x >= TBRCOL * 8) && (x <= (TBRCOL + 2) * 8) &&
				   (y >= TOPROW * 8) && (y <= (TOPROW + 1) * 8))
					{
						newMole();
						hits ++;
						mmEffect(SFX_SPLOOGE);

						if(hits > MAX_HITS)
						{
							game_start = false;
							mmEffect(SFX_APPLAUSE3);
						}
					}
				break;

			case L:
				if((x >= LCOL * 8) && (x <= (LCOL + 2) * 8) &&
				   (y >= MIDROW * 8) && (y <= (MIDROW  + 1) * 8))
					{
						newMole();
						hits ++;
						mmEffect(SFX_SPLOOGE);

						if(hits > MAX_HITS)
						{
							game_start = false;
							mmEffect(SFX_APPLAUSE3);
						}
					}
				break;

			case M:
				if((x >= MIDCOL * 8) && (x <= (MIDCOL + 2) * 8) &&
					(y >= MIDROW * 8) && (y <= (MIDROW  + 1) * 8))
					{
						newMole();
						hits ++;
						mmEffect(SFX_SPLOOGE);

						if(hits > MAX_HITS)
						{
							game_start = false;
							mmEffect(SFX_APPLAUSE3);
						}
					}
				break;

			case R:
				if((x >= RCOL * 8) && (x <= (RCOL + 2) * 8) &&
				   (y >= MIDROW * 8) && (y <= (MIDROW + 1) * 8))
					{
						newMole();
						hits ++;
						mmEffect(SFX_SPLOOGE);

						if(hits > MAX_HITS)
						{
							game_start = false;
							mmEffect(SFX_APPLAUSE3);
						}
					}
				break;

			case BL:
				if((x >= TBLCOL * 8) && (x <= (TBLCOL + 2) * 8) &&
				   (y >= BOTROW * 8) && (y <= (BOTROW + 1) * 8))
					{
						newMole();
						hits ++;
						mmEffect(SFX_SPLOOGE);

						if(hits > MAX_HITS)
						{
							game_start = false;
							mmEffect(SFX_APPLAUSE3);
						}
					}
				break;

			case BR:
				if((x >= (TBRCOL * 8)) && (x <= ((TBRCOL + 2) * 8)) &&
				   ((y >= BOTROW * 8)) && (y <= ((BOTROW + 1) * 8)))
					{
						newMole();
						hits ++;
						mmEffect(SFX_SPLOOGE);

						if(hits > MAX_HITS)
						{
							game_start = false;
							mmEffect(SFX_APPLAUSE3);
						}
					}
				break;

			default:
				break;
		}
	}
}
