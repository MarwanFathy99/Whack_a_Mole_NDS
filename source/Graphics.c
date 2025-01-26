/*
 * Graphics.c
 */
#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include "Graphics.h"

int row, col = 0;

unsigned char mole[] = {255, 255, 255, 255, 255, 255, 255, 255,				// Mole body
						  255, 255, 255, 255, 255, 255, 255, 255,
						  255, 255, 255, 255, 255, 255, 255, 255,
						  255, 255, 255, 255, 255, 255, 255, 255,
						  255, 255, 255, 255, 255, 255, 255, 255,
						  255, 255, 255, 255, 255, 255, 255, 255,
						  255, 255, 255, 255, 255, 255, 255, 255,
						  255, 255, 255, 255, 255, 255, 255, 255};

unsigned char moleTL[] = {0, 0, 0, 0, 0, 0, 255, 255,						// Mole left side of head
						  0, 0, 0, 0, 255, 255, 255, 255,
						  0, 0, 255, 255, 255, 255, 255, 255,
						  0, 255, 255, 255, 255, 255, 255, 255,
						  0, 255, 255, 255, 254, 254, 254, 255,
						  255, 255, 255, 255, 254, 254, 254, 255,
						  255, 255, 255, 255, 254, 254, 254, 255,
						  255, 255, 255, 255, 255, 255, 255, 255};

unsigned char moleTR[] = {255, 255, 0, 0, 0, 0, 0, 0,						// Mole right side of head
						  255, 255, 255, 255, 0, 0, 0, 0,
						  255, 255, 255, 255, 255, 255, 0, 0,
						  255, 255, 255, 255, 255, 255, 255, 0,
						  255, 254, 254, 254, 255, 255, 255, 0,
						  255, 254, 254, 254, 255, 255, 255, 255,
						  255, 254, 254, 254, 255, 255, 255, 255,
						  255, 255, 255, 255, 255, 255, 255, 255};

unsigned char empty[] = {0, 0, 0, 0, 0, 0, 0, 0,							// Transparent tile for mole removal
					    0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0};

void InitMainScreen()
{
	// Configure Background and VRAM

	REG_DISPCNT = MODE_5_2D | DISPLAY_BG2_ACTIVE;
	VRAM_A_CR = VRAM_ENABLE | VRAM_A_MAIN_BG;

	BGCTRL[2] = BG_BMP_BASE(0) | BgSize_B8_256x256;

	// Copy image bitmap and palette to memory

	swiCopy(ControlsPal, BG_PALETTE, ControlsPalLen/2);
	swiCopy(ControlsBitmap, BG_GFX, ControlsBitmapLen/2);

	// Affine Matrix
	REG_BG2PA = 256;
	REG_BG2PC = 0;
	REG_BG2PB = 0;
	REG_BG2PD = 256;
}

void InitSubScreen()
{
	//Setup control register and memory bank C (for sub engine background)

	REG_DISPCNT_SUB = MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG0_ACTIVE;
	VRAM_C_CR = VRAM_ENABLE | VRAM_C_SUB_BG;

	InitSubBG2();
	InitSubBG0();
	InitMap();
}


void InitSubBG2()
{
	BGCTRL_SUB[2] = BG_BMP_BASE(0) | BgSize_B8_256x256;

	//Copy image and palette to memory

	swiCopy(BottomPal, BG_PALETTE_SUB, BottomPalLen/2);
	swiCopy(BottomBitmap, BG_GFX_SUB, BottomBitmapLen/2);


	//Affine Matrix

	REG_BG2PA_SUB = 256;
	REG_BG2PC_SUB = 0;
	REG_BG2PB_SUB = 0;
	REG_BG2PD_SUB = 256;
}

void InitSubBG0()
{
	BGCTRL_SUB[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(24) | BG_TILE_BASE(0);

	//Copy tiles to memory

	swiCopy(mole, BG_TILE_RAM_SUB(0), 32);				// tile address 0
	swiCopy(moleTL, BG_TILE_RAM_SUB(0) + 32, 32);		// tile address 1
	swiCopy(moleTR, BG_TILE_RAM_SUB(0) + 64, 32);		// tile address 2
	swiCopy(empty, BG_TILE_RAM_SUB(0) + 96, 32);		// tile address 3

}

void InitMap()
{
	BG_PALETTE_SUB[255] = ARGB16(1, 17, 20, 0);			// Brown colour for Mole
	BG_PALETTE_SUB[254] = ARGB16(1, 0, 0, 0);			// Black for eyes

	int i,j;
	for(i = 0; i<24; i++)
		for(j = 0; j<32; j++)
			BG_MAP_RAM_SUB(24)[i * 32 + j] = 3;
}

void PlaceMole(int id)
{
	switch(id)
	{
		case TL:														// Remove previous mole and add a new one
			RemoveMole(row, col);
			row = TOPROW;
			col = TBLCOL;
			DrawMole(row, col);
			break;

		case TR:
			RemoveMole(row, col);
			row = TOPROW;
			col = TBRCOL;
			DrawMole(row, col);
			break;

		case L:
			RemoveMole(row, col);
			row = MIDROW;
			col = LCOL;
			DrawMole(row, col);
			break;

		case M:
			RemoveMole(row, col);
			row = MIDROW;
			col = MIDCOL;
			DrawMole(row, col);
			break;

		case R:
			RemoveMole(row, col);
			row = MIDROW;
			col = RCOL;
			DrawMole(row, col);
			break;

		case BL:
			RemoveMole(row, col);
			row = BOTROW;
			col = TBLCOL;
			DrawMole(row, col);
			break;

		case BR:
			RemoveMole(row, col);
			row = BOTROW;
			col = TBRCOL;
			DrawMole(row, col);
			break;
	}
}

void DrawMole(int row, int col)
{
	BG_MAP_RAM_SUB(24)[row * 32 + col] = 1;							// Top 2 tiles are the head
	BG_MAP_RAM_SUB(24)[row * 32 + col + 1] = 2;

	BG_MAP_RAM_SUB(24)[(row + 1) * 32 + col] = 0;					// Bottom 2 tiles are the body
	BG_MAP_RAM_SUB(24)[(row + 1) * 32 + col + 1] = 0;
}


void RemoveMole(int row, int col)
{
	BG_MAP_RAM_SUB(24)[row * 32 + col] = 3;							// Add transparent tiles instead of coloured ones
	BG_MAP_RAM_SUB(24)[row * 32 + col + 1] = 3;

	BG_MAP_RAM_SUB(24)[(row + 1) * 32 + col] = 3;
	BG_MAP_RAM_SUB(24)[(row + 1) * 32 + col + 1] = 3;
}
