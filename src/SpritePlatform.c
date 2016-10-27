#pragma bank=2
#include "SpritePlatform.h"
UINT8 bank_SPRITE_PLATFORM = 2;

#include "SpriteManager.h"
#include "Scroll.h"

struct PlatformCustomData {
	INT8 vx, vy;
	INT8 frame_accum;
};

void Start_SPRITE_PLATFORM(struct Sprite* sprite) {
	struct PlatformCustomData* data = (struct PlatformCustomData*)sprite->custom_data;
	data->vy =  -1;
	data->vx =  0;
	data->frame_accum = 0;

	sprite->x += 4;
}

void Update_SPRITE_PLATFORM() {
	struct PlatformCustomData* data = (struct PlatformCustomData*)sprite_manager_current_sprite->custom_data;
	struct Sprite* sprite = sprite_manager_current_sprite;
	UINT8 offset_x = 8;
	UINT8 offset_y = 8;
	UINT8 tile;

	data->frame_accum += 8;
	while((data->frame_accum >> 4) > 1) {
		data->frame_accum -= 1 << 4;


		sprite->x += (INT16)data->vx;
		sprite->y += (INT16)data->vy;


		if(data->vy != 0 && (0x7 & (sprite->y + offset_y)) == 4) {
			tile = GetScrollTile((sprite->x + offset_x) >> 3, (sprite->y + offset_y) >> 3);
			switch(tile) {
				case 51:
				case 52:
					data->vx = -1;
					data->vy = 0;
					break;

				case 53:
				case 54:
					data->vx = 1;
					data->vy = 0;
					break;
			}
		}else if(data->vx != 0 && (0x7 & (sprite->x + offset_x)) == 4) {
			tile = GetScrollTile((sprite->x + offset_x) >> 3, (sprite->y + offset_y) >> 3);
			switch(tile) {
				case 51:
				case 53:
					data->vx = 0;
					data->vy = 1;
					break;

				case 52:
				case 54:
					data->vx =  0;
					data->vy = -1;
					break;
			}
		}
	}
}

void Destroy_SPRITE_PLATFORM() {
}