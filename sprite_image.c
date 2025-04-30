// sprite_image.c
// Handles sprite image and palette loading, and tile lookup for background maps

#include "gba.h"       
#include "sprite_utils.h"    
#include "sprite_image.h"
#include "koopa.h"

/**
 * @brief Setup the sprite image and palette.
 */
void setup_sprite_image()
{
    // Load the palette from the image into palette memory
    memcpy16_dma((unsigned short *)sprite_palette, (unsigned short *)koopa_palette, PALETTE_SIZE);

    // Load the image into sprite image memory
    memcpy16_dma((unsigned short *)sprite_image_memory, (unsigned short *)koopa_data, (koopa_width * koopa_height) / 2);
}

/**
 * @brief Finds which tile a screen coordinate maps to, taking scroll into account.
 * @param x The x-coordinate on the screen.
 * @param y The y-coordinate on the screen.
 * @param xscroll The x-scroll offset.
 * @param yscroll The y-scroll offset.
 * @param tilemap A pointer to the tilemap.
 * @param tilemap_w The width of the tilemap (in tiles).
 * @param tilemap_h The height of the tilemap (in tiles).
 * @return The tile value at the corresponding screen coordinate.
 */
unsigned short tile_lookup(int x, int y, int xscroll, int yscroll,
                           const unsigned short *tilemap, int tilemap_w, int tilemap_h)
{
    // Adjust for the scroll
    x += xscroll;
    y += yscroll;

    // Convert from screen coordinates to tile coordinates
    x >>= 3;
    y >>= 3;

    // Wrap around coordinates if needed
    while (x >= tilemap_w) x -= tilemap_w;
    while (y >= tilemap_h) y -= tilemap_h;
    while (x < 0) x += tilemap_w;
    while (y < 0) y += tilemap_h;

    // Offset for large tilemaps (e.g., 64x32)
    int offset = 0;
    if (tilemap_w == 64 && x >= 32) {
        x -= 32;
        offset += 0x400;
    }

    int index = y * 32 + x;
    return tilemap[index + offset];
}
