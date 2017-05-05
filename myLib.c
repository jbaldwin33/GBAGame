#include "myLib.h"
#include "screen1.h"
#include "text.h"
#include "wasteland.h"
#include <stdio.h>
#include <stdlib.h>

u16 *videoBuffer = (u16 *)0x6000000;

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 159);
}

void drawImage3(int row, int col, int width, int height, const u16 *image)
{
	for (int r=row;r<height;r++) {
		DMA[DMA_CHANNEL_3].src = image+OFFSET(r,col,width);
		DMA[DMA_CHANNEL_3].dst = videoBuffer+OFFSET(r,col,240);
		DMA[DMA_CHANNEL_3].cnt = width | DMA_ON;
	}
}

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int r = 0; r<height; r++)
	{
		for(int c=0; c<width; c++)
		{
			setPixel(r+row, c+col, color);
		}
	}
}

void setPixel(int row, int col, u16 color)
{
		videoBuffer[OFFSET(row, col, 240)] = color;
}

void fillScreen3(unsigned short color)
{
	DMA[DMA_CHANNEL_3].src = &color;
	DMA[DMA_CHANNEL_3].dst = videoBuffer;
	DMA[DMA_CHANNEL_3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED;
}

int collisionLeftHelper(Sprite *spr, int* health) {
	for (int i = NUMSPR - NUMOBJ; i < NUMSPR; i++) {
       	if (collisionLeft(i, spr, health)) {
       		return 1;
       	}
    }
    return 0;
}

int collisionRightHelper(Sprite *spr, int* health) {
	for (int i = NUMSPR - NUMOBJ; i < NUMSPR; i++) {
       	if (collisionRight(i, spr, health)) {
       		return 1;
       	}
    }
    return 0;
}

int collisionUpHelper(Sprite *spr, int* health) {
	for (int i = NUMSPR - NUMOBJ; i < NUMSPR; i++) {
       	if (collisionUp(i, spr, health)) {
       		return 1;
       	}
    }
    return 0;
}

int collisionDownHelper(Sprite *spr, int* health) {
	for (int i = NUMSPR - NUMOBJ; i < NUMSPR; i++) {
       	if (collisionDown(i, spr, health)) {
       		return 1;
       	}
    }
    return 0;
}

int collisionLeft(int i, Sprite *spr, int* health)
{	
	if ((spr[0].col > spr[i].col + spr[i].width) || (spr[0].row + spr[0].height <= spr[i].row) 
	|| (spr[0].row >= spr[i].row + spr[i].height) || (spr[0].col + spr[0].width <= spr[i].col)) {
		return 0;
	}
	(*health)--;
	return 1;
}

int collisionRight(int i, Sprite *spr, int* health) {	
	if ((spr[0].row + spr[0].height <= spr[i].row) || (spr[0].row >= spr[i].row + spr[i].height)
	|| (spr[0].col + spr[0].width < spr[i].col) || (spr[0].col >= spr[i].col + spr[i].width)) {
		return 0;
	}
	(*health)--;
	return 1;
}

int collisionUp(int i, Sprite *spr, int* health) {
	if ((spr[0].row > spr[i].row + spr[i].height) || (spr[0].col + spr[0].width <= spr[i].col) 
	|| (spr[0].col >= spr[i].col + spr[i].width) || (spr[0].row + spr[0].height <= spr[i].row)) {
		return 0;
	}
	(*health)--;
	return 1;
}

int collisionDown(int i, Sprite *spr, int* health) {
	if ((spr[0].row + spr[0].height < spr[i].row) || (spr[0].col >= spr[i].col + spr[i].width) 
	|| (spr[0].col + spr[0].width <= spr[i].col) || (spr[0].row >= spr[i].row + spr[i].height)) {
		return 0;
	}
	(*health)--;
	return 1;
}

void setupScreen1(int* health, char* buffer) {
	drawImage3(0, 0, SCREEN1_WIDTH, SCREEN1_HEIGHT, screen1);
	drawRect(0, 0, 8, 70, WHITE);
    sprintf(buffer, "Health: %d", *health);
    drawString(0, 0, buffer, BLUE);
}

void setupScreen2(int* health, char* buffer) {
	drawImage3(0, 0, WASTELAND_WIDTH, WASTELAND_HEIGHT, wasteland);
	drawRect(0, 0, 8, 70, WHITE);
    sprintf(buffer, "Health: %d", *health);
    drawString(0, 0, buffer, BLUE);
}

typedef enum {
	up,
	down,
	left,
	right
} dir;

void updatePosition(Sprite* e) {
	int posX = e[0].col;
	int posY = e[0].row;
	if (e[NUMSPR-1].col > posX) {
		e[NUMSPR-1].col--;
	} else if (e[NUMSPR-1].col < posX) {
		e[NUMSPR-1].col++;
	}
	if (e[NUMSPR-1].row > posY) {
		e[NUMSPR-1].row--;
	} else if (e[NUMSPR-1].row < posY) {
		e[NUMSPR-1].row++;
	}
	
	
	
	
	
	
	/*int r = rand() % 7;
	switch(e[NUMSPR - 1].direction) {
	case 0:
		for (int i = 0; i < r; i++) {
			e[NUMSPR - 1].col += i;
		}
		break;
	case 1:
		for (int i = 0; i < r; i++) {
			e[NUMSPR - 1].col -= i;
		}
		break;
	case 2:
		for (int i = 0; i < r; i++) {
			e[NUMSPR - 1].row -= i;
		}
		break;
	case 3:
		for (int i = 0; i < r; i++) {
			e[NUMSPR - 1].row += i;
		}
		break;
	}
	for (int i = 0; i < 1000; i++) {
		e[NUMSPR - 1].row = e[NUMSPR - 1].row;
	}*/
}

void updateDirection(Sprite* e) {
	int r = (rand() - rand()) % 4;
	e[NUMSPR - 1].direction = r;
}



/*void randomMovement(Sprite* spr) {
	//int randX = rand() % 239;
	//int randY = rand() % 159;
	dir dir;// = up;
	int r = rand();
	if ((r % 12) == 7) {
		dir = up;
	} else if ((r % 12) == 9) {
		dir = down;
	} else if ((r % 12) == 5) {
		dir = left;
	} else if ((r % 12) == 6) {
		dir = right;
	}
	switch(dir) {
		case up:
			spr[3].row--;
			break;
		case down:
			spr[3].row++;
			break;
		case left:
			spr[3].col--;
			break;
		case right:
			spr[3].col++;
			break;
	}*/
	
	/*if (spr[3].row != randY || spr[3].col != randX) {
		if (randX > spr[3].col) {
			spr[3].col++;
		} else if (randX < spr[3].col) {
			spr[3].col--;
		}
		if (randY > spr[3].row) {
			spr[3].row++;
		} else if (randY < spr[3].row) {
			spr[3].row--;
		}
	}*/
	/*if ((r % 4) == 0) {
		spr[3].row--;
	} else if ((r % 4) == 1) {
		spr[3].row--;
	} else if ((r % 4) == 2) {
		spr[3].col++;
	} else if ((r % 4) == 3) {
		spr[3].col--;
	} 
}*/
