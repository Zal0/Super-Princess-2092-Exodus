#pragma bank=2
#include "SpriteShooter.h"
UINT8 bank_SPRITE_SHOOTER = 2;

#include "SpriteManager.h"
#include "../res/src/wallshooter.h"
#include "SpriteEnemyBullet.h"

#include "Scroll.h"

struct WShooterCustomData {
	UINT8 cool_down;
};

void Start_SPRITE_SHOOTER(struct Sprite* sprite) { 
	UINT8 tile = GetScrollTile((sprite->x - 8) >> 3, sprite->y >> 3);
	struct WShooterCustomData* data = (struct WShooterCustomData*)sprite->custom_data;
	data->cool_down = 70;

	if(scroll_collisions[tile] == 1u) {
		sprite->flags = OAM_VERTICAL_FLAG;
	}
}

void Update_SPRITE_SHOOTER() {
	struct WShooterCustomData* data = (struct WShooterCustomData*)sprite_manager_current_sprite->custom_data;
	
	data->cool_down += 1 << delta_time;
	if(data->cool_down > 70) {
		if(sprite_manager_current_sprite->flags == OAM_VERTICAL_FLAG) {
			CreateEnemyBullet(sprite_manager_current_sprite->x + 8, sprite_manager_current_sprite->y, 1, 0);
		} else {
			CreateEnemyBullet(sprite_manager_current_sprite->x, sprite_manager_current_sprite->y, -1, 0);
		}
		data->cool_down = 0;
	}

	if(data->cool_down < 5u) {
		sprite_manager_current_sprite->current_frame = 1;
	} else {
		sprite_manager_current_sprite->current_frame = 0;
	}
}

void Destroy_SPRITE_SHOOTER() { 
}