#include "Banks/SetBank2.h"
#include "main.h"

#include "SpriteManager.h"

#include "Scroll.h"

void CreateEnemyBullet(UINT16 x, UINT16 y, INT8 vx, INT8 vy);

struct WShooterCustomData {
	UINT8 cool_down;
};

void Start_SpriteShooter() { 
	UINT8 tile = GetScrollTile((THIS->x - 8) >> 3, THIS->y >> 3);
	struct WShooterCustomData* data = (struct WShooterCustomData*)THIS->custom_data;
	data->cool_down = 70;

	if(scroll_collisions[tile] == 1u) {
		THIS->mirror = V_MIRROR;
	}
}

void Update_SpriteShooter() {
	struct WShooterCustomData* data = (struct WShooterCustomData*)THIS->custom_data;
	
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

void Destroy_SpriteShooter() { 
}