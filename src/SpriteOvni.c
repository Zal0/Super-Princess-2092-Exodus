#include "Banks/SetAutoBank.h"
#include "main.h"

#include "Math.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "ZGBMain.h"

typedef struct {
	fixed tx, vx;
	UINT8 missile_launched;
} CUSTOM_DATA;

void START() {
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

	data->vx.w = 0;
	data->tx.w = 0;
	data->missile_launched = 0;
}

void UPDATE() {
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	
	if(data->vx.w == 0) {
		if(U_LESS_THAN(THIS->y, scroll_y)) {
			THIS->y ++;
		} else {
			if(U_LESS_THAN(scroll_target->x, THIS->x)) {
				data->vx.w = (UWORD)-255;
			} else {
				data->vx.w = 255;
			}
		}
	} else {
		data->tx.w += data->vx.w << (INT16)delta_time;
		THIS->x += (INT8)data->tx.b.h;
		data->tx.b.h = 0;

		if(data->missile_launched == 0) {
			if( (U_LESS_THAN(data->vx.w, 0) && U_LESS_THAN(THIS->x, scroll_target->x)) ||
					(U_LESS_THAN(0, data->vx.w) && U_LESS_THAN(scroll_target->x, THIS->x)) 
			) {
				SpriteManagerAdd(SpriteMissile, THIS->x, THIS->y + 8);
				data->missile_launched = 1;
			}
		}
	}
}

void DESTROY() {
}
