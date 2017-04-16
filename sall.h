/*
 * Exported with nin10kit v1.4
 * Invocation command was nin10kit -mode=sprites -bpp=8 -for_bitmap=1 -transparent=FFFFFF sall spriteright1.bmp spriteright2.bmp spriteright3.bmp spriteleft1.bmp spriteleft2.bmp spriteleft3.bmp spriteup1.bmp spriteup2.bmp spriteup3.bmp spritedown1.bmp spritedown2.bmp spritedown3.bmp boulder.jpg 
 * Time-stamp: Saturday 04/15/2017, 10:51:16
 * 
 * Image Information
 * -----------------
 * spriteright1.bmp 16@16
 * spriteright2.bmp 16@16
 * spriteright3.bmp 16@16
 * spriteleft1.bmp 16@16
 * spriteleft2.bmp 16@16
 * spriteleft3.bmp 16@16
 * spriteup1.bmp 16@16
 * spriteup2.bmp 16@16
 * spriteup3.bmp 16@16
 * spritedown1.bmp 16@16
 * spritedown2.bmp 16@16
 * spritedown3.bmp 16@16
 * boulder.jpg 16@16
 * Transparent color: (255, 255, 255)
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * 
 * All bug reports / feature requests are to be sent to Brandon (bwhitehead0308@gmail.com)
 */

#ifndef SALL_H
#define SALL_H

#define SALL_TRANSPARENT 0x00

#define SALL_PALETTE_TYPE (1 << 13)
#define SALL_DIMENSION_TYPE (1 << 6)

extern const unsigned short sall_palette[63];
#define SALL_PALETTE_SIZE 63

extern const unsigned short sall[1664];
#define SALL_SIZE 1664

#define SPRITERIGHT1_SPRITE_SHAPE (0 << 14)
#define SPRITERIGHT1_SPRITE_SIZE (1 << 14)
#define SPRITERIGHT1_ID 512

#define SPRITERIGHT2_SPRITE_SHAPE (0 << 14)
#define SPRITERIGHT2_SPRITE_SIZE (1 << 14)
#define SPRITERIGHT2_ID 520

#define SPRITERIGHT3_SPRITE_SHAPE (0 << 14)
#define SPRITERIGHT3_SPRITE_SIZE (1 << 14)
#define SPRITERIGHT3_ID 528

#define SPRITELEFT1_SPRITE_SHAPE (0 << 14)
#define SPRITELEFT1_SPRITE_SIZE (1 << 14)
#define SPRITELEFT1_ID 536

#define SPRITELEFT2_SPRITE_SHAPE (0 << 14)
#define SPRITELEFT2_SPRITE_SIZE (1 << 14)
#define SPRITELEFT2_ID 544

#define SPRITELEFT3_SPRITE_SHAPE (0 << 14)
#define SPRITELEFT3_SPRITE_SIZE (1 << 14)
#define SPRITELEFT3_ID 552

#define SPRITEUP1_SPRITE_SHAPE (0 << 14)
#define SPRITEUP1_SPRITE_SIZE (1 << 14)
#define SPRITEUP1_ID 560

#define SPRITEUP2_SPRITE_SHAPE (0 << 14)
#define SPRITEUP2_SPRITE_SIZE (1 << 14)
#define SPRITEUP2_ID 568

#define SPRITEUP3_SPRITE_SHAPE (0 << 14)
#define SPRITEUP3_SPRITE_SIZE (1 << 14)
#define SPRITEUP3_ID 576

#define SPRITEDOWN1_SPRITE_SHAPE (0 << 14)
#define SPRITEDOWN1_SPRITE_SIZE (1 << 14)
#define SPRITEDOWN1_ID 584

#define SPRITEDOWN2_SPRITE_SHAPE (0 << 14)
#define SPRITEDOWN2_SPRITE_SIZE (1 << 14)
#define SPRITEDOWN2_ID 592

#define SPRITEDOWN3_SPRITE_SHAPE (0 << 14)
#define SPRITEDOWN3_SPRITE_SIZE (1 << 14)
#define SPRITEDOWN3_ID 600

#define BOULDER_SPRITE_SHAPE (0 << 14)
#define BOULDER_SPRITE_SIZE (1 << 14)
#define BOULDER_ID 608

#endif

