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
#include "../res/src/stage1_7.h"

#include "SpriteMushroom.h"
#include "SpriteEnemyBullet.h"
#include "SpriteCeilingShooter.h"
#include "SpriteShooter.h"
#include "SpriteEnemyParticle.h"
#include "SpritePrincessParticle.h"

#include "../res/src/font.h"

const UINT8 collision_tiles[] = {1, 2, 27, 28, 33, 35, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 0};
const UINT8 collision_tiles_down[] = {23, 24, 0};

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
	{stage1_7Width,   stage1_7Height,  stage1_7,  3}
};

extern struct Sprite* sprite_princess;
void InitPlayerPos(UINT16 tile_start_x, UINT16 tile_start_y) {
	if(tile_start_x == 0) {
		tile_start_x += 1;
	} else if(tile_start_x == levels[current_level].w - 1) {
		tile_start_x -= 2;
	}

	if(tile_start_y == 0) {
		tile_start_y += 1;
	} else if(tile_start_y == levels[current_level].h - 1) {
		tile_start_y -= 2;
	} else {
		tile_start_y -= 1;
	}

	sprite_princess->x = tile_start_x << 3;
	sprite_princess->y = tile_start_y << 3;
}

void Start_STATE_GAME() {
	struct Sprite* princess_sprite;
	UINT16 tile_start_x, tile_start_y;
	
	SPRITES_8x16;
	SpriteManagerLoad(SPRITE_PRINCESS);
	SpriteManagerLoadSubsprite(SPRITE_BULLET, SPRITE_PRINCESS);
	SpriteManagerLoadSubsprite(SPRITE_PPARTICLE, SPRITE_PRINCESS);
	SpriteManagerLoad(SPRITE_MUSHROOM);
	SpriteManagerLoad(SPRITE_ENEMY_BULLET);
	SpriteManagerLoad(SPRITE_CSHOOTER);
	SpriteManagerLoad(SPRITE_SHOOTER);
	SpriteManagerLoad(SPRITE_EPARTICLE);
	SpriteManagerLoad(SPRITE_PLATFORM);
	SHOW_SPRITES;

	princess_sprite = SpriteManagerAdd(SPRITE_PRINCESS, 0, 0);
	
	
	ScrollFindTile(levels[current_level].w, levels[current_level].h, levels[current_level].map, levels[current_level].bank, 2, &tile_start_x, &tile_start_y);
	InitPlayerPos(tile_start_x, tile_start_y);
	scroll_target = princess_sprite;

	InitScrollTiles(0, 128, stage1_bg, 3);
	InitScroll(levels[current_level].w, levels[current_level].h, levels[current_level].map, collision_tiles, collision_tiles_down, levels[current_level].bank);
	SHOW_BKG;

#ifndef NDEBUG 
	InitScrollTiles(128, 45, font, 3);
	WX_REG = 7;
  WY_REG = 128;
	SHOW_WIN;
#endif

	PlayMusic(exo_level1_mod_Data, 4, 1);
}

INT16 Interpole(INT16 a, INT16 b, INT16 t, INT16 max) {
	return a + (b - a) * t / max;
}

