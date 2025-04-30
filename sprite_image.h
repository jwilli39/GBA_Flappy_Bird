// sprite_image.h

#ifndef SPRITE_IMAGE_H
#define SPRITE_IMAGE_H

#include "gba.h"

// Loads the sprite palette and image into VRAM
void setup_sprite_image();

// Looks up a tile from a tilemap using screen coordinates and scroll
unsigned short tile_lookup(int x, int y, int xscroll, int yscroll,
                           const unsigned short *tilemap, int tilemap_w, int tilemap_h);

#endif
