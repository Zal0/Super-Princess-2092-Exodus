#include "Banks/SetAutoBank.h"
#include "main.h"

#include "Math.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "ZGBMain.h"
#include "Scroll.h"
#include "Sound.h"

typedef struct {
	fixed ty, vy;
} CUSTOM_DATA;


void START() {
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

	data->ty.w = 0;
	data->vy.w = 255;
}

void UPDATE() {
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

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

void DESTROY() {
}

