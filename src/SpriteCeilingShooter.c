#include "Banks/SetAutoBank.h"
#include "main.h"

#include "SpriteManager.h"

void CreateEnemyBullet(UINT16 x, UINT16 y, INT8 vx, INT8 vy) BANKED;

typedef struct {
	UINT8 cool_down;
} CUSTOM_DATA;

void START() { 
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

	data->cool_down = 70;
}

void UPDATE() {
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	
	data->cool_down += 1 << delta_time;
	if(data->cool_down > 70) {
		CreateEnemyBullet(THIS->x + 6, THIS->y + 6, 0, 1);
		data->cool_down = 0;
	}

	if(data->cool_down < 10u) {
		SetFrame(THIS, 1);
	} else {
		SetFrame(THIS, 0);
	}
}

void DESTROY() { 
}