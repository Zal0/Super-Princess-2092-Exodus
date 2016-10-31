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

extern struct Sprite* princess_parent;
extern UINT16 princess_old_x;
extern UINT16 princess_old_y;
extern struct Sprite* sprite_princess;

#define U_LESS_THAN(A, B) ((A) - (B) & 0x8000u)

struct Rect {
	UINT16 x, y;
	UINT8 w, h;
};
void CreateRect(UINT16 x1, UINT16 y1, UINT16 x2, UINT16 y2, struct Rect* rect) {
	if(x1 > x2) {
		rect->x = x2;
		rect->w = x1 - x2;
	} else {
		rect->x = x1;
		rect->w = x2 + -x1;
	}

	if(y1 > y2) {
		rect->y = y2;
		rect->h = y1 - y2;
	} else {
		rect->y = y1;
		rect->h = y2 - y1;
	}
	/*rect->x = x1;
	rect->w = 16;
	rect->y = y1;
	rect->h = 16;*/
}

UINT8 CheckColl(UINT16 x1, UINT16 y1, UINT8 w1, UINT8 h1,
	              UINT16 x2, UINT16 y2, UINT8 w2, UINT8 h2) {
	if( (x1 + w1 < x2) ||
	    (x1 > x2 + w2) ||
			(y1 + h1 < y2) ||
			(y1 > y2 + h2)
	) {
		return 0;
	} else {
		return 1;
	}
}

void Update_SPRITE_PLATFORM() {
	struct PlatformCustomData* data = (struct PlatformCustomData*)sprite_manager_current_sprite->custom_data;
	struct Sprite* sprite = sprite_manager_current_sprite;
	UINT8 offset_x = 8;
	UINT8 offset_y = 8;
	UINT8 tile;
	struct Rect r1, r2;
	UINT16 old_x, old_y;

	//data->frame_accum += 16;
	//while((data->frame_accum >> 4) > 1) {
	//	data->frame_accum -= 1 << 4;

		/*old_x = sprite->x;
		old_y = sprite->y;
		sprite->x += (INT16)data->vx;
		sprite->y += (INT16)data->vy;*/

		if(princess_parent == 0) {
			CreateRect(sprite_princess->x, sprite_princess->y, sprite_princess->x + 16u, sprite_princess->y + 16, &r1);
			CreateRect(sprite->x,          sprite->y,          sprite->x + 16,           sprite->y + 16,          &r2);

			if(CheckColl(r1.x, r1.y, r1.w, r1.h, r2.x, r2.y, r2.w, r2.h)) {
				princess_parent = sprite_manager_current_sprite;
			}
		} else if(princess_parent == sprite_manager_current_sprite) {
			if((sprite_princess->x + sprite_princess->coll_x) > (sprite->x + sprite->coll_x + sprite->coll_w) ||
				 (sprite_princess->x + sprite_princess->coll_x + sprite_princess->coll_w) < sprite->x
			) {
				princess_parent = 0;
			}

			//sprite_princess->x += (INT16)data->vx;
			//sprite_princess->y += (INT16)data->vy;
		}

		/*if(data->vy != 0 && (0x7 & (sprite->y + offset_y)) == 4) {
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
		}*/
	//}
}

void Destroy_SPRITE_PLATFORM() {
}