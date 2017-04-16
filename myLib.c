#include "myLib.h"

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

int collisionLeft(Sprite *spr, int* health)
{	
	if ((spr[0].col > spr[1].col+spr[1].width) || (spr[0].row+spr[0].height <= spr[1].row)
	|| (spr[0].row >= spr[1].row+spr[1].height) || ( (spr[0].row <= spr[1].row+spr[1].height) 
	&& (spr[0].row+spr[0].height >= spr[1].row) && (spr[0].col+spr[0].width <= spr[1].col))) {	
		return 1;
	}
	(*health)--;
	return 0;
}

int collisionRight(Sprite *spr, int* health) {	
	if ((spr[0].row+spr[0].height <= spr[1].row) || (spr[0].col+spr[0].width < spr[1].col) 
	|| (spr[0].row >= spr[1].row+spr[1].height) || ((spr[0].row < spr[1].row+spr[1].height) 
	&& (spr[0].row+spr[0].height > spr[1].row) && (spr[0].col >= spr[1].col+spr[1].width))) {
		return 1;
	}
	(*health)--;
	return 0;
}

int collisionUp(Sprite *spr, int* health) {
	if ((spr[0].row > spr[1].row+spr[1].height) || (spr[0].col+spr[0].width <= spr[1].col) 
	|| (spr[0].col >= spr[1].col+spr[1].width) || ((spr[0].col+spr[0].width > spr[1].col) 
	&& (spr[0].col < spr[1].col+spr[1].width) && (spr[0].row+spr[0].height <= spr[1].row))) {
		return 1;
	}
	(*health)--;
	return 0;
}

int collisionDown(Sprite *spr, int* health) {
	if ((spr[0].row+spr[0].height < spr[1].row) || (spr[0].col+spr[0].width <= spr[1].col) 
	|| (spr[0].col >= spr[1].col+spr[1].width) || ((spr[0].row >= spr[1].row+spr[1].height) 
	&& (spr[0].col+spr[0].width > spr[1].col) && (spr[0].col < spr[1].col+spr[1].width))) {
		return 1;
	}
	(*health)--;
	return 0;
}
