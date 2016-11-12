#pragma bank=2
#include "SpriteFly.h"
UINT8 bank_SPRITE_FLY = 2;

#include "Scroll.h"
#include "Math.h"
#include "SpriteManager.h"


struct FlyCustomData {
	fixed vx, vy;
	UINT16 tx, ty;
};


const UINT8 anim_fly[] = {2, 0, 1};

#define DIST_ACTION 20
#define DIST_COUNTER 10
#define ACCEL_OFFSET 4
#define HEIGHT 50
void Start_SPRITE_FLY(struct Sprite* sprite) {
	struct FlyCustomData* data = (struct FlyCustomData*)sprite->custom_data;
	
	SetSpriteAnim(sprite, anim_fly, 33);
	data->vx.w = 0;
	data->vy.w = 0;
	data->tx = 0;
}

#define DISTANCE(A, B) (U_LESS_THAN(A, B) ? (B - A) : (A - B))

void Update_SPRITE_FLY() {
	struct FlyCustomData* data = (struct FlyCustomData*)sprite_manager_current_sprite->custom_data;

	if(data->tx == 0) {
		data->vx.w = (sprite_manager_current_sprite->flags == 0) ? (data->vx.w - 100) : (data->vx.w + 100);
		if(U_LESS_THAN(DISTANCE(sprite_manager_current_sprite->x, scroll_target->x), DIST_ACTION)){
			data->tx = scroll_target->x;
			data->ty = scroll_target->y + 16;
		} 
	} else {
		data->vx.w += (data->tx - sprite_manager_current_sprite->x) << ACCEL_OFFSET;
		data->vy.w += (data->ty - sprite_manager_current_sprite->y) << ACCEL_OFFSET;
		if(U_LESS_THAN(sprite_manager_current_sprite->y, data->ty)) {
			//ATTACKING
			if(U_LESS_THAN(DISTANCE(data->ty, sprite_manager_current_sprite->y), 8)){
				data->tx = (sprite_manager_current_sprite->flags == 0) ? (data->tx - DIST_COUNTER) : (data->tx + DIST_COUNTER); 
				data->ty = data->ty - HEIGHT;
			}
		} else {
			//CHARGING 
			if(U_LESS_THAN(DISTANCE(data->ty, sprite_manager_current_sprite->y), 4)){
				sprite_manager_current_sprite->flags = U_LESS_THAN(scroll_target->x, sprite_manager_current_sprite->x) ? 0 : OAM_VERTICAL_FLAG;
				data->tx = 0;
			}
		}
	}
	

	sprite_manager_current_sprite->x += (INT16)data->vx.b.h;
	sprite_manager_current_sprite->y += (INT16)data->vy.b.h;
	data->vx.b.h = 0;
	data->vy.b.h = 0;
}

void Destroy_SPRITE_FLY() {
}