all:
	gbacc main.c flappyBird.c flappy_utils.c gba.c koopa_logic.c koopa.c background_utils.c map.c functions.s sprite_utils.c sprite_position.c sprite_image.c -o flappy_bird.gba
