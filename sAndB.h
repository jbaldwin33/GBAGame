/*
 * Exported with nin10kit v1.4
 * Invocation command was nin10kit -mode=sprites -bpp=8 -for_bitmap=1 -transparent=FFFFFF sAndB spriteup1.bmp boulder.jpg 
 * Time-stamp: Monday 04/03/2017, 19:34:48
 * 
 * Image Information
 * -----------------
 * spriteup1.bmp 16@16
 * boulder.jpg 16@16
 * Transparent color: (255, 255, 255)
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef SANDB_H
#define SANDB_H

#define SANDB_TRANSPARENT 0x00

#define SANDB_PALETTE_TYPE (1 << 13)
#define SANDB_DIMENSION_TYPE (1 << 6)

extern const unsigned short sAndB_palette[63];
#define SANDB_PALETTE_SIZE 63

extern const unsigned short sAndB[256];
#define SANDB_SIZE 256

#define SPRITEUP1_SPRITE_SHAPE (0 << 14)
#define SPRITEUP1_SPRITE_SIZE (1 << 14)
#define SPRITEUP1_ID 512

#define BOULDER_SPRITE_SHAPE (0 << 14)
#define BOULDER_SPRITE_SIZE (1 << 14)
#define BOULDER_ID 520

#endif

