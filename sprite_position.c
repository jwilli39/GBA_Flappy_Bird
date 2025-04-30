// sprite_position.c
// Functions for positioning and flipping sprites

#include "sprite_utils.h"    
#include "sprite_position.h"

/**
 * @brief Set the position of a sprite on the screen.
 * @param sprite A pointer to the sprite whose position will be set.
 * @param x The x-coordinate of the sprite.
 * @param y The y-coordinate of the sprite.
 */
void sprite_position(struct Sprite *sprite, int x, int y)
{
    // Clear the old y-coordinate
    sprite->attribute0 &= 0xff00;

    // Set the new y-coordinate
    sprite->attribute0 |= (y & 0xff);

    // Clear the old x-coordinate
    sprite->attribute1 &= 0xfe00;

    // Set the new x-coordinate
    sprite->attribute1 |= (x & 0x1ff);
}

/**
 * @brief Move a sprite in a given direction.
 * @param sprite A pointer to the sprite to be moved.
 * @param dx The change in x-coordinate.
 * @param dy The change in y-coordinate.
 */
void sprite_move(struct Sprite *sprite, int dx, int dy)
{
    // Get the current y-coordinate
    int y = sprite->attribute0 & 0xff;

    // Get the current x-coordinate
    int x = sprite->attribute1 & 0x1ff;

    // Move the sprite to the new location by updating its position
    sprite_position(sprite, x + dx, y + dy);
}

/**
 * @brief Change the vertical flip flag of a sprite.
 * @param sprite A pointer to the sprite whose vertical flip flag is being changed.
 * @param vertical_flip If true, the vertical flip flag will be set; otherwise, it will be cleared.
 */
void sprite_set_vertical_flip(struct Sprite *sprite, int vertical_flip)
{
    if (vertical_flip)
    {
        // Set the vertical flip bit
        sprite->attribute1 |= 0x2000;
    }
    else
    {
        // Clear the vertical flip bit
        sprite->attribute1 &= 0xdfff;
    }
}

/**
 * @brief Change the horizontal flip flag of a sprite.
 * @param sprite A pointer to the sprite whose horizontal flip flag is being changed.
 * @param horizontal_flip If true, the horizontal flip flag will be set; otherwise, it will be cleared.
 */
void sprite_set_horizontal_flip(struct Sprite *sprite, int horizontal_flip)
{
    if (horizontal_flip)
    {
        // Set the horizontal flip bit
        sprite->attribute1 |= 0x1000;
    }
    else
    {
        // Clear the horizontal flip bit
        sprite->attribute1 &= 0xefff;
    }
}

/**
 * @brief Change the tile offset of a sprite.
 * @param sprite A pointer to the sprite whose offset is being changed.
 * @param offset The new offset to be applied to the sprite.
 */
void sprite_set_offset(struct Sprite *sprite, int offset)
{
    // Clear the old offset
    sprite->attribute2 &= 0xfc00;

    // Apply the new one
    sprite->attribute2 |= (offset & 0x03ff);
}
