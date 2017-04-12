#pragma bank=6
#include "StateGame.h"
UINT8 bank_STATE_GAME = 6;

#include "Scroll.h"
#include "Frame.h"
#include "Sprite.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Math.h"
#include "gbt_player.h"

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
#include "../res/src/stage1_8.h"

#include "../res/src/stage2_bg.h"
#include "../res/src/stage2_1.h"
#include "../res/src/stage2_2.h"
#include "../res/src/stage2_3.h"
#include "../res/src/stage2_4.h"
#include "../res/src/stage2_5.h"
#include "../res/src/stage2_6.h"
#include "../res/src/stage2_7.h"
#include "../res/src/stage2_8.h"

#include "../res/src/stage3_bg.h"
#include "../res/src/stage3_1.h"
#include "../res/src/stage3_2.h"
#include "../res/src/stage3_3.h"
#include "../res/src/stage3_4.h"
#include "../res/src/stage3_5.h"
#include "../res/src/stage3_6.h"
#include "../res/src/stage3_7.h"
#include "../res/src/stage3_8.h"

#include "Print.h"
#include "../res/src/font.h"

const UINT8 collision_tiles_1[] = {1, 2, 27, 28, 33, 35, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 0};
const UINT8 collision_tiles_down_1[] = {23, 24, 0};

const UINT8 collision_tiles_2[] = {1, 2, 27, 28, 33, 35, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 55, 56, 57, 58, 0};
const UINT8 collision_tiles_down_2[] = {23, 24, 0};

const UINT8 collision_tiles_3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 27, 28, 33, 35, 0};
const UINT8 collision_tiles_down_3[] = {23, 24, 0};

extern const unsigned char* exo_level1_mod_Data[];
extern const unsigned char* exo_level2_mod_Data[];
extern const unsigned char* exo_level3_mod_Data[];

UINT8 current_level;
UINT8 n_lives;
UINT8 stage_completion;

typedef struct LevelInfo {
	UINT16 w;
	UINT16 h;
	UINT8* map;
	UINT8 bank;
};

const struct LevelInfo levels_1[] = {
	{stage1_1Width,   stage1_1Height,  stage1_1,  3},
	{stage1_2Width,   stage1_2Height,  stage1_2,  3},
	{stage1_3Width,   stage1_3Height,  stage1_3,  3},
	{stage1_3bWidth,  stage1_3bHeight, stage1_3b, 3},
	{stage1_4Width,   stage1_4Height,  stage1_4,  3},
	{stage1_5Width,   stage1_5Height,  stage1_5,  3},
	{stage1_6Width,   stage1_6Height,  stage1_6,  3},
	{stage1_7Width,   stage1_7Height,  stage1_7,  3},
	{stage1_8Width,   stage1_8Height,  stage1_8,  3},
};

const struct LevelInfo levels_2[] = {
	{stage2_1Width,   stage2_1Height,  stage2_1,  5},
	{stage2_2Width,   stage2_2Height,  stage2_2,  5},
	{stage2_3Width,   stage2_3Height,  stage2_3,  5},
	{stage2_4Width,   stage2_4Height,  stage2_4,  5},
	{stage2_5Width,   stage2_5Height,  stage2_5,  5},
	{stage2_6Width,   stage2_6Height,  stage2_6,  5},
	{stage2_7Width,   stage2_7Height,  stage2_7,  5},
	{stage2_8Width,   stage2_8Height,  stage2_8,  5},
};

const struct LevelInfo levels_3[] = {
	{stage3_1Width,   stage3_1Height,  stage3_1,  6},
	{stage3_2Width,   stage3_2Height,  stage3_2,  6},
	{stage3_3Width,   stage3_3Height,  stage3_3,  6},
	{stage3_4Width,   stage3_4Height,  stage3_4,  6},
	{stage3_5Width,   stage3_5Height,  stage3_5,  6},
	{stage3_6Width,   stage3_6Height,  stage3_6,  6},
	{stage3_7Width,   stage3_7Height,  stage3_7,  6},
	{stage3_8Width,   stage3_8Height,  stage3_8,  6},
};

const struct LevelInfo* stages[] = {levels_1, levels_2, levels_3};
UINT8 current_stage = 0;

