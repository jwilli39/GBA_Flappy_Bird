// koopa_logic.c
// Handles Koopa's movement, physics, animation, and collision logic

#include "gba.h"
#include "flappyBird.h"
#include "koopa_logic.h"
#include "map.h"
#include "sprite_utils.h"
#include "sprite_image.h"
#include "sprite_position.h"

/** 
 *@brief Initializes the Koopa character
 *@details Sets default values for position, velocity, animation, and assigns a sprite
 */ 
void koopa_init(struct Koopa *koopa) {
    koopa->x = 10;           // starting x position
    koopa->y = 50;           // starting y position
    koopa->yvel = 0;         // initial vertical velocity
    koopa->gravity = 50;     // gravity affecting the Koopa
    koopa->border = 40;      // distance from screen edge
    koopa->frame = 0;        // initial animation frame
    koopa->move = 0;         // not moving initially
    koopa->counter = 0;      // animation counter
    koopa->falling = 0;      // not falling at start
    koopa->animation_delay = 8;  // delay between animation frames

    // initialize the sprite with these properties
    koopa->sprite = sprite_init(koopa->x, koopa->y, SIZE_16_16, 0, 0, koopa->frame, 0);
}

/** 
 * @brief Updates Koopa’s position, animation, and collision
 * @details Applies gravity, checks ground tile, updates animation if moving
*/
void koopa_update(struct Koopa *koopa, int xscroll) {
    // Apply gravity if falling
    if (koopa->falling) {
        koopa->y += (koopa->yvel >> 8);  // update position
        koopa->yvel += koopa->gravity;   // apply acceleration
    }

    // Check tile below Koopa's feet
    unsigned short tile = tile_lookup(koopa->x + 8, koopa->y + 15, xscroll, 0,
                                      map, map_width, map_height);

    // Ground collision detection
    if ((tile >= 1 && tile <= 6) || (tile >= 12 && tile <= 17)) {
        koopa->falling = 0;
        koopa->yvel = 0;
        koopa->y &= ~0x3;  // align to tile grid
        koopa->y++;        // adjust for sprite gap
    } else {
        koopa->falling = 1;
    }

    // Handle animation while moving
    if (koopa->move) {
        koopa->counter++;
        if (koopa->counter >= koopa->animation_delay) {
            koopa->frame += 16;
            if (koopa->frame > 16) koopa->frame = 0;
            sprite_set_offset(koopa->sprite, koopa->frame);
            koopa->counter = 0;
        }
    }

    // Update on-screen sprite position
    sprite_position(koopa->sprite, koopa->x, koopa->y);
}

/** 
 * @brief Makes the Koopa jump
 * @details Sets a negative y-velocity to initiate upward motion
 */
void koopa_jump(struct Koopa *koopa) {
    koopa->yvel = -250;  // jump force
}

/** 
 * @brief Moves Koopa to the left
 * @details Updates x position unless too close to the screen edge
 */
int koopa_left(struct Koopa *koopa) {
    sprite_set_horizontal_flip(koopa->sprite, 1);  // face left
    koopa->move = 1;  // mark as moving

    if (koopa->x < koopa->border) {
        return 1;  // hit left edge
    } else {
        koopa->x--;  // move left
        return 0;
    }
}

/** 
 * @brief Moves Koopa to the right
 * @details Updates direction, returns 1 if at the right screen edge 
 */
int koopa_right(struct Koopa *koopa) {
    sprite_set_horizontal_flip(koopa->sprite, 0);  // face right
    koopa->move = 1;  // mark as moving

    if (koopa->x > (240 - 16 - koopa->border)) {
        return 1;  // hit right edge
    } else {
        return 0;
    }
}

/** 
 * @brief Stops Koopa's horizontal movement
 * @details Resets animation and movement flags when Koopa is idle 
 */
void koopa_stop(struct Koopa *koopa) {
    koopa->move = 0;              // stop moving
    koopa->frame = 0;             // reset to first animation frame
    koopa->counter = 7;           // reset frame delay counter
    sprite_set_offset(koopa->sprite, koopa->frame); // update sprite frame
}

/** 
 * @brief Checks if Koopa is colliding with a tile above
 * @details Uses Koopa's x and y to sample tile data at the top of the sprite 
 */
int check_collision_top(struct Koopa *koopa, int xscroll) {
    unsigned short tile = tile_lookup(koopa->x + 8, koopa->y, xscroll, 0,
                                      map, map_width, map_height);
    return ((tile >= 1 && tile <= 6) || (tile >= 12 && tile <= 17)); // check valid tiles
}

/** 
 * @brief Checks if Koopa is colliding with a tile below
 * @details Uses Koopa's x and y+15 (bottom edge) to sample the tile below 
 */
int check_collision_bottom(struct Koopa *koopa, int xscroll) {
    unsigned short tile = tile_lookup(koopa->x + 8, koopa->y + 15, xscroll, 0,
                                      map, map_width, map_height);
    return ((tile >= 1 && tile <= 6) || (tile >= 12 && tile <= 17)); // check valid tiles
}
