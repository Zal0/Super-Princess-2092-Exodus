#pragma bank=2
#include "SpriteMissile.h"
UINT8 bank_SPRITE_MISSILE = 2;

#include "Math.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "GBJAM2016.h"
#include "Scroll.h"

struct MissileCustomData {
	fixed ty, vy;
};


void Start_SPRITE_MISSILE(struct Sprite* sprite) {
	struct MissileCustomData* data = sprite->custom_data;

	sprite->coll_x += 2;
	sprite->coll_w -= 4;

	data->ty.w = 0;
	data->vy.w = 255;
}

void Update_SPRITE_MISSILE() {
	struct MissileCustomData* data = THIS->custom_data;

	if(U_LESS_THAN(data->vy.w, 1600)) {
		data->vy.w += 32 << delta_time;
	}

	data->ty.w += data->vy.w;
	if( TranslateSprite(THIS, 0, (INT16)data->ty.b.h)) {
		SpriteManagerRemove(sprite_manager_current_index);
		SpriteManagerAdd(SPRITE_EPARTICLE, THIS->x, THIS->y);
	}
	data->ty.b.h = 0;
}

void Destroy_SPRITE_MISSILE() {
}

