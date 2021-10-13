#include "ZGBMain.h"
#include "Math.h"

UINT8 next_state = StateMenu;

extern UINT8* tile_replacement_tile_ptr;
extern UINT8* tile_replacement_ptr;
extern UINT8  tile_replacement_enemy_type;

void GetTileReplacement() {
	if(current_state == StateGame) {
		switch (*tile_replacement_tile_ptr) {
			case 1:
			case 2:
				//Fix for the stairs
				if(*(tile_replacement_tile_ptr + 1) == 24) 
					*tile_replacement_ptr = 23;
				else
					*tile_replacement_ptr = 0;
				tile_replacement_enemy_type = 255u;
				return;

			default:
				tile_replacement_enemy_type = (255u - *tile_replacement_tile_ptr);
				if(tile_replacement_enemy_type < N_SPRITE_TYPES) {
					*tile_replacement_ptr = 0;
					return;
				}
				break;
		}
	}

	tile_replacement_enemy_type = 255u;
	*tile_replacement_ptr = *tile_replacement_tile_ptr;
}