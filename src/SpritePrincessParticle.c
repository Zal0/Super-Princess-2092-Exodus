#include "Banks/SetAutoBank.h"
#include "main.h"

#include "SpriteManager.h"
#include "ZGBMain.h"

const UINT8 pparticle_anim_idle[] = {2, 0, 1};

typedef struct {
	INT16 vx;
	INT16 vy;
} CUSTOM_DATA;

void CreatePParticle(UINT16 x, UINT16 y, INT8 vx, INT8 vy) BANKED{
	Sprite* spr = SpriteManagerAdd(SpritePrincessParticle, x, y);
	CUSTOM_DATA* data = (CUSTOM_DATA*)spr->custom_data;

	data->vx = vx;
	data->vy = vy;
}

void START() {
	SetSpriteAnim(THIS, pparticle_anim_idle, 10u);
}

void UPDATE() {
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	
	THIS->x += (INT16)data->vx << delta_time;
	THIS->y += (INT16)data->vy << delta_time;
}

void DESTROY() {
}
