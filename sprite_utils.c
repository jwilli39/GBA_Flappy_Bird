// sprite_utils.c
// Functions for initializing, updating, and clearing sprites on the GBA

#include "gba.h"
#include "sprite_utils.h"

// Global array for all 128 possible hardware sprites
struct Sprite sprites[NUM_SPRITES];

// Index to track the next free sprite slot
int next_sprite_index = 0;

/**
 * @brief Initialize a sprite with its properties and return a pointer to it.
 * @param x The x-coordinate of the sprite.
 * @param y The y-coordinate of the sprite.
 * @param size The size of the sprite (enum SpriteSize).
 * @param horizontal_flip If true, the sprite will be flipped horizontally.
 * @param vertical_flip If true, the sprite will be flipped vertically.
 * @param tile_index The tile index in VRAM for the sprite graphic.
 * @param priority The drawing priority (0–3, 0 = highest).
 * @return A pointer to the initialized Sprite struct.
 */
struct Sprite *sprite_init(int x, int y, enum SpriteSize size,
                           int horizontal_flip, int vertical_flip, int tile_index, int priority)
{
    // Use the next available sprite slot
    int index = next_sprite_index++;

    // Determine the shape and size bits used for sprite rendering
    int size_bits, shape_bits;
    switch (size)
    {
    case SIZE_8_8:
        size_bits = 0;
        shape_bits = 0;
        break;
    case SIZE_16_16:
        size_bits = 1;
        shape_bits = 0;
        break;
    case SIZE_32_32:
        size_bits = 2;
        shape_bits = 0;
        break;
    case SIZE_64_64:
        size_bits = 3;
        shape_bits = 0;
        break;
    case SIZE_16_8:
        size_bits = 0;
        shape_bits = 1;
        break;
    case SIZE_32_8:
        size_bits = 1;
        shape_bits = 1;
        break;
    case SIZE_32_16:
        size_bits = 2;
        shape_bits = 1;
        break;
    case SIZE_64_32:
        size_bits = 3;
        shape_bits = 1;
        break;
    case SIZE_8_16:
        size_bits = 0;
        shape_bits = 2;
        break;
    case SIZE_8_32:
        size_bits = 1;
        shape_bits = 2;
        break;
    case SIZE_16_32:
        size_bits = 2;
        shape_bits = 2;
        break;
    case SIZE_32_64:
        size_bits = 3;
        shape_bits = 2;
        break;
    }

    // Set flip flags based on input
    int h = 0;
    int v = 0;

    if (horizontal_flip)
    {
        h = 1;
    }
    if (vertical_flip)
    {
        v = 1;
    }

    // Set up the sprite's rendering attributes
    sprites[index].attribute0 = y |                 // Y-coordinate on screen
                                (0 << 8) |          // regular rendering mode
                                (0 << 10) |         // no special graphics mode
                                (0 << 12) |         // no mosaic effect
                                (1 << 13) |         // use 256-color tiles
                                (shape_bits << 14); // sprite shape

    sprites[index].attribute1 = x |                // X-coordinate on screen
                                (0 << 9) |         // not using affine transforms
                                (h << 12) |        // enable horizontal flip if set
                                (v << 13) |        // enable vertical flip if set
                                (size_bits << 14); // sprite size

    sprites[index].attribute2 = tile_index |       // starting tile index in video memory
                                (priority << 10) | // drawing priority (lower value draws in front)
                                (0 << 12);         // palette bank (only used in 16-color mode)

    return &sprites[index];
}

/**
 * @brief Copy all sprite data to video memory to update what's displayed on screen.
 */
void sprite_update_all()
{
    // Transfer all sprite attribute data into sprite memory using DMA
    memcpy16_dma((unsigned short *)sprite_attribute_memory,
                 (unsigned short *)sprites,
                 NUM_SPRITES * sizeof(struct Sprite) / 2); // 2 bytes per short
}

/**
 * @brief Clear all sprites by resetting the index and hiding them offscreen.
 */
void sprite_clear()
{
    // Reset sprite counter to 0 (start fresh)
    next_sprite_index = 0;

    // Move all sprites offscreen (so they aren't rendered)
    for (int i = 0; i < NUM_SPRITES; i++)
    {
        sprites[i].attribute0 = SCREEN_HEIGHT; // Y offscreen
        sprites[i].attribute1 = SCREEN_WIDTH;  // X offscreen
    }
}
