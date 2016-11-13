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

	data->ty.w = 0;
	data->vy.w = 255;
}

void Update_SPRITE_MISSILE() {
	struct MissileCustomData* data = sprite_manager_current_sprite->custom_data;

	if(U_LESS_THAN(data->vy.w, 1600)) {
		data->vy.w += 32;
	}

	data->ty.w += data->vy.w;
	if( TranslateSprite(sprite_manager_current_sprite, 0, (INT16)data->ty.b.h)) {
		SpriteManagerRemove(sprite_manager_current_index);
		SpriteManagerAdd(SPRITE_EPARTICLE, sprite_manager_current_sprite->x, sprite_manager_current_sprite->y);
	}
	data->ty.b.h = 0;
}

void Destroy_SPRITE_MISSILE() {
}

