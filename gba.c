// gba.c
// Implements GBA hardware register access and utility functions

#include "gba.h"

// background control registers
volatile unsigned short* bg0_control = (volatile unsigned short*)0x4000008;
volatile unsigned short* bg1_control = (volatile unsigned short*)0x400000A;
volatile unsigned short* bg2_control = (volatile unsigned short*)0x400000C;
volatile unsigned short* bg3_control = (volatile unsigned short*)0x400000E;

// display control register
volatile unsigned long* display_control = (volatile unsigned long*)0x4000000;

// sprite-related memory locations
volatile unsigned short* sprite_attribute_memory = (volatile unsigned short*)0x7000000;
volatile unsigned short* sprite_image_memory     = (volatile unsigned short*)0x6010000;

// palette memory
volatile unsigned short* bg_palette     = (volatile unsigned short*)0x5000000;
volatile unsigned short* sprite_palette = (volatile unsigned short*)0x5000200;

// button input register
volatile unsigned short* buttons = (volatile unsigned short*)0x04000130;

// scanline counter (used for vblank wait)
volatile unsigned short* scanline_counter = (volatile unsigned short*)0x4000006;

// background scroll registers
volatile short* bg0_x_scroll = (volatile short*)0x4000010;
volatile short* bg0_y_scroll = (volatile short*)0x4000012;

// DMA registers
volatile unsigned int* dma_source      = (volatile unsigned int*)0x40000D4;
volatile unsigned int* dma_destination = (volatile unsigned int*)0x40000D8;
volatile unsigned int* dma_count       = (volatile unsigned int*)0x40000DC;

/*
 * @brief Waits for the screen to finish drawing before VBlank.
 * @function wait_vblank
 */
void wait_vblank() {
    while (*scanline_counter < 160) {
    }
}

/*
 * @brief Checks if a specific button is currently pressed.
 * @param button The button bitmask to check.
 * @return 1 if pressed, 0 if not.
 */
unsigned char button_pressed(unsigned short button) {
    return (*buttons & button) == 0;
}

/*
 * @brief Returns a pointer to a character block.
 * @param block The block index (0–3).
 * @return Pointer to the character block.
 */
volatile unsigned short* char_block(unsigned long block) {
    return (volatile unsigned short*)(0x6000000 + (block * 0x4000));
}

/*
 * @brief Returns a pointer to a screen block.
 * @param block The block index (0–31).
 * @return Pointer to the screen block.
 */
volatile unsigned short* screen_block(unsigned long block) {
    return (volatile unsigned short*)(0x6000000 + (block * 0x800));
}

/*
 * @brief Copies memory using 16-bit DMA.
 * @param dest Destination pointer.
 * @param source Source pointer.
 * @param amount Number of 16-bit words to copy.
 */
void memcpy16_dma(unsigned short* dest, unsigned short* source, int amount) {
    *dma_source = (unsigned int)source;
    *dma_destination = (unsigned int)dest;
    *dma_count = amount | DMA_16 | DMA_ENABLE;
}
