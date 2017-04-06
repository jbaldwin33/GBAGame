/*
 * Exported with nin10kit v1.4
 * Invocation command was nin10kit -mode=sprites -bpp=8 -for_bitmap=1 boulder boulder.jpg 
 * Time-stamp: Monday 04/03/2017, 19:05:58
 * 
 * Image Information
 * -----------------
 * boulder.jpg 16@16
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef BOULDER_H
#define BOULDER_H

#define BOULDER_PALETTE_TYPE (1 << 13)
#define BOULDER_DIMENSION_TYPE (1 << 6)

extern const unsigned short boulder_palette[61];
#define BOULDER_PALETTE_SIZE 61

extern const unsigned short boulder[128];
#define BOULDER_SIZE 128

#define BOULDER_SPRITE_SHAPE (0 << 14)
#define BOULDER_SPRITE_SIZE (1 << 14)
#define BOULDER_ID 512

#endif

