#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_SHOOTER = 2;

#include "SpriteManager.h"
#include "../res/src/wallshooter.h"

#include "Scroll.h"

void CreateEnemyBullet(UINT16 x, UINT16 y, INT8 vx, INT8 vy);

struct WShooterCustomData {
	UINT8 cool_down;
};

void Start_SPRITE_SHOOTER() { 
	UINT8 tile = GetScrollTile((THIS->x - 8) >> 3, THIS->y >> 3);
	struct WShooterCustomData* data = (struct WShooterCustomData*)THIS->custom_data;
	data->cool_down = 70;

	if(scroll_collisions[tile] == 1u) {
		SPRITE_SET_VMIRROR(THIS);
	}
}

void Update_SPRITE_SHOOTER() {
	struct WShooterCustomData* data = (struct WShooterCustomData*)THIS->custom_data;
	
	data->cool_down += 1 << delta_time;
	if(data->cool_down > 70) {
		if(SPRITE_GET_VMIRROR(THIS)) {
			CreateEnemyBullet(THIS->x + 8, THIS->y, 1, 0);
		} else {
			CreateEnemyBullet(THIS->x, THIS->y, -1, 0);
		}
		data->cool_down = 0;
	}

	if(data->cool_down < 5u) {
		SET_FRAME(THIS, (UINT8)1u);
	} else {
		SET_FRAME(THIS, (UINT8)0u);
	}
}

void Destroy_SPRITE_SHOOTER() { 
}