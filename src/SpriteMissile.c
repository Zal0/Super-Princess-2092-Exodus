#include "Banks/SetBank2.h"
#include "main.h"

#include "Math.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Sound.h"

struct MissileCustomData {
	fixed ty, vy;
};


void Start_SpriteMissile() {
	struct MissileCustomData* data = (struct MissileCustomData*)THIS->custom_data;

	THIS->coll_x += 2;
	THIS->coll_w -= 4;

	data->ty.w = 0;
	data->vy.w = 255;
}

void Update_SpriteMissile() {
	struct MissileCustomData* data = (struct MissileCustomData*)THIS->custom_data;

	if(U_LESS_THAN(data->vy.w, 1600)) {
		data->vy.w += 32 << delta_time;
	}

	data->ty.w += data->vy.w;
	if( TranslateSprite(THIS, 0, (INT16)data->ty.b.h)) {
		SpriteManagerRemove(THIS_IDX);
		SpriteManagerAdd(SpriteEnemyParticle, THIS->x, THIS->y);
		PlayFx(CHANNEL_4, 20, 0x0d, 0xff, 0x7d, 0xc0);
	}
	data->ty.b.h = 0;
}

void Destroy_SpriteMissile() {
}

