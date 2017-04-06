#include <stdlib.h>
#include "myLib.h"
#include "text.h"
#include "titleScreen.h"
#include "screen1.h"
#include "sAndB.h"
#include "level.h"
#include "wasteland.h"
#include "gameover.h"
#include <stdio.h>
#include <string.h>



int main () {

	ObjAttr shadow[128];

    //create sprite
    Sprite spr[NUMSPR] = {{80, 120, SPRITEUP1_ID, SPRITEUP1_SPRITE_SHAPE, SPRITEUP1_SPRITE_SIZE, 16, 16, 1, 1}, {30, 30, BOULDER_ID, BOULDER_SPRITE_SHAPE, BOULDER_SPRITE_SIZE, 16, 16, 1, 1}};
	
	//allocate player's health
	int *healthptr = malloc(sizeof(int));
	*healthptr = 200;
	
	
    //setup register display
    REG_DISPCNT = MODE3 | BG2_ENABLE | OBJ_ENABLE | SANDB_DIMENSION_TYPE;

    //copy palette to SPRITEPAL
    DMA[DMA_CHANNEL_3].src = sAndB_palette;
    DMA[DMA_CHANNEL_3].dst = SPRITEPAL;
    DMA[DMA_CHANNEL_3].cnt = SANDB_PALETTE_SIZE | DMA_ON;

    //copy data to CHARBLOCKBASE[5]
    DMA[DMA_CHANNEL_3].src = sAndB;
    DMA[DMA_CHANNEL_3].dst = &CHARBLOCKBASE[5];
    DMA[DMA_CHANNEL_3].cnt = SANDB_SIZE | DMA_ON;
    
    for(int i=0; i<NUMSPR; i++) {
        shadow[i].attr0 = spr[i].row | SANDB_PALETTE_TYPE | spr[i].shape;
        shadow[i].attr1 = spr[i].col | spr[i].size;
        shadow[i].attr2 = spr[i].start;
    }

    //hide all sprites
    for(int i = 0; i < 128; i++) {
        shadow[i].attr0 = ATTR0_HIDE;
    }

    //game screens
    typedef enum {
        TITLE,
        NODRAW,
        LEVEL,
        GAMEOVER,
        OPTIONS,
        SCREEN1,
        SCREEN2,
    } GameState;

    //variables for game
    GameState state = TITLE;
    GameState previousState;
    int aPressed;
    int bPressed;
    int upPressed;
    int downPressed;
    int selectPressed;
    int cursor = 0;
    int titleX = 90;
    int titleY = 100;
    char titleStr1[10] = "Start Game";
    char titleStr2[7] = "Options";
    char *titleStrShow;
    char buffer[100];
    sprintf(buffer, "Health: %d", *healthptr);
    
    //start game loop
    while (1) {
        waitForVblank();
        switch(state) {
        case TITLE:
            drawImage3(0, 0, TITLESCREEN_WIDTH, TITLESCREEN_HEIGHT, titleScreen);
            drawString(100, 90, "Start Game", BLACK);
            drawString(120, 100, "Options", BLACK);
            if ((cursor % 2) == 0) {
                titleX = 90;
                titleY = 100;
                titleStrShow = titleStr1;
                drawString(titleY, titleX, titleStrShow, WHITE);
            } else if ((cursor % 2) == 1) {
                titleX = 100;
                titleY = 120;
                titleStrShow = titleStr2;
                drawString(titleY, titleX, titleStrShow, WHITE);
            }
            previousState = TITLE;
            state = NODRAW;
            break;
        case NODRAW:
            if (!KEY_DOWN_NOW(BUTTON_SELECT)) {
                selectPressed = 0;
            }
            if (!KEY_DOWN_NOW(BUTTON_A)) {
                aPressed = 0;
            }
            if (!KEY_DOWN_NOW(BUTTON_B)) {
                bPressed = 0;
            }
            if (!KEY_DOWN_NOW(BUTTON_UP)) {
                upPressed = 0;
            }
            if (!KEY_DOWN_NOW(BUTTON_DOWN)) {
                downPressed = 0;
            }
            if (previousState == TITLE) {
                if (!aPressed && KEY_DOWN_NOW(BUTTON_A)) {
                    aPressed = 1;
                    if (titleStrShow == titleStr1) {
                        state = LEVEL;
                    } else if (titleStrShow == titleStr2) {
                        state = OPTIONS;
                    }
                } else if (!upPressed && KEY_DOWN_NOW(BUTTON_UP)) {
                    upPressed = 1;
                    cursor++;
                    state = TITLE;
                } else if (!downPressed && KEY_DOWN_NOW(BUTTON_DOWN)) {
                    downPressed = 1;
                    cursor++;
                    state = TITLE;
                }
            } else if (previousState == LEVEL) {
            	if (!aPressed && KEY_DOWN_NOW(BUTTON_A)) {
                    aPressed = 1;
                    state = SCREEN1;
                }
            } else if (previousState == OPTIONS) {
                if (!bPressed && KEY_DOWN_NOW(BUTTON_B)) {
                    bPressed = 1;
                    state = TITLE;
                }
            } else if (previousState == SCREEN1) {
            	if (KEY_DOWN_NOW(BUTTON_LEFT)) {
	            	if (collisionLeft(spr, healthptr)) {
	                	spr[0].col -= spr[0].cdel;
	                	if (spr[0].col < 0) {
	                		state = SCREEN2;
	                	}
	                	state = SCREEN1;
	                }
	            }
	            if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
	            	if (collisionRight(spr, healthptr)) {
	                	spr[0].col += spr[0].cdel;
	                	if (spr[0].col > 230) {
	                		state = SCREEN2;
	                	}
	                	state = SCREEN1;
	                }
	            }
	            if (KEY_DOWN_NOW(BUTTON_UP)) {
       				if (collisionUp(spr, healthptr)) {
		                spr[0].row -= spr[0].rdel;
		                if (spr[0].row < 0) {
		                	state = SCREEN2;
		                }
		                state = SCREEN1;
		            }
	            }
	            if (KEY_DOWN_NOW(BUTTON_DOWN)) {
            		if (collisionDown(spr, healthptr)) {
		                spr[0].row += spr[0].rdel;
		                state = SCREEN1;
		            }
	            }
	            if (*healthptr <= 0) {
	            	state = GAMEOVER;
	            }
	            if (spr[0].row > 145) {
	            	spr[0].row = 1;
	            	state = SCREEN2;
	            }
	            if (spr[0].row < 1) {
	            	spr[0].row = 145;
	            	state = SCREEN2;
	            }
	            if (spr[0].col > 224) {
	            	spr[0].col = 1;
	            	state = SCREEN2;
	            }
	            if (spr[0].col < 1) {
	            	spr[0].col = 224;
	            	state = SCREEN2;
	            }
            } else if (previousState == SCREEN2) {
            	if (KEY_DOWN_NOW(BUTTON_LEFT)) {
	            	if (collisionLeft(spr, healthptr)) {
	                	spr[0].col -= spr[0].cdel;
	                	if (spr[0].col < 0) {
	                		state = SCREEN1;
	                	}
	                	state = SCREEN2;
	                }
	            }
	            
	            if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
	            	if (collisionRight(spr, healthptr)) {
	                	spr[0].col += spr[0].cdel;
	                	if (spr[0].col > 230) {
	                		state = SCREEN1;
	                	}
	                	state = SCREEN2;
	                }
	            }
	            if (KEY_DOWN_NOW(BUTTON_UP)) {
       				if (collisionUp(spr, healthptr)) {
		                spr[0].row -= spr[0].rdel;
		                if (spr[0].row < 0) {
		                	state = SCREEN1;
		                }
		                state = SCREEN2;
		            }
	            }
	            if (KEY_DOWN_NOW(BUTTON_DOWN)) {
            		if (collisionDown(spr, healthptr)) {
		                spr[0].row += spr[0].rdel;
		                if (spr[0].row > 150) {
		                	state = SCREEN1;
		                }
		                state = SCREEN2;
		            }
	            }
	            if (*healthptr <= 0) {
	            	state = GAMEOVER;
	            }
	            if (spr[0].row > 145) {
	            	spr[0].row = 1;
	            	state = SCREEN1;
	            }
	            if (spr[0].row < 1) {
	            	spr[0].row = 145;
	            	state = SCREEN1;
	            }
	            if (spr[0].col > 224) {
	            	spr[0].col = 1;
	            	state = SCREEN1;
	            }
	            if (spr[0].col < 1) {
	            	spr[0].col = 224;
	            	state = SCREEN1;
	            }
            } else if (previousState == GAMEOVER) {
            	if (!aPressed && KEY_DOWN_NOW(BUTTON_A)) {
                    aPressed = 1;
                    cursor = 0;
                    *healthptr = 200;
	                spr[0].row = 80;
    	            spr[0].col = 120;
    	            for(int i = 0; i < 128; i++) {
				        shadow[i].attr0 = ATTR0_HIDE;
    				}
    				DMA[DMA_CHANNEL_3].src = shadow;
		        	DMA[DMA_CHANNEL_3].dst = SPRITEMEM;
    		    	DMA[DMA_CHANNEL_3].cnt = (NUMSPR*sizeof(ObjAttr)/2) | DMA_ON;
    	            state = TITLE;
                }
            }
            if (!selectPressed && KEY_DOWN_NOW(BUTTON_SELECT)) {
                selectPressed = 1;
                cursor = 0;
                *healthptr = 200;
                spr[0].row = 80;
                spr[0].col = 120;
                for(int i = 0; i < 128; i++) {
			        shadow[i].attr0 = ATTR0_HIDE;
    			}
    			DMA[DMA_CHANNEL_3].src = shadow;
	        	DMA[DMA_CHANNEL_3].dst = SPRITEMEM;
    	    	DMA[DMA_CHANNEL_3].cnt = (NUMSPR*sizeof(ObjAttr)/2) | DMA_ON;
                state = TITLE;
            }
            break;
        case LEVEL:
        	fillScreen3(WHITE);
        	drawImage3(0, 0, LEVEL_WIDTH, LEVEL_HEIGHT, level);
        	previousState = LEVEL;
        	state = NODRAW;
        	break;
        case GAMEOVER:
			drawImage3(0, 0, GAMEOVER_WIDTH, GAMEOVER_HEIGHT, gameover);
			drawString(110, 40, "Press A to go ", WHITE);
			drawString(120, 40, "to the title screen.", WHITE);
			previousState = GAMEOVER;
			state = NODRAW;
            break;
        case OPTIONS:
            fillScreen3(RED);
            drawString(5, 50, "Button Configurations", BLACK);
            drawString(20, 20, "Z ---------> A", BLACK);
            drawString(30, 20, "X ---------> B", BLACK);
            drawString(40, 20, "A ---------> L", BLACK);
            drawString(50, 20, "S ---------> R", BLACK);
            drawString(60, 20, "Enter -----> Start", BLACK);
            drawString(70, 20, "Backspace -> Select", BLACK);
            drawString(90, 20, "Pressing Select will reset the game.", BLACK);
            drawString(110, 50, "Press B to go back.", BLACK);
            previousState = OPTIONS;
            state = NODRAW;
            break;
        case SCREEN1:
            drawImage3(0, 0, SCREEN1_WIDTH, SCREEN1_HEIGHT, screen1);
            //drawString(0, 0, buffer, BLUE);
            for(int i=0; i<NUMSPR; i++) {
    	        shadow[i].attr0 = (ROWMASK&spr[i].row) | ATTR0_8BPP | spr[i].shape;
	            shadow[i].attr1 = (COLMASK&spr[i].col) | spr[i].size;
            	shadow[i].attr2 = spr[i].start;
        	}
            DMA[DMA_CHANNEL_3].src = shadow;
        	DMA[DMA_CHANNEL_3].dst = SPRITEMEM;
        	DMA[DMA_CHANNEL_3].cnt = (NUMSPR*sizeof(ObjAttr)/2) | DMA_ON;
            previousState = SCREEN1;
            state = NODRAW;
            break;
        case SCREEN2:
        	drawImage3(0, 0, WASTELAND_WIDTH, WASTELAND_HEIGHT, wasteland);
        	for(int i=0; i<NUMSPR; i++) {
    	        shadow[i].attr0 = (ROWMASK&spr[i].row) | ATTR0_8BPP | spr[i].shape;
	            shadow[i].attr1 = (COLMASK&spr[i].col) | spr[i].size;
            	shadow[i].attr2 = spr[i].start;
        	}
            DMA[DMA_CHANNEL_3].src = shadow;
        	DMA[DMA_CHANNEL_3].dst = SPRITEMEM;
        	DMA[DMA_CHANNEL_3].cnt = (NUMSPR*sizeof(ObjAttr)/2) | DMA_ON;
            previousState = SCREEN2;
            state = NODRAW;
            break;

        }
    }	//end game loop
    
	free(healthptr);
}


