#include "Banks/SetAutoBank.h"
#include "main.h"

#include "SpriteManager.h"

#include "Scroll.h"

void CreateEnemyBullet(UINT16 x, UINT16 y, INT8 vx, INT8 vy) BANKED;

typedef struct {
	UINT8 cool_down;
} CUSTOM_DATA;

void START() { 
	UINT8 tile = GetScrollTile((THIS->x - 8) >> 3, THIS->y >> 3);
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	data->cool_down = 70;

	if(scroll_collisions[tile] == 1u) {
		THIS->mirror = V_MIRROR;
	}
}

void UPDATE() {
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	
	data->cool_down += 1 << delta_time;
	if(data->cool_down > 70) {
		if(THIS->mirror) {
			CreateEnemyBullet(THIS->x + 12, THIS->y + 6, 1, 0);
		} else {
			CreateEnemyBullet(THIS->x + 4, THIS->y + 6, -1, 0);
		}
		data->cool_down = 0;
	}

	if(data->cool_down < 5u) {
		SetFrame(THIS, 1);
	} else {
		SetFrame(THIS, 0);
	}
}

void DESTROY() { 
}