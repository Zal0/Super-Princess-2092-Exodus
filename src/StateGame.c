#pragma bank=2
#include "StateGame.h"
UINT8 bank_STATE_GAME = 2;

#include "Scroll.h"
#include "Frame.h"
#include "Sprite.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "GBJAM2016.h"

#include "../res/src/stage1_1.h"
#include "../res/src/stage1_bg.h"

#include "../res/src/princess.h"
#include "../res/src/mushroom.h"

#include "SpriteMushroom.h"

const UINT8 collision_tiles[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 0};
const UINT8 collision_tiles_down[] = {23, 24, 0};
UINT8 princess_idx;
UINT8 mushroom_idx;

/*#include "SpritePrincess.h"
#include "SpriteAznar.h"

#include "resources/map.h"
#include "resources/map2.h"
#include "resources/princess.h"
#include "resources/particles.h"
#include "resources/zurrapa.h"
#include "resources/tilemap.h"
#include "resources/aznar.h"
#include "resources/flag.h"

#include "gbt_player.h"

extern const unsigned char * level_mod_Data[];

const UINT8 collision_tiles[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 47, 48, 53, 56, 57, 58, 59, 0};

UINT8 particles_idx;
UINT8 zurrapa_idx;
UINT8 aznar_idx;
UINT8 flag_idx;

UINT16 reset_x;
UINT16 reset_y;

UINT8 level;

struct Sprite* game_over_particle;*/

void Start_STATE_GAME() {
	struct Sprite* princess_sprite;

	/*game_over_particle = 0;
	*/
	SPRITES_8x16;
	princess_idx = LoadSprite(11 * 4, spriteprincess, 3);
	mushroom_idx = LoadSprite(2 * 4, mushroom, 3);
	/*zurrapa_idx = LoadSprite(2 * 4, zurrapa);
	particles_idx = LoadSprite(6 * 4, particles);
	aznar_idx = LoadSprite(5 * 4, aznar);
	flag_idx = LoadSprite(2 * 4, flag);*/
	SHOW_SPRITES;

	MushroomResetCustomData();

	princess_sprite = SpriteManagerAdd(SPRITE_PRINCESS);
	princess_sprite->x = 32;
	princess_sprite->y = 114;
	//ScrollFindTile(stage1_1Width, stage1_1Height, stage1_1, 3, 26u, &princess_sprite->x, &princess_sprite->y);
	scroll_target = princess_sprite;

	InitScrollTiles(0, 128, stage1_bg, 3);
	/*switch(level) {
		case 0:
			InitScroll(level1Width, level1Height, level1 , collision_tiles, 3);
			break;
		case 1:
			InitScroll(level2Width, level2Height, level2, collision_tiles, 3);
			break;
	}*/
	InitScroll(stage1_1Width, stage1_1Height, stage1_1, collision_tiles, collision_tiles_down, 3);
	SHOW_BKG;

	/*PlayMusic(level_mod_Data, 3, 1);*/
}

void Update_STATE_GAME() {
	SpriteManagerUpdate();

	/*if(game_over_particle && game_over_particle->current_frame == 5) {
		SetState(STATE_GAME);
	}*/
}