INT16 DespRight(INT16 a, INT16 b);
INT8 load_next = 0;
extern INT16 old_scroll_x, old_scroll_y;
void ClampScrollLimits(UINT16* x, UINT16* y);
void LoadNextScreen(UINT8 current_level, UINT8 next_level) {
	struct Sprite* player = scroll_target;
	INT16 old_scr_x = scroll_x;
	INT16 old_scr_y = scroll_y;
	INT16 old_player_x = scroll_target->x;
	INT16 old_player_y = scroll_target->y;
	UINT8 ix;
	UINT16 tile_start_x, tile_start_y;
	INT16 scroll_start_x, scroll_end_x, scroll_start_y, scroll_end_y;
	INT16 offset_x, offset_y;

	wait_vbl_done();
	ScrollFindTileInCorners(levels[next_level].w, levels[next_level].h, levels[next_level].map, levels[next_level].bank, load_next == -1 ? 1 : 2, &tile_start_x, &tile_start_y);
	InitPlayerPos(tile_start_x, tile_start_y);
	ScrollSetMap(levels[next_level].w, levels[next_level].h, levels[next_level].map, levels[next_level].bank);
	
	if((tile_start_x == 0) || (tile_start_x == levels[next_level].w - 1)) {
		if(tile_start_x == 0) {
			offset_x = levels[current_level].w << 3;
			offset_x = -offset_x;
		} else  { // tile_start_x == levels[next_level].w - 1)
			offset_x = levels[next_level].w << 3;
		}
		offset_y = (tile_start_y << 3) - (INT16)((old_player_y + 15) & 0xFFF8);

		//This keeps the scroll y in the same position it was on the previous screen
		//scroll_y = scroll_target->y + (old_scr_y - old_player_y);
		//ClampScrollLimits(&scroll_x, &scroll_y);	
		//scroll_end_y = scroll_y;
	}
	
	if((tile_start_y == 0) || (tile_start_y == levels[next_level].h - 1)) {
		if(tile_start_y == 0) {
			offset_y = levels[current_level].h << 3;
			offset_y = -offset_y;
		} else { //(tile_start_y == levels[next_level].h - 1)
			offset_y = levels[next_level].h << 3;
		}
		offset_x = (tile_start_x << 3) - (INT16)((old_player_x + + player->coll_x) & 0xFFF8);
	}

	//Adding offset_x and offset_y will convert coordinates from old screen to the new one
	scroll_offset_x = 0x1F & (scroll_offset_x - (offset_x >> 3));
	scroll_start_x = old_scr_x + offset_x;
	scroll_offset_y = 0x1F & (scroll_offset_y - (offset_y >> 3));
	scroll_start_y = old_scr_y + offset_y;


	scroll_end_x = scroll_x;
	scroll_end_y = scroll_y;
	old_scroll_x = scroll_x = scroll_start_x;
	old_scroll_y = scroll_y = scroll_start_y;
	
	old_player_x = scroll_start_x + (old_player_x - old_scr_x);
	old_player_y = scroll_start_y + (old_player_y - old_scr_y);;

	//Clear all sprites except the first one
	for(ix = 1u; ix != sprite_manager_updatables[0]; ++ix) {
		SpriteManagerRemove(ix);
	}
	SpriteManagerFlushRemove();

	//Because the way I update the scroll there are 2 columns or 1 that need to be updated first
	//Do this here, after settting scroll_x and scroll_y to avoid an annoying blink (because scroll_x and scroll_y are used on vblank)
	if(tile_start_x == 0) {
		ScrollUpdateColumn(DespRight(scroll_end_x, 3), DespRight(scroll_y, 3));
		ScrollUpdateColumn(DespRight(scroll_end_x, 3) + 1, DespRight(scroll_y, 3));
	} else if(tile_start_x == levels[next_level].w - 1) {
		ScrollUpdateColumn(DespRight(scroll_start_x, 3) - 1, DespRight(scroll_y, 3));
	}
	if(tile_start_y == 0) {
		ScrollUpdateRow(DespRight(scroll_end_x, 3) - 1, DespRight(scroll_end_y, 3));
	}

	scroll_target = 0;
	clamp_enabled = 0;
	for(ix = 0; ix != SCREENWIDTH; ix += 8) {
		MoveScroll(
			Interpole(scroll_start_x, scroll_end_x, ix >> 2, SCREENWIDTH >> 2), 
			Interpole(scroll_start_y, scroll_end_y, ix >> 2, SCREENWIDTH >> 2)
		);
		
		DrawFrame(player->oam_idx, player->size, player->first_tile + player->data[1 + player->current_frame], 
			scroll_start_x + Interpole(old_player_x - scroll_start_x, player->x - scroll_start_x, ix >> 2, SCREENWIDTH >> 2),
			scroll_start_y + Interpole(old_player_y - scroll_start_y, player->y - scroll_start_y, ix >> 2, SCREENWIDTH >> 2),
		player->flags);

		wait_vbl_done();
	}
	scroll_target = player;
	clamp_enabled = 1;
}

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

	if(load_next) {
		if(current_level != 0 || load_next == 1) { //current_level > 0 || load_next == 1 (to avoid going under 0)
			current_level += load_next;
			LoadNextScreen(current_level - load_next, current_level);
		}

		load_next = 0;
	}
}

