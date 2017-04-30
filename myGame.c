#include <stdlib.h>
#include "myLib.h"
#include "text.h"
#include "titleScreen.h"
#include "screen1.h"
#include "sall.h"
#include "level.h"
#include "wasteland.h"
#include "gameover.h"
#include <stdio.h>
#include <string.h>



int main () {

	ObjAttr shadow[128];

    //create sprite
    //Sprite obj[2] = {{30, 30, BOULDER_ID, BOULDER_SPRITE_SHAPE, BOULDER_SPRITE_SIZE, 16, 16, 1, 1, 1}, {80, 80, BOULDER_ID, BOULDER_SPRITE_SHAPE, BOULDER_SPRITE_SIZE, 16, 16, 1, 1, 1}};
	
	
	Sprite sR[NUMSPR + NUMOBJ] = {{80, 120, SPRITERIGHT1_ID, SPRITERIGHT1_SPRITE_SHAPE, SPRITERIGHT1_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 0}, {80, 120, SPRITERIGHT2_ID, SPRITERIGHT2_SPRITE_SHAPE, SPRITERIGHT2_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 0}, {80, 120, SPRITERIGHT3_ID, SPRITERIGHT3_SPRITE_SHAPE, SPRITERIGHT3_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 0}, {80, 120, SPRITELEFT1_ID, SPRITELEFT1_SPRITE_SHAPE, SPRITELEFT1_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 0}, {80, 120, SPRITELEFT2_ID, SPRITELEFT2_SPRITE_SHAPE, SPRITELEFT2_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 0}, {80, 120, SPRITELEFT3_ID, SPRITELEFT3_SPRITE_SHAPE, SPRITELEFT3_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 0}, {80, 120, SPRITEUP1_ID, SPRITEUP1_SPRITE_SHAPE, SPRITEUP1_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 0}, {80, 120, SPRITEUP2_ID, SPRITEUP2_SPRITE_SHAPE, SPRITEUP2_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 0}, {80, 120, SPRITEUP3_ID, SPRITEUP3_SPRITE_SHAPE, SPRITEUP3_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 0}, {80, 120, SPRITEDOWN1_ID, SPRITEDOWN1_SPRITE_SHAPE, SPRITEDOWN1_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 0}, {80, 120, SPRITEDOWN2_ID, SPRITEDOWN2_SPRITE_SHAPE, SPRITEDOWN2_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 0}, {80, 120, SPRITEDOWN3_ID, SPRITEDOWN3_SPRITE_SHAPE, SPRITEDOWN3_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 0}, {80, 80, BOULDER_ID, BOULDER_SPRITE_SHAPE, BOULDER_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 1}, {20, 20, BOULDER_ID, BOULDER_SPRITE_SHAPE, BOULDER_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 1}, {120, 120, SPRITEDOWN1_ID, SPRITEDOWN1_SPRITE_SHAPE, SPRITEDOWN1_SPRITE_SIZE, 16, 16, SPRSPEED, SPRSPEED, 0}};
	//allocate player's health
	int *healthptr = malloc(sizeof(int));
	*healthptr = 200;
	
	
    //setup register display
    REG_DISPCNT = MODE3 | BG2_ENABLE | OBJ_ENABLE | SALL_DIMENSION_TYPE;

    //copy palette to SPRITEPAL
    DMA[DMA_CHANNEL_3].src = sall_palette;
    DMA[DMA_CHANNEL_3].dst = SPRITEPAL;
    DMA[DMA_CHANNEL_3].cnt = SALL_PALETTE_SIZE | DMA_ON;

    //copy data to CHARBLOCKBASE[5]
    DMA[DMA_CHANNEL_3].src = sall;
    DMA[DMA_CHANNEL_3].dst = &CHARBLOCKBASE[5];
    DMA[DMA_CHANNEL_3].cnt = SALL_SIZE | DMA_ON;
    
    for(int i=0; i<NUMSPR; i++) {
        shadow[i].attr0 = sR[i].row | SALL_PALETTE_TYPE | sR[i].shape;
        shadow[i].attr1 = sR[i].col | sR[i].size;
        shadow[i].attr2 = sR[i].start;
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
    char titleStr1[10] = "Start Game";
    char titleStr2[7] = "Options";
    char *titleStrShow;
    char buffer[7];
    char buffer2[] = "   ";
    int oldHealth;
    
    int active = 0;
    int active2 = 0;
    int direc = 0;
    //start game loop
    while (1) {
        waitForVblank();
        if (active >=30) {
        	active = 0;
        }
        if (active2 >= 30) {
        	active2 = 0;
        }
        active2++;
        switch(state) {
        case TITLE:
            drawImage3(0, 0, TITLESCREEN_WIDTH, TITLESCREEN_HEIGHT, titleScreen);
            drawString(100, 90, "Start Game", BLACK);
            drawString(120, 100, "Options", BLACK);
            if ((cursor % 2) == 0) {
                titleStrShow = titleStr1;
                drawString(100, 90, "Start Game", WHITE);
            } else if ((cursor % 2) == 1) {
                titleStrShow = titleStr2;
                drawString(120, 100, "Options", WHITE);
            }
            previousState = TITLE;
            state = NODRAW;
            break;
        case NODRAW:
        	if ((active2%15) == 0) {
	        	updatePosition(sR);
	        }
        	//updateDirection(sR);
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
				shadow[NUMSPR-1].attr0 = (ROWMASK&sR[NUMSPR-1].row) | ATTR0_8BPP | sR[NUMSPR-1].shape;
		        shadow[NUMSPR-1].attr1 = (COLMASK&sR[NUMSPR-1].col) | sR[NUMSPR-1].size;
		    	shadow[NUMSPR-1].attr2 = sR[NUMSPR-1].start;
		        DMA[DMA_CHANNEL_3].src = shadow;
		    	DMA[DMA_CHANNEL_3].dst = SPRITEMEM;
		    	DMA[DMA_CHANNEL_3].cnt = (NUMSPR*sizeof(ObjAttr)/2) | DMA_ON;
            	if (KEY_DOWN_NOW(BUTTON_LEFT)) {
            		direc = 0;
            		active++;
            		if (oldHealth != *healthptr) {
    	        		sprintf(buffer2, "%d", *healthptr);
    	        		drawRect(0, 48, 8, 20, WHITE);
			            drawString(0, 48, buffer2, BLUE);
		            }
		            if (!collisionLeftHelper(sR, healthptr)) {
	            		oldHealth = *healthptr;
	                	for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
	                		sR[i].col -= sR[i].cdel;
	                	}
	                	if (sR[0].col < 0) {
	                		state = SCREEN2;
	                	}
                		state = SCREEN1;
               		}
	            }
	            if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
	            	direc = 1;
	            	active++;
	            	if (oldHealth != *healthptr) {
    	        		sprintf(buffer2, "%d", *healthptr);
    	        		drawRect(0, 48, 8, 20, WHITE);
			            drawString(0, 48, buffer2, BLUE);
		            }
	            	if (!collisionRightHelper(sR, healthptr)) {
	            		oldHealth = *healthptr;
	                	for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
		                	sR[i].col += sR[i].cdel;
		                }
	                	if (sR[0].col > 230) {
	                		state = SCREEN2;
	                	}
	                	state = SCREEN1;
	                }
	            }
	            if (KEY_DOWN_NOW(BUTTON_UP)) {
					direc = 2;
					active++;
	            	if (oldHealth != *healthptr) {
    	        		sprintf(buffer2, "%d", *healthptr);
    	        		drawRect(0, 48, 8, 20, WHITE);
			            drawString(0, 48, buffer2, BLUE);
		            }
       				if (!collisionUpHelper(sR, healthptr)) {
       					oldHealth = *healthptr;
       					for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
			                sR[i].row -= sR[i].rdel;
			            }
		                if (sR[0].row < 0) {
		                	state = SCREEN2;
		                }
		                state = SCREEN1;
		            }
	            }
	            if (KEY_DOWN_NOW(BUTTON_DOWN)) {
					direc = 3;
					active++;
	            	if (oldHealth != *healthptr) {
    	        		sprintf(buffer2, "%d", *healthptr);
    	        		drawRect(0, 48, 8, 20, WHITE);
			            drawString(0, 48, buffer2, BLUE);
		            }
            		if (!collisionDownHelper(sR, healthptr)) {
            			oldHealth = *healthptr;
            			for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
		                	sR[i].row += sR[i].rdel;
						}
		                if (sR[0].row > 150) {
		                	state = SCREEN2;
		                }
		                state = SCREEN1;
		            }
	            }
	            if (*healthptr <= 0) {
	            	state = GAMEOVER;
	            }
	            if (sR[0].row > 145) {
	            	for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
		            	sR[i].row = 1;
		            }
	            	state = SCREEN2;
	            }
	            if (sR[0].row < 1) {
	            	for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
		            	sR[i].row = 145;
		            }
	            	state = SCREEN2;
	            }
	            if (sR[0].col > 224) {
	            	for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
		            	sR[i].col = 1;
		            }
	            	state = SCREEN2;
	            }
	            if (sR[0].col < 1) {
	            	for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
	            		sR[i].col = 224;
	            	}
	            	state = SCREEN2;
	            }
            } else if (previousState == SCREEN2) {
            	if (KEY_DOWN_NOW(BUTTON_LEFT)) {
            		direc = 0;
            		active++;
            		if (oldHealth != *healthptr) {
    	        		sprintf(buffer2, "%d", *healthptr);
	            		drawRect(0, 48, 8, 20, WHITE);
		            	drawString(0, 48, buffer2, BLUE);
		            }
	            	if (!collisionLeftHelper(sR, healthptr)) {
	            		oldHealth = *healthptr;
	            		for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
		                	sR[i].col -= sR[i].cdel;
		                }
	                	if (sR[0].col < 0) {
	                		state = SCREEN1;
	                	}
	                	state = SCREEN2;
	                }
	            }
	            
	            if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
	            	direc = 1;
	            	active++;
	            	if (oldHealth != *healthptr) {
    	        		sprintf(buffer2, "%d", *healthptr);
    	        		drawRect(0, 48, 8, 20, WHITE);
			            drawString(0, 48, buffer2, BLUE);
		            }
	            	if (!collisionRightHelper(sR, healthptr)) {
	            		oldHealth = *healthptr;
	            		for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
		                	sR[i].col += sR[i].cdel;
		                }
	                	if (sR[0].col > 230) {
	                		state = SCREEN1;
	                	}
	                	state = SCREEN2;
	                }
	            }
	            if (KEY_DOWN_NOW(BUTTON_UP)) {
					direc = 2;
	            	active++;
	            	if (oldHealth != *healthptr) {
    	        		sprintf(buffer2, "%d", *healthptr);
    	        		drawRect(0, 48, 8, 20, WHITE);
			            drawString(0, 48, buffer2, BLUE);
		            }
       				if (!collisionUpHelper(sR, healthptr)) {
       					oldHealth = *healthptr;
       					for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
			                sR[i].row -= sR[i].rdel;
			            }
		                if (sR[0].row < 0) {
		                	state = SCREEN1;
		                }
		                state = SCREEN2;
		            }
	            }
	            if (KEY_DOWN_NOW(BUTTON_DOWN)) {
	            	direc = 3;
	            	active++;
	            	if (oldHealth != *healthptr) {
    	        		sprintf(buffer2, "%d", *healthptr);
    	        		drawRect(0, 48, 8, 20, WHITE);
			            drawString(0, 48, buffer2, BLUE);
		            }
            		if (!collisionDownHelper(sR, healthptr)) {
            			oldHealth = *healthptr;
            			for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
		                	sR[i].row += sR[i].rdel;
		                }
		                if (sR[0].row > 150) {
		                	state = SCREEN1;
		                }
		                state = SCREEN2;
		            }
	            }
	            if (*healthptr <= 0) {
	            	state = GAMEOVER;
	            }
	            if (sR[0].row > 145) {
	            	for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
		            	sR[i].row = 1;
		            }
	            	state = SCREEN1;
	            }
	            if (sR[0].row < 1) {
	            	for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
		            	sR[i].row = 145;
		            }
	            	state = SCREEN1;
	            }
	            if (sR[0].col > 224) {
	            	for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
		            	sR[i].col = 1;
		            }
	            	state = SCREEN1;
	            }
	            if (sR[0].col < 1) {
	            	for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
	            		sR[i].col = 224;
	            	}
	            	state = SCREEN1;
	            }
            } else if (previousState == GAMEOVER) {
            	if (!aPressed && KEY_DOWN_NOW(BUTTON_A)) {
                    aPressed = 1;
                    cursor = 0;
                    *healthptr = 200;
                    for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
		                sR[i].row = 80;
    		            sR[i].col = 120;
    		        }
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
                for (int i = 0; i < NUMSPR - NUMOBJ; i++) {
		            sR[i].row = 80;
    		        sR[i].col = 120;
    		    }
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
        	if (previousState != SCREEN1) {
        		setupScreen1(healthptr, buffer);
        	}
        	//updatePosition(sR);
        	//updateDirection(sR);
            for(int i=0; i<NUMSPR; i++) {
    	        shadow[i].attr0 = (ROWMASK&sR[i].row) | ATTR0_8BPP | sR[i].shape;
	            shadow[i].attr1 = (COLMASK&sR[i].col) | sR[i].size;
            	shadow[i].attr2 = sR[i].start;
        	}
        	if (active < 10 && direc == 1) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=0) {
	   	    			shadow[i].attr0 = ATTR0_HIDE;
	   	    		}
   	    		}
   	    	} else if (active >= 10 && active < 20 && direc == 1) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=1) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	} else if (active >= 20 && active < 30 && direc == 1) {
   	       		for (int i=0;i<12;i++) {
   	    			if (i!=2) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	}
        	if (active < 10 && direc == 0) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=3) {
    	    			shadow[i].attr0 = ATTR0_HIDE;
    	    		}
   	    		}
   	    	} else if (active >= 10 && active < 20 && direc == 0) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=4) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	} else if (active >= 20 && active < 30 && direc == 0) {
   	       		for (int i=0;i<12;i++) {
   	    			if (i!=5) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	}
           	if (active < 10 && direc == 2) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=6) {
    	    			shadow[i].attr0 = ATTR0_HIDE;
    	    		}
   	    		}
   	    	} else if (active >= 10 && active < 20 && direc == 2) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=7) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	} else if (active >= 20 && active < 30 && direc == 2) {
   	       		for (int i=0;i<12;i++) {
   	    			if (i!=8) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	}
   	    	if (active < 10 && direc == 3) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=9) {
    	    			shadow[i].attr0 = ATTR0_HIDE;
    	    		}
   	    		}
   	    	} else if (active >= 10 && active < 20 && direc == 3) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=10) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	} else if (active >= 20 && active < 30 && direc == 3) {
   	       		for (int i=0;i<12;i++) {
   	    			if (i!=11) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	}
        	
            DMA[DMA_CHANNEL_3].src = shadow;
        	DMA[DMA_CHANNEL_3].dst = SPRITEMEM;
        	DMA[DMA_CHANNEL_3].cnt = (NUMSPR*sizeof(ObjAttr)/2) | DMA_ON;
            previousState = SCREEN1;
            state = NODRAW;
            break;
        case SCREEN2:
        	if (previousState != SCREEN2) {
        		setupScreen2(healthptr, buffer);
        	}
        	for(int i=0; i<NUMSPR; i++) {
    	        shadow[i].attr0 = (ROWMASK&sR[i].row) | ATTR0_8BPP | sR[i].shape;
	            shadow[i].attr1 = (COLMASK&sR[i].col) | sR[i].size;
            	shadow[i].attr2 = sR[i].start;
        	}
			if (active < 10 && direc == 1) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=0) {
	   	    			shadow[i].attr0 = ATTR0_HIDE;
	   	    		}
   	    		}
   	    	} else if (active >= 10 && active < 20 && direc == 1) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=1) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	} else if (active >= 20 && active < 30 && direc == 1) {
   	       		for (int i=0;i<12;i++) {
   	    			if (i!=2) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	}
        	if (active < 10 && direc == 0) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=3) {
    	    			shadow[i].attr0 = ATTR0_HIDE;
    	    		}
   	    		}
   	    	} else if (active >= 10 && active < 20 && direc == 0) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=4) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	} else if (active >= 20 && active < 30 && direc == 0) {
   	       		for (int i=0;i<12;i++) {
   	    			if (i!=5) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	}
           	if (active < 10 && direc == 2) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=6) {
    	    			shadow[i].attr0 = ATTR0_HIDE;
    	    		}
   	    		}
   	    	} else if (active >= 10 && active < 20 && direc == 2) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=7) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	} else if (active >= 20 && active < 30 && direc == 2) {
   	       		for (int i=0;i<12;i++) {
   	    			if (i!=8) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	}
   	    	if (active < 10 && direc == 3) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=9) {
    	    			shadow[i].attr0 = ATTR0_HIDE;
    	    		}
   	    		}
   	    	} else if (active >= 10 && active < 20 && direc == 3) {
   	    		for (int i=0;i<12;i++) {
   	    			if (i!=10) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
   	    	} else if (active >= 20 && active < 30 && direc == 3) {
   	       		for (int i=0;i<12;i++) {
   	    			if (i!=11) {
   	    				shadow[i].attr0 = ATTR0_HIDE;
   	    			}
   	    		}
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


