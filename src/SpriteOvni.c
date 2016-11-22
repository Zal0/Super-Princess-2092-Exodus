#pragma bank=2
#include "SpriteOvni.h"
UINT8 bank_SPRITE_OVNI = 2;

#include "Math.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "GBJAM2016.h"

struct OvniCustomData {
	fixed tx, vx;
	UINT8 missile_launched;
};

void Start_SPRITE_OVNI(struct Sprite* sprite) {
	struct OvniCustomData* data = (struct OvniCustomData*)sprite->custom_data;

	data->vx.w = 0;
	data->tx.w = 0;
	data->missile_launched = 0;
}

void Update_SPRITE_OVNI() {
	struct OvniCustomData* data = (struct OvniCustomData*)sprite_manager_current_sprite->custom_data;
	
	if(data->vx.w == 0) {
		if(U_LESS_THAN(sprite_manager_current_sprite->y, scroll_y)) {
			sprite_manager_current_sprite->y ++;
		} else {
			if(U_LESS_THAN(scroll_target->x, sprite_manager_current_sprite->x)) {
				data->vx.w = -255;
			} else {
				data->vx.w = 255;
			}
		}
	} else {
		data->tx.w += data->vx.w << (INT16)delta_time;
		sprite_manager_current_sprite->x += (INT16)data->tx.b.h;
		data->tx.b.h = 0;

		if(data->missile_launched == 0) {
			if( (U_LESS_THAN(data->vx.w, 0) && U_LESS_THAN(sprite_manager_current_sprite->x, scroll_target->x)) ||
					(U_LESS_THAN(0, data->vx.w) && U_LESS_THAN(scroll_target->x, sprite_manager_current_sprite->x)) 
			) {
				SpriteManagerAdd(SPRITE_MISSILE, sprite_manager_current_sprite->x, sprite_manager_current_sprite->y + 8);
				data->missile_launched = 1;
			}
		}
	}
}

void Destroy_SPRITE_OVNI() {
}
