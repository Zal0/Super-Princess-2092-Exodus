#pragma bank 2
#include "SpriteShooter.h"
UINT8 bank_SPRITE_SHOOTER = 2;

#include "SpriteManager.h"
#include "../res/src/wallshooter.h"
#include "SpriteEnemyBullet.h"

#include "Scroll.h"

struct WShooterCustomData {
	UINT8 cool_down;
};

void Start_SPRITE_SHOOTER() { 
	UINT8 tile = GetScrollTile((THIS->x - 8) >> 3, THIS->y >> 3);
	struct WShooterCustomData* data = (struct WShooterCustomData*)THIS->custom_data;
	data->cool_down = 70;

	if(scroll_collisions[tile] == 1u) {
		THIS->flags = OAM_VERTICAL_FLAG;
	}
}

void Update_SPRITE_SHOOTER() {
	struct WShooterCustomData* data = (struct WShooterCustomData*)THIS->custom_data;
	
	data->cool_down += 1 << delta_time;
	if(data->cool_down > 70) {
		if(THIS->flags == OAM_VERTICAL_FLAG) {
			CreateEnemyBullet(THIS->x + 8, THIS->y, 1, 0);
		} else {
			CreateEnemyBullet(THIS->x, THIS->y, -1, 0);
		}
		data->cool_down = 0;
	}

	if(data->cool_down < 5u) {
		THIS->current_frame = 1;
	} else {
		THIS->current_frame = 0;
	}
}

void Destroy_SPRITE_SHOOTER() { 
}