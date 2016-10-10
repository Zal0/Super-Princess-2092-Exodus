#pragma bank=2
#include "SpriteShooter.h"
UINT8 bank_SPRITE_SHOOTER = 2;

#include "SpriteManager.h"
#include "../res/src/wallshooter.h"
#include "SpriteEnemyBullet.h"

extern UINT8 wshooter_idx;
const UINT8 wshooter_anim_idle[] = {1, 0};
const UINT8 wshooter_anim_fire[] = {1, 1};

#define NUM_CUSTOMS_DATA 5
#define CUSTOM_DATA_TYPE  WShooterCustomData
#define CUSTOM_DATA_VAR   wShooterCustomData
#define CUSTOM_DATA_STACK wShooterCustomDataStack

struct CUSTOM_DATA_TYPE {
	UINT8 cool_down;
} CUSTOM_DATA_VAR[NUM_CUSTOMS_DATA];
DECLARE_STACK(CUSTOM_DATA_STACK, NUM_CUSTOMS_DATA);

void WShooterResetCustomData() {
	UINT8 i;
	CUSTOM_DATA_STACK[0] = 0;
	for(i = 0; i < NUM_CUSTOMS_DATA; ++i) {
		StackPush(CUSTOM_DATA_STACK, i);
	}
}

void Start_SPRITE_SHOOTER(struct Sprite* sprite) { 
	struct CUSTOM_DATA_TYPE* data;
	InitSprite(sprite, FRAME_16x16, wshooter_idx >> 2);
	SetSpriteAnim(sprite, wshooter_anim_idle, 3u);

	sprite->custom_data_idx = StackPop(CUSTOM_DATA_STACK);
	data = &CUSTOM_DATA_VAR[sprite->custom_data_idx];
	data->cool_down = 0;
}

void Update_SPRITE_SHOOTER() {
	struct CUSTOM_DATA_TYPE* data = &CUSTOM_DATA_VAR[sprite_manager_current_sprite->custom_data_idx];
	
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
	StackPush(CUSTOM_DATA_STACK, sprite_manager_current_sprite->custom_data_idx);
}