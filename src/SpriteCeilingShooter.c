#pragma bank=2
#include "SpriteCeilingShooter.h"
UINT8 bank_SPRITE_CSHOOTER = 2;

#include "../res/src/ceilingshooter.h"
#include "SpriteManager.h"
#include "SpriteEnemyBullet.h"

extern UINT8 cshooter_idx;
const UINT8 cshooter_anim_idle[] = {1, 0};
const UINT8 cshooter_anim_fire[] = {1, 1};

struct CShooterCustomData {
	UINT8 cool_down;
};

void Start_SPRITE_CSHOOTER(struct Sprite* sprite) { 
	struct CShooterCustomData* data = (struct CShooterCustomData*)sprite->custom_data;
	InitSprite(sprite, FRAME_16x16, cshooter_idx >> 2);
	SetSpriteAnim(sprite, cshooter_anim_idle, 3u);

	data->cool_down = 0;
}

void Update_SPRITE_CSHOOTER() {
	struct CShooterCustomData* data = (struct CShooterCustomData*)sprite_manager_current_sprite->custom_data;
	
	data->cool_down += 1 << delta_time;
	if(data->cool_down > 70) {
		CreateEnemyBullet(sprite_manager_current_sprite->x, sprite_manager_current_sprite->y, 0, 1);
		data->cool_down = 0;
	}

	if(data->cool_down < 10u) {
		SetSpriteAnim(sprite_manager_current_sprite, cshooter_anim_fire, 3);
	} else {
		SetSpriteAnim(sprite_manager_current_sprite, cshooter_anim_idle, 3);
	}
}

void Destroy_SPRITE_CSHOOTER() { 
}