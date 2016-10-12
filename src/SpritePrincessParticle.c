#pragma bank=2
#include "SpritePrincessParticle.h"
UINT8 bank_SPRITE_PPARTICLE = 2;

#include "SpriteManager.h"
#include "../res/src/enemybullet16x16.h"
#include "GBJAM2016.h"

extern UINT8 princess_idx;
const UINT8 pparticle_anim_idle[] = {2, 12, 13};

struct PParticleCustomData {
	INT16 vx;
	INT16 vy;
};

void CreatePParticle(UINT16 x, UINT16 y, INT8 vx, INT8 vy){
	struct Sprite* spr = SpriteManagerAdd(SPRITE_PPARTICLE);
	struct PParticleCustomData* data = (struct PParticleCustomData*)spr->custom_data;
	spr->x = x;
	spr->y = y;

	data->vx = vx;
	data->vy = vy;
}

void Start_SPRITE_PPARTICLE(struct Sprite* sprite) {
	InitSprite(sprite, FRAME_16x16, princess_idx >> 2);
	SetSpriteAnim(sprite, pparticle_anim_idle, 10u);
}

void Update_SPRITE_PPARTICLE() {
	struct PParticleCustomData* data = (struct PParticleCustomData*)sprite_manager_current_sprite->custom_data;
	
	sprite_manager_current_sprite->x += (INT16)data->vx << delta_time;
	sprite_manager_current_sprite->y += (INT16)data->vy << delta_time;
}

void Destroy_SPRITE_PPARTICLE() {
}