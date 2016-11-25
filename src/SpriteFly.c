#pragma bank=1
#include "SpriteFly.h"
UINT8 bank_SPRITE_FLY = 1;

#include "Scroll.h"
#include "Math.h"
#include "SpriteManager.h"


struct FlyCustomData {
	fixed vx, vy;
	UINT16 tx, ty;
};


const UINT8 anim_fly[] = {2, 0, 1};

#define DIST_ACTION 40
#define DIST_COUNTER 40
#define ACCEL_OFFSET 4
#define HEIGHT 50
void Start_SPRITE_FLY(struct Sprite* sprite) {
	struct FlyCustomData* data = (struct FlyCustomData*)sprite->custom_data;
	
	SetSpriteAnim(sprite, anim_fly, 33);
	data->vx.w = 0;
	data->vy.w = 0;
	data->tx = 0;
	sprite->flags = U_LESS_THAN(scroll_target->x, sprite->x) ? 0 : OAM_VERTICAL_FLAG;
}

void Update_SPRITE_FLY() {
	struct FlyCustomData* data = (struct FlyCustomData*)THIS->custom_data;

	if(scroll_target) {
		if(data->tx == 0) {
			data->vx.w = (THIS->flags == 0) ? (data->vx.w - (100 << delta_time)) : (data->vx.w + (100 << delta_time));
			if(U_LESS_THAN(DISTANCE(THIS->x + 8, scroll_target->x + 8), DIST_ACTION)){
				data->tx = scroll_target->x;
				data->ty = scroll_target->y + 8;
			} 
		} else {
			data->vx.w += (data->tx - THIS->x) << ACCEL_OFFSET << delta_time;
			data->vy.w += (data->ty - THIS->y) << ACCEL_OFFSET << delta_time;
			if(U_LESS_THAN(THIS->y, data->ty)) {
				//ATTACKING
				if(U_LESS_THAN(DISTANCE(data->ty, THIS->y), 8)){
					if(THIS->flags == 0) {
						if(U_LESS_THAN(THIS->x - 8, scroll_target->x)) {
							data->tx = (scroll_target->x - DIST_COUNTER);
						}
					} else {
						if(U_LESS_THAN(scroll_target->x - 8, THIS->x)) {
							data->tx = (scroll_target->x + DIST_COUNTER);
						}
					}

					data->ty = data->ty - HEIGHT;
				}
			} else {
				//CHARGING 
				if(U_LESS_THAN(DISTANCE(data->ty, THIS->y), 4)){
					THIS->flags = U_LESS_THAN(scroll_target->x, THIS->x) ? 0 : OAM_VERTICAL_FLAG;
					data->tx = 0;
				}
			}
		}
	}
	

	THIS->x += (INT16)data->vx.b.h;
	THIS->y += (INT16)data->vy.b.h;
	data->vx.b.h = 0;
	data->vy.b.h = 0;
}

void Destroy_SPRITE_FLY() {
}