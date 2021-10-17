#include "Banks/SetAutoBank.h"
#include "main.h"

#include "Scroll.h"
#include "Sprite.h"
#include "Keys.h"
#include "SpriteManager.h"
#include "Math.h"
#include "Music.h"

#include "ZGBMain.h"

IMPORT_MAP(stage1_bg);
IMPORT_MAP(stage1_1);
IMPORT_MAP(stage1_2);
IMPORT_MAP(stage1_3);
IMPORT_MAP(stage1_4);
IMPORT_MAP(stage1_5);
IMPORT_MAP(stage1_6);
IMPORT_MAP(stage1_7);
IMPORT_MAP(stage1_8);

IMPORT_MAP(stage2_bg);
IMPORT_MAP(stage2_1);
IMPORT_MAP(stage2_2);
IMPORT_MAP(stage2_3);
IMPORT_MAP(stage2_4);
IMPORT_MAP(stage2_5);
IMPORT_MAP(stage2_6);
IMPORT_MAP(stage2_7);
IMPORT_MAP(stage2_8);

IMPORT_MAP(stage3_bg);
IMPORT_MAP(stage3_1);
IMPORT_MAP(stage3_2);
IMPORT_MAP(stage3_3);
IMPORT_MAP(stage3_4);
IMPORT_MAP(stage3_5);
IMPORT_MAP(stage3_6);
IMPORT_MAP(stage3_7);
IMPORT_MAP(stage3_8);

#include "Print.h"
IMPORT_TILES(font);

const UINT8 collision_tiles_1[] = {1, 2, 27, 28, 33, 35, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 0};
const UINT8 collision_tiles_down_1[] = {59, 60, 0};

const UINT8 collision_tiles_2[] = {1, 2, 27, 28, 33, 35, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 55, 56, 57, 58, 0};
const UINT8 collision_tiles_down_2[] = {59, 60, 0};

const UINT8 collision_tiles_3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 27, 28, 33, 35, 0};
const UINT8 collision_tiles_down_3[] = {59, 60, 0};

DECLARE_MUSIC(exo_level1);
DECLARE_MUSIC(exo_level2);
DECLARE_MUSIC(exo_level3);

UINT8 current_level;
UINT8 n_lives;
UINT8 stage_completion;

struct MapInfoBanked {
	UINT8 bank;
	struct MapInfo* map;
};
#define BANKED_MAP(MAP) {BANK(MAP), &MAP}

const struct MapInfoBanked levels_1[] = {
	BANKED_MAP(stage1_1),
	BANKED_MAP(stage1_2),
	BANKED_MAP(stage1_3),
	BANKED_MAP(stage1_4),
	BANKED_MAP(stage1_5),
	BANKED_MAP(stage1_6),
	BANKED_MAP(stage1_7),
	BANKED_MAP(stage1_8),
};

const struct MapInfoBanked levels_2[] = {
	BANKED_MAP(stage2_1),
	BANKED_MAP(stage2_2),
	BANKED_MAP(stage2_3),
	BANKED_MAP(stage2_4),
	BANKED_MAP(stage2_5),
	BANKED_MAP(stage2_6),
	BANKED_MAP(stage2_7),
	BANKED_MAP(stage2_8),
};

const struct MapInfoBanked levels_3[] = {
	BANKED_MAP(stage3_1),
	BANKED_MAP(stage3_2),
	BANKED_MAP(stage3_3),
	BANKED_MAP(stage3_4),
	BANKED_MAP(stage3_5),
	BANKED_MAP(stage3_6),
	BANKED_MAP(stage3_7),
	BANKED_MAP(stage3_8),
};

const struct MapInfoBanked* stages[] = {levels_1, levels_2, levels_3};
UINT8 current_stage = 0;

extern Sprite* sprite_princess;
void InitPlayerPos(UINT16 tile_start_x, UINT16 tile_start_y) {
	const struct MapInfoBanked* levels = stages[current_stage];
	const struct MapInfoBanked* map = &levels[current_level];
	UINT8 map_w, map_h;
	GetMapSize(map->bank, map->map, &map_w, &map_h);

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
		sprite_princess->x = (tile_start_x << 3) + (sprite_princess->x & 0x7); //x &0x7 keeps the relative offset to tile (useful when climbing stairs)
		sprite_princess->y = (tile_start_y << 3) + (sprite_princess->y & 0x7);
	} else {
		SpriteManagerAdd(SpritePrincess, tile_start_x << 3, (tile_start_y << 3) + 2);
	}
}

