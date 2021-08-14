#include "Banks/SetBank2.h"
#include "main.h"

#include "SpriteManager.h"
#include "Scroll.h"
#include "Print.h"
#include "Math.h"

#include "Print.h"

struct PlatformCustomData {
	INT8 vx, vy;
	INT8 frame_accum;
};

void Start_SpritePlatform() {
	UINT16 tile_x = THIS->x >> 3;
	UINT16 tile_y = THIS->y >> 3;
	UINT16 tile;

	struct PlatformCustomData* data = (struct PlatformCustomData*)THIS->custom_data;
	data->frame_accum = 0;

	tile = GetScrollTile(tile_x + 1, tile_y + 1);
	if(U_LESS_THAN(48u, tile) && U_LESS_THAN(tile, 55u)) {
		data->vy = -1;
		data->vx =  0;
		THIS->x += 4;
	} else {
		tile = GetScrollTile(tile_x - 1, tile_y + 1);
		if(U_LESS_THAN(48u, tile) && U_LESS_THAN(tile, 55u)) {
			data->vy = 1;
			data->vx = 0;
			THIS->x -= 12;
		} else {
			tile = GetScrollTile(tile_x, tile_y + 2);
			if(U_LESS_THAN(48u, tile) && U_LESS_THAN(tile, 55u)) {
				data->vy =  0;
				data->vx = -1;
				THIS->y += 12;
			} else {
				tile = GetScrollTile(tile_x, tile_y);
				if(U_LESS_THAN(48u, tile) && U_LESS_THAN(tile, 55u)) {
					data->vy = 0;
					data->vx = 1;
					THIS->y -= 4;
				}
			}
		}
	}

	THIS->lim_x = 100u;
	THIS->lim_y = 100u;
}

extern struct Sprite* princess_parent;
extern UINT16 princess_old_x;
extern UINT16 princess_old_y;
extern struct Sprite* sprite_princess;

struct Rect {
	UINT16 x, y;
	UINT16 w, h;
};
void CreateRect(UINT16 x1, UINT16 y1, UINT16 x2, UINT16 y2, struct Rect* rect) {
	UINT16 tmp0, tmp1; // I need to use this tmp vars because after exiting the ifs the value is broken (stack broken??)

	if(U_LESS_THAN(x2, x1)) {
		tmp0 = x2;
		tmp1 = x1 - x2;
	} else {
		tmp0 = x1;
		tmp1 = x2 - x1;
	}
	rect->x = tmp0;
	rect->w = tmp1;

	if(U_LESS_THAN(y2, y1)) {
		tmp0 = y2;
		tmp1 = y1 - y2;
	} else {
		tmp0 = y1;
		tmp1 = y2 - y1;
	}
	rect->y = tmp0;
	rect->h = tmp1;
}

UINT8 CheckColl(UINT16 x1, UINT16 y1, UINT16 w1, UINT16 h1,
	              UINT16 x2, UINT16 y2, UINT16 w2, UINT16 h2) {
	if( U_LESS_THAN((x1 + w1), x2) ||
	    U_LESS_THAN((x2 + w2), x1) ||
			U_LESS_THAN((y1 + h1), y2) ||
			U_LESS_THAN((y2 + h2), y1)
	) {
		return 0;
	} else {
		return 1;
	}
}

void Update_SpritePlatform() {
	struct PlatformCustomData* data = (struct PlatformCustomData*)THIS->custom_data;
	struct Sprite* sprite = THIS;
	UINT8 offset_x = 8;
	UINT8 offset_y = 3;
	UINT8 tile;
	struct Rect r1, r2;
	UINT16 old_x, old_y;

	data->frame_accum += 8;
	old_x = sprite->x;
	old_y = sprite->y;
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

	if(princess_parent == 0) {
		CreateRect( sprite_princess->x, 
				        princess_old_y + sprite_princess->coll_h, //Old sprite bottom
				        sprite_princess->x + sprite_princess->coll_w, 
				        sprite_princess->y + sprite_princess->coll_h, //Current sprite bottom
				        &r1);

		CreateRect( old_x,
			          old_y,
			          sprite->x + sprite->coll_w,
			          sprite->y,
			          &r2);
		

		if(U_LESS_THAN(0, sprite_princess->y - princess_old_y)) { //Only check collision when the sprite is falling
			if(CheckColl(r1.x, r1.y, r1.w, r1.h, r2.x, r2.y, r2.w, r2.h)) {
				princess_parent = THIS;
				sprite_princess->y = sprite->y - sprite_princess->coll_h;
			}
		}
	} else if(princess_parent == THIS) {
		//If it goes beyond left or right  limits, detach (the sprite will detach itself when jumping)
		if( U_LESS_THAN((sprite->x + sprite->coll_w), (sprite_princess->x)) ||
				U_LESS_THAN((sprite_princess->x + sprite_princess->coll_w), sprite->x)
		) {
			princess_parent = 0;
		} else {
			sprite_princess->x += sprite->x - old_x;
			sprite_princess->y += sprite->y - old_y;
			RefreshScroll();
		}
	}
}

void Destroy_SpritePlatform() {
}