#pragma bank=2
#include "SpriteCeilingShooter.h"
UINT8 bank_SPRITE_CSHOOTER = 2;

#include "../res/src/ceilingshooter.h"
#include "SpriteManager.h"
#include "SpriteEnemyBullet.h"

struct CShooterCustomData {
	UINT8 cool_down;
};

void Start_SPRITE_CSHOOTER(struct Sprite* sprite) { 
	struct CShooterCustomData* data = (struct CShooterCustomData*)sprite->custom_data;

	data->cool_down = 0;
}

void Update_SPRITE_CSHOOTER() {
	struct CShooterCustomData* data = (struct CShooterCustomData*)sprite_manager_current_sprite->custom_data;
	
	data->cool_down += 1 << delta_time;
	if(data->cool_down > 70) {
		CreateEnemyBullet(sprite_manager_current_sprite->x + 4, sprite_manager_current_sprite->y, 0, 1);
		data->cool_down = 0;
	}

	if(data->cool_down < 10u) {
		sprite_manager_current_sprite->current_frame = 1;
	} else {
		sprite_manager_current_sprite->current_frame = 0;
	}
}

void Destroy_SPRITE_CSHOOTER() { 
}