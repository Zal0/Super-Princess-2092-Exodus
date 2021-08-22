#include "Banks/SetAutoBank.h"
#include "main.h"

#include "SpriteManager.h"
#include "ZGBMain.h"

const UINT8 pparticle_anim_idle[] = {2, 0, 1};

struct PParticleCustomData {
	INT16 vx;
	INT16 vy;
};

void CreatePParticle(UINT16 x, UINT16 y, INT8 vx, INT8 vy) BANKED{
	struct Sprite* spr = SpriteManagerAdd(SpritePrincessParticle, x, y);
	struct PParticleCustomData* data = (struct PParticleCustomData*)spr->custom_data;

	data->vx = vx;
	data->vy = vy;
}

void Start_SpritePrincessParticle() {
	SetSpriteAnim(THIS, pparticle_anim_idle, 10u);
}

void Update_SpritePrincessParticle() {
	struct PParticleCustomData* data = (struct PParticleCustomData*)THIS->custom_data;
	
	THIS->x += (INT16)data->vx << delta_time;
	THIS->y += (INT16)data->vy << delta_time;
}

void Destroy_SpritePrincessParticle() {
}