void START() {
	UINT16 tile_start_x, tile_start_y;
	const UINT8* coll_list = 0;
	const UINT8* coll_down_list = 0;
	const struct MapInfoBanked* levels = stages[current_stage];
	const struct MapInfoBanked* level = &levels[current_level];
	UINT8 map_w, map_h;

	INIT_CONSOLE(font, 3, 2);

	GetMapSize(level->bank, level->map, &map_w, &map_h);
	ScrollFindTile(level->bank, level->map, 2, 
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

	InitScroll(level->bank, level->map, coll_list, coll_down_list);

	switch(current_stage) {
		case 1:  PlayMusic(exo_level2, 1); break;
		case 2:  PlayMusic(exo_level3, 1); break;
		default: PlayMusic(exo_level1, 1); break;
	}
}

INT16 Interpole(INT16 a, INT16 b, INT16 t, INT16 max) {
	return a + (b - a) * t / max;
}

void ScrollFindTileInCorners(UINT16 map_w, UINT16 map_h, const struct MapInfoBanked* map, UINT8 tile, UINT16* x, UINT16* y) {
	if(ScrollFindTile(map->bank, map->map, tile, 0, 0, map_w, 1, x, y)) {
		return;
	}
	if(ScrollFindTile(map->bank, map->map, tile, 0, map_h - 1, map_w, 1, x, y)) {
		return;
	}
	if(ScrollFindTile(map->bank, map->map, tile, 0, 0, 1, map_h, x, y)) {
		return;
	}
	if(ScrollFindTile(map->bank, map->map, tile, map_w - 1, 0, 1, map_h, x, y)) {
		return;
	}
}

INT8 load_next = 0;
void ClampScrollLimits();
void LoadNextScreen(UINT8 current_level, UINT8 next_level) {
	Sprite* player = scroll_target;
	INT16 scroll_start_x = scroll_x;
	INT16 scroll_start_y = scroll_y;
	INT16 player_start_x = player->x;
	INT16 player_start_y = player->y;
	UINT8 ix;
	UINT16 tile_start_x, tile_start_y;
	INT16 scroll_end_x, scroll_end_y, player_end_x, player_end_y;
	INT16 offset_x = 0;
	INT16 offset_y = 0;
	const struct MapInfoBanked* levels = stages[current_stage];
	const struct MapInfoBanked* next_map = &levels[next_level];
	const struct MapInfoBanked* current_map = &levels[current_level];
	UINT8 next_level_w, next_level_h, current_level_w, current_level_h;

	GetMapSize(next_map->bank, next_map->map, &next_level_w, &next_level_h);
	GetMapSize(current_map->bank, current_map->map, &current_level_w, &current_level_h);

	ScrollFindTileInCorners(next_level_w, next_level_h, next_map, load_next == -1 ? 1 : 2, &tile_start_x, &tile_start_y);
	wait_vbl_done();
	InitPlayerPos(tile_start_x, tile_start_y);
	ScrollSetMap(next_map->bank, next_map->map);
	
	if((tile_start_x == 0) || (tile_start_x == next_level_w - 1)) {
		if(tile_start_x == 0) {
			offset_x = current_level_w << 3;
			offset_x = -offset_x;
		} else  { // tile_start_x == levels[next_level].w - 1)
			offset_x = next_level_w << 3;
		}
		offset_y = (tile_start_y << 3) - (INT16)((player_start_y + (player->coll_h - 1)) & 0xFFF8);

		//This keeps the scroll y in the same position it was on the previous screen
		//scroll_y = player->y + (old_scr_y - player_start_y);
		//ClampScrollLimits();	
		//scroll_end_y = scroll_y;
	}
	
	if((tile_start_y == 0) || (tile_start_y == next_level_h - 1)) {
		if(tile_start_y == 0) {
			offset_y = current_level_h << 3;
			offset_y = -offset_y;
		} else { //(tile_start_y == levels[next_level].h - 1)
			offset_y = next_level_h << 3;
		}
		offset_x = (tile_start_x << 3) - (INT16)((player_start_x) & 0xFFF8);
	}

	//Adding offset_x and offset_y will convert coordinates from old screen to the new one
	scroll_offset_x = 0x1F & (scroll_offset_x - (offset_x >> 3));
	scroll_start_x += offset_x;
	scroll_offset_y = 0x1F & (scroll_offset_y - (offset_y >> 3));
	scroll_start_y += offset_y;

	scroll_end_x = scroll_x;
	scroll_end_y = scroll_y;
	scroll_x_vblank = scroll_x = scroll_start_x;
	scroll_y_vblank = scroll_y = scroll_start_y;
	
	player_start_x += offset_x;
	player_start_y += offset_y;
	player_end_x = player->x;
	player_end_y = player->y;
	player->anim_data = 0; //Animation data is in another bank, we must remove it

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
			Interpole(scroll_start_x, scroll_end_x, ix, SCREENWIDTH), 
			Interpole(scroll_start_y, scroll_end_y, ix, SCREENWIDTH)
		);
		
		player->x = Interpole(player_start_x, player_end_x, ix, SCREENWIDTH);
		player->y = Interpole(player_start_y, player_end_y, ix, SCREENWIDTH);
		THIS = player;
		DrawSprite();

		wait_vbl_done();
		SwapOAMs();
	}
	player->x = player_end_x;
	player->y = player_end_y;
	clamp_enabled = 1;
}

UINT8 wait_end_time = 0;
void UPDATE() {
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

