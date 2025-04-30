// koopa_logic.h

#ifndef KOOPA_LOGIC_H
#define KOOPA_LOGIC_H

#include "flappyBird.h"  // For Sprite struct and SpriteSize enum

// Structure representing the Koopa character's state and behavior
struct Koopa {
    struct Sprite *sprite;       // Pointer to the associated sprite
    int x, y;                    // X and Y position on screen
    int yvel;                    // Vertical velocity (used for jumping/falling)
    int gravity;                 // Acceleration due to gravity
    int frame;                   // Current animation frame
    int animation_delay;         // Number of frames to wait before changing animation
    int counter;                 // Counts frames for animation timing
    int move;                    // Non-zero if Koopa is moving
    int border;                  // Distance to keep from screen edges
    int falling;                 // Non-zero if Koopa is in the air
};

// Initialization and state update
void koopa_init(struct Koopa *koopa);
void koopa_update(struct Koopa *koopa, int xscroll);

// Movement and control logic
void koopa_jump(struct Koopa *koopa);
int  koopa_left(struct Koopa *koopa);
int  koopa_right(struct Koopa *koopa);
void koopa_stop(struct Koopa *koopa);

// Collision detection
int check_collision_top(struct Koopa *koopa, int xscroll);
int check_collision_bottom(struct Koopa *koopa, int xscroll);

#endif
