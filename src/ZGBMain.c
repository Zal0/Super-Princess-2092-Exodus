#include "ZGBMain.h"
#include "Math.h"

UINT8 next_state = StateMenu;

UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {
	if(current_state == StateGame) {
		*tile = 0;
		switch(*tile_ptr) {
			case 1:
			case 2:
				if(*(tile_ptr + 1) == 24) 
					*tile = 23;
				return 255u;

			default:
				if(U_LESS_THAN(255 - (UINT16)*tile_ptr, N_SPRITE_TYPES)) {
					return 255 - (UINT16)*tile_ptr;
				}
		}
		*tile = *tile_ptr;
	}

	return 255u;
}