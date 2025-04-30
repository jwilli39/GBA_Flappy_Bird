#ifndef SPRITE_UTILS_H
#define SPRITE_UTILS_H

struct Sprite {
    unsigned short attribute0;
    unsigned short attribute1;
    unsigned short attribute2;
    unsigned short attribute3;
};

// Possible sprite sizes
enum SpriteSize {
    SIZE_8_8,
    SIZE_16_16,
    SIZE_32_32,
    SIZE_64_64,
    SIZE_16_8,
    SIZE_32_8,
    SIZE_32_16,
    SIZE_64_32,
    SIZE_8_16,
    SIZE_8_32,
    SIZE_16_32,
    SIZE_32_64
};

// Sprite manipulation functions
struct Sprite *sprite_init(int x, int y, enum SpriteSize size, int horizontal_flip, int vertical_flip, int tile_index, int priority);
void sprite_update_all();
void sprite_clear();

#endif
