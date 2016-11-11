#pragma bank=2
#include "SpriteFly.h"
UINT8 bank_SPRITE_FLY = 2;

#include "Scroll.h"
#include "Math.h"
#include "SpriteManager.h"


struct FlyCustomData {
	fixed vx, vy;
	UINT16 h;
};


const UINT8 anim_fly[] = {2, 0, 1};

#define DIST_ACTION 40
#define DIST_COUNTER 40
#define ACCEL_OFFSET 4
#define HEIGHT 30
void Start_SPRITE_FLY(struct Sprite* sprite) {
	struct FlyCustomData* data = (struct FlyCustomData*)sprite->custom_data;
	
	SetSpriteAnim(sprite, anim_fly, 33);
	data->vx.w = 0;
	data->vy.w = 0;
	data->h = scroll_target->y - HEIGHT;
}

void Update_SPRITE_FLY() {
	struct FlyCustomData* data = (struct FlyCustomData*)sprite_manager_current_sprite->custom_data;

	if(sprite_manager_current_sprite->flags == 0) { //Moving Left
		data->vx.w -= 100;
		if(U_LESS_THAN(scroll_target->x, sprite_manager_current_sprite->x)) {
			if(U_LESS_THAN(sprite_manager_current_sprite->x - DIST_ACTION, scroll_target->x)){
				data->vx.w += (scroll_target->x - sprite_manager_current_sprite->x) << ACCEL_OFFSET;
				data->vy.w += (scroll_target->y + 8 - sprite_manager_current_sprite->y) << ACCEL_OFFSET;
				data->h = scroll_target->y - HEIGHT;
			} 
		} else {
			if(U_LESS_THAN(sprite_manager_current_sprite->x + DIST_COUNTER, scroll_target->x)){
				sprite_manager_current_sprite->flags = OAM_VERTICAL_FLAG;
			} else {
				data->vy.w += (data->h - sprite_manager_current_sprite->y) << ACCEL_OFFSET;
			}
		} 
	} else {
		data->vx.w += 100;
		if(U_LESS_THAN(sprite_manager_current_sprite->x, scroll_target->x)) {
			if(U_LESS_THAN(scroll_target->x, sprite_manager_current_sprite->x + DIST_ACTION)){
				data->vx.w += (scroll_target->x - sprite_manager_current_sprite->x) << ACCEL_OFFSET;
				data->vy.w += (scroll_target->y + 8 - sprite_manager_current_sprite->y) << ACCEL_OFFSET;
				data->h = scroll_target->y - HEIGHT;
			} 
		} else {
			if(U_LESS_THAN(scroll_target->x, sprite_manager_current_sprite->x - DIST_COUNTER)){
				sprite_manager_current_sprite->flags = 0;
			} else {
				data->vy.w += (data->h - sprite_manager_current_sprite->y) << ACCEL_OFFSET;
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