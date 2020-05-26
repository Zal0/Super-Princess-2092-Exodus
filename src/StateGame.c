#include "Banks/SetBank6.h"
#include "main.h"

#include "Scroll.h"
#include "Frame.h"
#include "Sprite.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Math.h"
#include "gbt_player.h"

#include "ZGBMain.h"

#include "../res/src/stage1_bg.h"
#include "../res/src/stage1_1.h"
#include "../res/src/stage1_2.h"
#include "../res/src/stage1_3.h"
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

const struct MapInfo* levels_1[] = {
	&stage1_1,
	&stage1_2,
	&stage1_3,
	&stage1_4,
	&stage1_5,
	&stage1_6,
	&stage1_7,
	&stage1_8,
};

const struct MapInfo* levels_2[] = {
	&stage2_1,
	&stage2_2,
	&stage2_3,
	&stage2_4,
	&stage2_5,
	&stage2_6,
	&stage2_7,
	&stage2_8,
};

const struct MapInfo* levels_3[] = {
	&stage3_1,
	&stage3_2,
	&stage3_3,
	&stage3_4,
	&stage3_5,
	&stage3_6,
	&stage3_7,
	&stage3_8,
};

const struct MapInfo** stages[] = {levels_1, levels_2, levels_3};
UINT8 current_stage = 0;

extern struct Sprite* sprite_princess;
void InitPlayerPos(UINT16 tile_start_x, UINT16 tile_start_y) {
	const struct MapInfo** levels = stages[current_stage];
	UINT8 map_w, map_h;
	GetMapSize(levels[current_level], &map_w, &map_h);

	if(tile_start_x == 0) {
		tile_start_x += 1;
	} else if(tile_start_x == map_w - 1) {
		tile_start_x -= 2;
	}

	if(tile_start_y == 0) {
		tile_start_y += 1;
	} else if(tile_start_y == map_h - 1) {
		tile_start_y -= 2;
	} else {
		tile_start_y -= 1;
	}

	if(sprite_princess) {
		sprite_princess->x = tile_start_x << 3;
		sprite_princess->y = tile_start_y << 3;
	} else {
		SpriteManagerAdd(SpritePrincess, tile_start_x << 3, tile_start_y << 3);
	}
}

