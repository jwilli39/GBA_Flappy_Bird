// background_utils.c
// Utility functions for setting up and clearing GBA backgrounds

#include "background.h"
#include "background0.h"

#include "background_utils.h"
#include "gba.h"
#include "map.h"

/**
 * @brief Function to setup the background for the program.
 */
void setup_background()
{
    // Load the palette from the image into palette memory
    memcpy16_dma((unsigned short *)bg_palette, (unsigned short *)background_palette, PALETTE_SIZE);

    // Load the image into char block 0
    memcpy16_dma((unsigned short *)char_block(0), (unsigned short *)background_data,
                 (background_width * background_height) / 2);

    // Set all control bits in this register for background 0
    *bg0_control = 0 |         // priority, 0 is highest, 3 is lowest
                   (0 << 2) |  // the char block the image data is stored in
                   (0 << 6) |  // the mosaic flag
                   (1 << 7) |  // color mode, 0 is 16 colors, 1 is 256 colors
                   (16 << 8) | // the screen block the tile data is stored in
                   (1 << 13) | // wrapping flag
                   (0 << 14);  // bg size, 0 is 256x256

    // Set background 1 control
    *bg1_control = 3 |         // priority, 0 is highest, 3 is lowest
                   (0 << 2) |  // the char block the image data is stored in
                   (0 << 6) |  // the mosaic flag
                   (1 << 7) |  // color mode, 0 is 16 colors, 1 is 256 colors
                   (24 << 8) | // the screen block the tile data is stored in
                   (1 << 13) | // wrapping flag
                   (0 << 14);  // bg size, 0 is 256x256

    // Load the tile data into screen block 16
    memcpy16_dma((unsigned short *)screen_block(16), (unsigned short *)map, map_width * map_height);
}

/**
 * @brief Function to setup the background 0 for the program.
 */
void setup_background0()
{
    // Load the palette from the image into palette memory
    memcpy16_dma((unsigned short *)bg_palette, (unsigned short *)background0_palette, PALETTE_SIZE);

    // Load the image into char block 0
    memcpy16_dma((unsigned short *)char_block(0), (unsigned short *)background0_data,
                 (background0_width * background0_height) / 2);

    // Set background 0 control to show a black screen
    *bg0_control = 3 |         // priority, 0 is highest, 3 is lowest
                   (0 << 2) |  // the char block the image data is stored in
                   (0 << 6) |  // the mosaic flag
                   (1 << 7) |  // color mode, 0 is 16 colors, 1 is 256 colors
                   (16 << 8) | // the screen block the tile data is stored in
                   (1 << 13) | // wrapping flag
                   (0 << 14);  // bg size, 0 is 256x256

    // Set background 1 control to show text background
    *bg1_control = 0 |         // priority, 0 is highest, 3 is lowest
                   (0 << 2) |  // the char block the image data is stored in
                   (0 << 6) |  // the mosaic flag
                   (1 << 7) |  // color mode, 0 is 16 colors, 1 is 256 colors
                   (24 << 8) | // the screen block the tile data is stored in
                   (1 << 13) | // wrapping flag
                   (0 << 14);  // bg size, 0 is 256x256

    // Clear the tile map in screen block 16 to all black tiles
    volatile unsigned short *ptr = screen_block(16);
    for (int i = 0; i < 32 * 32; i++)
    {
        ptr[i] = 95;
    }

    // Clear the text map to be all blanks
    ptr = screen_block(24);
    for (int i = 0; i < 32 * 32; i++)
    {
        ptr[i] = 0;
    }
}

/**
 * @brief Clears the background by resetting the tile and text maps to blank.
 */
void clear_background()
{
    // Clear the tile map in screen block 16 to all black tiles
    volatile unsigned short *ptr = screen_block(16);
    for (int i = 0; i < 32 * 32; i++)
    {
        ptr[i] = 95;
    }

    // Clear the text map to be all blanks
    ptr = screen_block(24);
    for (int i = 0; i < 32 * 32; i++)
    {
        ptr[i] = 0;
    }
}
