// flappy_utils.h

#ifndef FLAPPY_UTILS_H
#define FLAPPY_UTILS_H

#include <stdio.h>
#include "gba.h"
#include "koopa.h"
#include "koopa_logic.h"
#include "flappyBird.h"
#include "map.h"
#include "sprite_utils.h"

// Screen dimensions
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

// Palette configuration
#define PALETTE_SIZE 256

// Sprite system
#define NUM_SPRITES 128

// C utility functions
void set_text(char *str, int row, int col);
void delay(unsigned int amount);

// Assembly utility functions
int increment_speed(int score);
int countDown(int n, int r1, int r2, int r3);

#endif