void Start_StateGame() {
	UINT8 i;
	UINT16 tile_start_x, tile_start_y;
	const UINT8* coll_list = 0;
	const UINT8* coll_down_list = 0;
	const struct MapInfo** levels = stages[current_stage];
	UINT8 map_w, map_h;

	SPRITES_8x16;
	for(i = 0; i != N_SPRITE_TYPES; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	INIT_CONSOLE(font, 3, 2);

	GetMapSize(levels[current_level], &map_w, &map_h);
	ScrollFindTile(levels[current_level], 2, 
		0, 0, map_w, map_h,
		&tile_start_x, &tile_start_y);
	InitPlayerPos(tile_start_x, tile_start_y);
	scroll_target = sprite_princess;

	if(levels == levels_1) {
		coll_list = collision_tiles_1;
		coll_down_list = collision_tiles_down_1;
	} else if(levels == levels_2) {
		coll_list = collision_tiles_2;
		coll_down_list = collision_tiles_down_2;
	} else if(levels == levels_3) {
		coll_list = collision_tiles_3;
		coll_down_list = collision_tiles_down_3;
	}

	InitScroll(levels[current_level], coll_list, coll_down_list);
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

void ScrollFindTileInCorners(UINT16 map_w, UINT16 map_h, const struct MapInfo* map, UINT8 tile, UINT16* x, UINT16* y) {
	if(ScrollFindTile(map, tile, 0, 0, map_w, 1, x, y)) {
		return;
	}
	if(ScrollFindTile(map, tile, 0, map_h - 1, map_w, 1, x, y)) {
		return;
	}
	if(ScrollFindTile(map, tile, 0, 0, 1, map_h, x, y)) {
		return;
	}
	if(ScrollFindTile(map, tile, map_w - 1, 0, 1, map_h, x, y)) {
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
	INT16 offset_x = 0;
	INT16 offset_y = 0;
	const struct MapInfo** levels = stages[current_stage];
	UINT8 next_level_w, next_level_h, current_level_w, current_level_h;

	GetMapSize(levels[next_level], &next_level_w, &next_level_h);
	GetMapSize(levels[current_level], &current_level_w, &current_level_h);

	ScrollFindTileInCorners(next_level_w, next_level_h, levels[next_level], load_next == -1 ? 1 : 2, &tile_start_x, &tile_start_y);
	wait_vbl_done();
	InitPlayerPos(tile_start_x, tile_start_y);
	ScrollSetMap(levels[next_level]);
	
	if((tile_start_x == 0) || (tile_start_x == next_level_w - 1)) {
		if(tile_start_x == 0) {
			offset_x = current_level_w << 3;
			offset_x = -offset_x;
		} else  { // tile_start_x == levels[next_level].w - 1)
			offset_x = next_level_w << 3;
		}
		offset_y = (tile_start_y << 3) - (INT16)((old_player_y + 15) & 0xFFF8);

		//This keeps the scroll y in the same position it was on the previous screen
		//scroll_y = scroll_target->y + (old_scr_y - old_player_y);
		//ClampScrollLimits(&scroll_x, &scroll_y);	
		//scroll_end_y = scroll_y;
	}
	
	if((tile_start_y == 0) || (tile_start_y == next_level_h - 1)) {
		if(tile_start_y == 0) {
			offset_y = current_level_h << 3;
			offset_y = -offset_y;
		} else { //(tile_start_y == levels[next_level].h - 1)
			offset_y = next_level_h << 3;
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
		ScrollUpdateColumn((scroll_end_x >> 3),       (scroll_y >> 3) - 1);
		ScrollUpdateColumn((scroll_end_x >> 3) + 1,   (scroll_y >> 3) - 1);
	} else if(tile_start_x == next_level_w - 1) {
		ScrollUpdateColumn((scroll_start_x >> 3) - 1, (scroll_y >> 3) - 1);
	}

	if(tile_start_y == 0) {
		ScrollUpdateRow((scroll_x >> 3) - 1, (scroll_end_y >> 3));
		ScrollUpdateRow((scroll_x >> 3) - 1, (scroll_end_y >> 3) + 1);
	}  else if(tile_start_y == next_level_h - 1) {
		ScrollUpdateRow((scroll_x >> 3) - 1, (scroll_start_y >> 3) - 1);
	}

	clamp_enabled = 0;
	for(ix = 0; ix != SCREENWIDTH; ix += 8) {
		MoveScroll(
			Interpole(scroll_start_x, scroll_end_x, ix >> 2, SCREENWIDTH >> 2), 
			Interpole(scroll_start_y, scroll_end_y, ix >> 2, SCREENWIDTH >> 2)
		);
		
		DrawFrame(player->size, get_sprite_tile(SPRITE_GET_VMIRROR(player) ? 1 : 0), 
			scroll_start_x + Interpole(old_player_x - scroll_start_x, player->x - scroll_start_x, ix >> 2, SCREENWIDTH >> 2) - scroll_x,
			scroll_start_y + Interpole(old_player_y - scroll_start_y, player->y - scroll_start_y, ix >> 2, SCREENWIDTH >> 2) - scroll_y,
		player->flags);

		wait_vbl_done();
		SwapOAMs();
	}
	clamp_enabled = 1;
}

UINT8 wait_end_time = 0;
void Update_StateGame() {
	if(sprite_princess == 0) {
		wait_end_time ++;
		if(wait_end_time > 80) {
			wait_end_time = 0;

			n_lives --;
			SetState(n_lives == 0 ? StateGameOver : StateLiveLost);
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

