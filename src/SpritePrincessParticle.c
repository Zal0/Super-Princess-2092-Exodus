#pragma bank=2
#include "SpritePrincessParticle.h"
UINT8 bank_SPRITE_PPARTICLE = 2;

#include "SpriteManager.h"
#include "../res/src/enemybullet16x16.h"
#include "GBJAM2016.h"

extern UINT8 princess_idx;
const UINT8 pparticle_anim_idle[] = {2, 12, 13};

#define NUM_CUSTOMS_DATA 5
#define CUSTOM_DATA_TYPE  PParticleCustomData
#define CUSTOM_DATA_VAR   pparticleCustomData
#define CUSTOM_DATA_STACK pparticleCustomDataStack

struct CUSTOM_DATA_TYPE {
	INT16 vx;
	INT16 vy;
} CUSTOM_DATA_VAR[NUM_CUSTOMS_DATA];
DECLARE_STACK(CUSTOM_DATA_STACK, NUM_CUSTOMS_DATA);

void PParticleResetCustomData() {
	UINT8 i;
	CUSTOM_DATA_STACK[0] = 0;
	for(i = 0; i < NUM_CUSTOMS_DATA; ++i) {
		StackPush(CUSTOM_DATA_STACK, i);
	}
}

void CreatePParticle(UINT16 x, UINT16 y, INT8 vx, INT8 vy){
	struct CUSTOM_DATA_TYPE* data;
	struct Sprite* spr = SpriteManagerAdd(SPRITE_PPARTICLE);
	spr->x = x;
	spr->y = y;

	data = &CUSTOM_DATA_VAR[spr->custom_data_idx];
	data->vx = vx;
	data->vy = vy;
}

void Start_SPRITE_PPARTICLE(struct Sprite* sprite) {
	InitSprite(sprite, FRAME_16x16, princess_idx >> 2);
	SetSpriteAnim(sprite, pparticle_anim_idle, 10u);

	sprite->custom_data_idx = StackPop(CUSTOM_DATA_STACK);
}

void Update_SPRITE_PPARTICLE() {
	struct CUSTOM_DATA_TYPE* data = &CUSTOM_DATA_VAR[sprite_manager_current_sprite->custom_data_idx];
	
	sprite_manager_current_sprite->x += (INT16)data->vx << delta_time;
	sprite_manager_current_sprite->y += (INT16)data->vy << delta_time;
}

void Destroy_SPRITE_PPARTICLE() {
	StackPush(CUSTOM_DATA_STACK, sprite_manager_current_sprite->custom_data_idx);
}
