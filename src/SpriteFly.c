#include "Banks/SetAutoBank.h"
#include "main.h"

#include "Scroll.h"
#include "Math.h"
#include "SpriteManager.h"


typedef struct {
	fixed vx, vy;
	UINT16 tx, ty;
} CUSTOM_DATA;


const UINT8 anim_fly[] = {2, 0, 1};

#define DIST_ACTION 40
#define DIST_COUNTER 40
#define ACCEL_OFFSET 4
#define HEIGHT 50
void START() {
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	
	SetSpriteAnim(THIS, anim_fly, 33);
	data->vx.w = 0;
	data->vy.w = 0;
	data->tx = 0;
	if(U_LESS_THAN(scroll_target->x, THIS->x))
		THIS->mirror = NO_MIRROR;
	else
		THIS->mirror = V_MIRROR;
}

void UPDATE() {
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

	if(scroll_target) {
		if(data->tx == 0) {
			data->vx.w = (THIS->mirror == NO_MIRROR) ? (data->vx.w - (100 << delta_time)) : (data->vx.w + (100 << delta_time));
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
					if(THIS->mirror == NO_MIRROR) {
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
					if(U_LESS_THAN(scroll_target->x, THIS->x))
						THIS->mirror = NO_MIRROR;
					else
						THIS->mirror = V_MIRROR;
					data->tx = 0;
				}
			}
		}
	}
	

	THIS->x += (INT8)data->vx.b.h;
	THIS->y += (INT8)data->vy.b.h;
	data->vx.b.h = 0;
	data->vy.b.h = 0;
}

void DESTROY() {
}