extern struct Sprite* sprite_princess;
void InitPlayerPos(UINT16 tile_start_x, UINT16 tile_start_y) {
	struct LevelInfo* levels = stages[current_stage];

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

	if(sprite_princess) {
		sprite_princess->x = tile_start_x << 3;
		sprite_princess->y = tile_start_y << 3;
	} else {
		SpriteManagerAdd(SPRITE_PRINCESS, tile_start_x << 3, tile_start_y << 3);
	}
}

extern UINT8 n_sprite_types;
void Start_STATE_GAME() {
	UINT8 i;
	UINT16 tile_start_x, tile_start_y;
	UINT8* coll_list;
	UINT8* coll_down_list;
	struct LevelInfo* levels = stages[current_stage];

	SPRITES_8x16;
	for(i = 0; i != n_sprite_types; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	INIT_CONSOLE(font, 3, 2);

	ScrollSetMap(levels[current_level].w, levels[current_level].h, levels[current_level].map, levels[current_level].bank);
	ScrollFindTile(levels[current_level].w, levels[current_level].h, levels[current_level].map, levels[current_level].bank, 2, 
		0, 0, levels[current_level].w, levels[current_level].h,
		&tile_start_x, &tile_start_y);
	InitPlayerPos(tile_start_x, tile_start_y);
	scroll_target = sprite_princess;

	if(levels == levels_1) {
		InitScrollTiles(0, 128, stage1_bg, 3);
		coll_list = collision_tiles_1;
		coll_down_list = collision_tiles_down_1;
	} else if(levels == levels_2) {
		InitScrollTiles(0, 128, stage2_bg, 3);
		coll_list = collision_tiles_2;
		coll_down_list = collision_tiles_down_2;
	} else if(levels == levels_3) {
		InitScrollTiles(0, 128, stage3_bg, 6);
		coll_list = collision_tiles_3;
		coll_down_list = collision_tiles_down_3;
	}

	InitScroll(levels[current_level].w, levels[current_level].h, levels[current_level].map, coll_list, coll_down_list, levels[current_level].bank);
	SHOW_BKG;

	switch(current_stage) {
		case 1:  PlayMusic(exo_level2_mod_Data, 4, 1); break;
		case 2:  PlayMusic(exo_level3_mod_Data, 4, 1); break;
		default: PlayMusic(exo_level1_mod_Data, 4, 1); break;
	}
}

INT16 Interpole(INT16 a, INT16 b, INT16 t, INT16 max) {
	return a + (b - a) * t / max;
}

void ScrollFindTileInCorners(UINT16 map_w, UINT16 map_h, unsigned char* map, UINT8 bank, UINT8 tile, UINT16* x, UINT16* y) {
	if(ScrollFindTile(map_w, map_h, map, bank, tile, 0, 0, map_w, 1, x, y)) {
		return;
	}
	if(ScrollFindTile(map_w, map_h, map, bank, tile, 0, map_h - 1, map_w, 1, x, y)) {
		return;
	}
	if(ScrollFindTile(map_w, map_h, map, bank, tile, 0, 0, 1, map_h, x, y)) {
		return;
	}
	if(ScrollFindTile(map_w, map_h, map, bank, tile, map_w - 1, 0, 1, map_h, x, y)) {
		return;
	}
}

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
	struct LevelInfo* levels = stages[current_stage];

	ScrollFindTileInCorners(levels[next_level].w, levels[next_level].h, levels[next_level].map, levels[next_level].bank, load_next == -1 ? 1 : 2, &tile_start_x, &tile_start_y);
	wait_vbl_done();
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

	clamp_enabled = 0;
	for(ix = 0; ix != SCREENWIDTH; ix += 8) {
		MoveScroll(
			Interpole(scroll_start_x, scroll_end_x, ix >> 2, SCREENWIDTH >> 2), 
			Interpole(scroll_start_y, scroll_end_y, ix >> 2, SCREENWIDTH >> 2)
		);
		
		DrawFrame(player->oam_idx, player->size, player->first_tile + player->anim_data[1 + player->current_frame] << player->size, 
			scroll_start_x + Interpole(old_player_x - scroll_start_x, player->x - scroll_start_x, ix >> 2, SCREENWIDTH >> 2),
			scroll_start_y + Interpole(old_player_y - scroll_start_y, player->y - scroll_start_y, ix >> 2, SCREENWIDTH >> 2),
		player->flags);

		wait_vbl_done();
	}
	clamp_enabled = 1;
}

UINT8 wait_end_time = 0;
void Update_STATE_GAME() {
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

