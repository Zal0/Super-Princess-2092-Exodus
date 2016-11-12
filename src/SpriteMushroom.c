#pragma bank=2
#include "SpriteMushroom.h"
UINT8 bank_SPRITE_MUSHROOM = 2;

#include "../res/src/mushroom.h"
#include "SpriteManager.h"
#include "SpriteEnemyBullet.h"

const UINT8 mushroom_anim_hide[] = {1, 0};
const UINT8 mushroom_anim_show[] = {1, 1};


struct MushroomCustomData {
	UINT8 time_out;
};

void Start_SPRITE_MUSHROOM(struct Sprite* sprite) {
	struct MushroomCustomData* data = (struct MushroomCustomData*)sprite->custom_data;
	SetSpriteAnim(sprite, mushroom_anim_hide, 3u);

	data->time_out = 200u;
}

UINT16 dist(UINT16 v0, UINT16 v1) {
	if((v0 - v1) & 0xF000)
		return v1 - v0;
	else
		return v0 - v1;
}

extern struct Sprite* sprite_princess;

void Update_SPRITE_MUSHROOM() {
	struct MushroomCustomData* data = (struct MushroomCustomData*)sprite_manager_current_sprite->custom_data;
	UINT8 x;
	
	if(data->time_out > 50) {
		if(sprite_princess && (dist(sprite_princess->x, sprite_manager_current_sprite->x) < 60u)) {
			data->time_out = 0;
			x = ((sprite_princess->x - sprite_manager_current_sprite->x) & 0xF000) ? -1 : 1;

			CreateEnemyBullet(sprite_manager_current_sprite->x, sprite_manager_current_sprite->y, 0, -1);
			CreateEnemyBullet(sprite_manager_current_sprite->x, sprite_manager_current_sprite->y, x,  0);
			
			CreateEnemyBullet(sprite_manager_current_sprite->x, sprite_manager_current_sprite->y, x, -1);
		}
	} else {
		data->time_out += 1;	
	}

	if(data->time_out < 20u) {
		SetSpriteAnim(sprite_manager_current_sprite, mushroom_anim_show, 3);
	} else {
		SetSpriteAnim(sprite_manager_current_sprite, mushroom_anim_hide, 3);
	}
}

void Destroy_SPRITE_MUSHROOM() {
}