/*
 * Graphics.h
 *
 *  Created on: Jan 4, 2021
 *      Author: nds
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include "Controls.h"
#include "Bottom.h"

#define TOPROW	4
#define	MIDROW	11
#define	BOTROW	19
#define TBLCOL	8
#define TBRCOL	21
#define LCOL 	2
#define MIDCOL	14
#define RCOL	28

enum{TL, TR, L, M, R, BL, BR}; // Mole locations: top left, top right, left, middle, etc..

void InitMainScreen();
void InitSubScreen();
void InitSubBG2();
void InitSubBG0();
void InitMap();
void PlaceMole(int id);
void DrawMole(int row, int col);
void RemoveMole(int row, int col);

#endif /* GRAPHICS_H_ */
