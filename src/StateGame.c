#pragma bank=2
#include "StateGame.h"
UINT8 bank_STATE_GAME = 2;

#include "Scroll.h"
#include "Frame.h"
#include "Sprite.h"
#include "Keys.h"
#include "SpriteManager.h"

#include "GBJAM2016.h"

#include "../res/src/stage1_bg.h"
#include "../res/src/stage1_1.h"
#include "../res/src/stage1_2.h"
#include "../res/src/stage1_3.h"
#include "../res/src/stage1_3b.h"
#include "../res/src/stage1_4.h"
#include "../res/src/stage1_5.h"
#include "../res/src/stage1_6.h"


#include "../res/src/princess.h"
#include "../res/src/mushroom.h"
#include "../res/src/enemybullet16x16.h"
#include "../res/src/ceilingshooter.h"
#include "../res/src/wallshooter.h"
#include "../res/src/enemyexplosion.h"

#include "SpriteMushroom.h"
#include "SpriteEnemyBullet.h"
#include "SpriteCeilingShooter.h"
#include "SpriteShooter.h"
#include "SpriteEnemyParticle.h"
#include "SpritePrincessParticle.h"

const UINT8 collision_tiles[] = {1, 2, 27, 28, 33, 35, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 0};
const UINT8 collision_tiles_down[] = {23, 24, 0};
UINT8 princess_idx;
UINT8 mushroom_idx;
UINT8 enemy_bullet_idx;
UINT8 cshooter_idx;
UINT8 wshooter_idx;
UINT8 enemy_particle_idx;


#include "gbt_player.h"
extern const unsigned char* exo_level1_mod_Data[];


UINT8 current_level;
UINT8 n_lives;

typedef struct LevelInfo {
	UINT16 w;
	UINT16 h;
	UINT8* map;
	UINT8 bank;
};
struct LevelInfo levels[] = {
	{stage1_1Width,   stage1_1Height,  stage1_1,  3},
	{stage1_2Width,   stage1_2Height,  stage1_2,  3},
	{stage1_3Width,   stage1_3Height,  stage1_3,  3},
	{stage1_3bWidth,  stage1_3bHeight, stage1_3b, 3},
	{stage1_4Width,   stage1_4Height,  stage1_4,  3},
	{stage1_5Width,   stage1_5Height,  stage1_5,  3},
	{stage1_6Width,   stage1_6Height,  stage1_6,  3},
};

void Start_STATE_GAME() {
	struct Sprite* princess_sprite;
	UINT16 tile_start_x, tile_start_y;

	SPRITES_8x16;
	princess_idx       = LoadSprite(14 * 4, spriteprincess,   3);
	mushroom_idx       = LoadSprite( 2 * 4, mushroom,         3);
	enemy_bullet_idx   = LoadSprite( 1 * 4, enemybullet16x16, 3);
	cshooter_idx       = LoadSprite( 2 * 4, ceilingshooter,   3);
	wshooter_idx       = LoadSprite( 2 * 4, wallshooter,      3);
	enemy_particle_idx = LoadSprite( 4 * 4, enemyexplosion,   3);
	LoadSprite(14 * 4, spriteprincess,   3);
	SHOW_SPRITES;

	MushroomResetCustomData();
	EnemyBulletResetCustomData();
	CShooterResetCustomData();
	WShooterResetCustomData();
	PParticleResetCustomData();


	princess_sprite = SpriteManagerAdd(SPRITE_PRINCESS);
	ScrollFindTile(levels[current_level].w, levels[current_level].h, levels[current_level].map, levels[current_level].bank, 2, &tile_start_x, &tile_start_y);
	
	if(tile_start_x == 0)
		tile_start_x += 1;
	if(tile_start_x == levels[current_level].w - 1)
		tile_start_x -= 2;

	if(tile_start_y == 0)
		tile_start_y += 1;
	else if(tile_start_y == levels[current_level].h - 1)
		tile_start_y -= 2;
	else
		tile_start_y -= 1;

	princess_sprite->x = tile_start_x << 3;
	princess_sprite->y = (tile_start_y << 3);
	
	scroll_target = princess_sprite;

	InitScrollTiles(0, 128, stage1_bg, 3);
	InitScroll(levels[current_level].w, levels[current_level].h, levels[current_level].map, collision_tiles, collision_tiles_down, levels[current_level].bank);
	SHOW_BKG;

	PlayMusic(exo_level1_mod_Data, 4, 1);
}

extern struct Sprite* sprite_princess;

UINT8 wait_end_time = 0;
void Update_STATE_GAME() {
	SpriteManagerUpdate();

	if(sprite_princess == 0) {
		wait_end_time ++;
		if(wait_end_time > 80) {
			wait_end_time = 0;

			n_lives --;
			SetState(n_lives == 0 ? STATE_GAMEOVER : STATE_LIVELOST);
		}
	}
}

