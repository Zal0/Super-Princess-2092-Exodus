#pragma bank 2
#include "SpriteMissile.h"
UINT8 bank_SPRITE_MISSILE = 2;

#include "Math.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "GBJAM2016.h"
#include "Scroll.h"
#include "Sound.h"

struct MissileCustomData {
	fixed ty, vy;
};


void Start_SPRITE_MISSILE() {
	struct MissileCustomData* data = (struct MissileCustomData*)THIS->custom_data;

	THIS->coll_x += 2;
	THIS->coll_w -= 4;

	data->ty.w = 0;
	data->vy.w = 255;
}

void Update_SPRITE_MISSILE() {
	struct MissileCustomData* data = (struct MissileCustomData*)THIS->custom_data;

	if(U_LESS_THAN(data->vy.w, 1600)) {
		data->vy.w += 32 << delta_time;
	}

	data->ty.w += data->vy.w;
	if( TranslateSprite(THIS, 0, (INT16)data->ty.b.h)) {
		SpriteManagerRemove(THIS_IDX);
		SpriteManagerAdd(SPRITE_EPARTICLE, THIS->x, THIS->y);
		PlayFx(CHANNEL_4, 20, 0x0d, 0xff, 0x7d, 0xc0);
	}
	data->ty.b.h = 0;
}

void Destroy_SPRITE_MISSILE() {
}

