// sprite_position.h

#ifndef SPRITE_POSITION_H
#define SPRITE_POSITION_H

#include "sprite_utils.h"

void sprite_position(struct Sprite *sprite, int x, int y);
void sprite_move(struct Sprite *sprite, int dx, int dy);
void sprite_set_horizontal_flip(struct Sprite *sprite, int horizontal_flip);
void sprite_set_vertical_flip(struct Sprite *sprite, int vertical_flip);
void sprite_set_offset(struct Sprite *sprite, int offset);

#endif
