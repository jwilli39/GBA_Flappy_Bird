// gba.h

#ifndef GBA_H
#define GBA_H

// screen dimensions
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

// display modes
#define MODE0 0x00
#define MODE1 0x01
#define MODE2 0x02
#define MODE3 0x03

// background enable flags
#define BG0_ENABLE 0x100
#define BG1_ENABLE 0x200
#define BG2_ENABLE 0x400
#define BG3_ENABLE 0x800

// sprite display flags
#define SPRITE_ENABLE 0x1000
#define SPRITE_MAP_2D 0x0
#define SPRITE_MAP_1D 0x40

// palette size constant
#define PALETTE_SIZE 256

// max number of sprites
#define NUM_SPRITES 128

// DMA transfer flags
#define DMA_ENABLE 0x80000000
#define DMA_16     0x00000000
#define DMA_32     0x04000000

// button masks
#define BUTTON_A      (1 << 0)
#define BUTTON_B      (1 << 1)
#define BUTTON_SELECT (1 << 2)
#define BUTTON_START  (1 << 3)
#define BUTTON_RIGHT  (1 << 4)
#define BUTTON_LEFT   (1 << 5)
#define BUTTON_UP     (1 << 6)
#define BUTTON_DOWN   (1 << 7)
#define BUTTON_R      (1 << 8)
#define BUTTON_L      (1 << 9)

// hardware register pointers
extern volatile unsigned short* bg0_control;
extern volatile unsigned short* bg1_control;
extern volatile unsigned short* bg2_control;
extern volatile unsigned short* bg3_control;

extern volatile unsigned long*  display_control;
extern volatile unsigned short* sprite_attribute_memory;
extern volatile unsigned short* sprite_image_memory;
extern volatile unsigned short* bg_palette;
extern volatile unsigned short* sprite_palette;
extern volatile unsigned short* buttons;
extern volatile unsigned short* scanline_counter;

extern volatile short* bg0_x_scroll;
extern volatile short* bg0_y_scroll;

extern volatile unsigned int* dma_source;
extern volatile unsigned int* dma_destination;
extern volatile unsigned int* dma_count;

// utility functions
void wait_vblank();
unsigned char button_pressed(unsigned short button);
volatile unsigned short* char_block(unsigned long block);
volatile unsigned short* screen_block(unsigned long block);
void memcpy16_dma(unsigned short* dest, unsigned short* source, int amount);

#endif
