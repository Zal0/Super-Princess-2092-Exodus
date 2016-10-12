#pragma bank=2
#include "SpriteShooter.h"
UINT8 bank_SPRITE_SHOOTER = 2;

#include "SpriteManager.h"
#include "../res/src/wallshooter.h"
#include "SpriteEnemyBullet.h"

extern UINT8 wshooter_idx;
const UINT8 wshooter_anim_idle[] = {1, 0};
const UINT8 wshooter_anim_fire[] = {1, 1};

struct WShooterCustomData {
	UINT8 cool_down;
};

void Start_SPRITE_SHOOTER(struct Sprite* sprite) { 
	struct WShooterCustomData* data = (struct WShooterCustomData*)sprite->custom_data;
	InitSprite(sprite, FRAME_16x16, wshooter_idx >> 2);
	SetSpriteAnim(sprite, wshooter_anim_idle, 3u);

	data->cool_down = 0;
}

void Update_SPRITE_SHOOTER() {
	struct WShooterCustomData* data = (struct WShooterCustomData*)sprite_manager_current_sprite->custom_data;
	
	data->cool_down += 1 << delta_time;
	if(data->cool_down > 70) {
		CreateEnemyBullet(sprite_manager_current_sprite->x, sprite_manager_current_sprite->y, -1, 0);
		data->cool_down = 0;
	}

	if(data->cool_down < 5u) {
		SetSpriteAnim(sprite_manager_current_sprite, wshooter_anim_fire, 3);
	} else {
		SetSpriteAnim(sprite_manager_current_sprite, wshooter_anim_idle, 3);
	}
}

void Destroy_SPRITE_SHOOTER() { 
}