#pragma bank=2
#include "SpriteMushroom.h"
UINT8 bank_SPRITE_MUSHROOM = 2;

#include "SpriteManager.h"
#include "../res/src/mushroom.h"
#include "SpriteEnemyBullet.h"

extern UINT8 mushroom_idx;
const UINT8 mushroom_anim_hide[] = {1, 0};
const UINT8 mushroom_anim_show[] = {1, 1};

#define NUM_CUSTOMS_DATA 5
struct MushroomCustomData {
	UINT8 time_out;
} mushroomCustomData[NUM_CUSTOMS_DATA];
DECLARE_STACK(mushroomCustomDataStack, NUM_CUSTOMS_DATA);

void MushroomResetCustomData() {
	UINT8 i;
	mushroomCustomDataStack[0] = 0;
	for(i = 0; i <NUM_CUSTOMS_DATA; ++i) {
		StackPush(mushroomCustomDataStack, i);
	}
}

void Start_SPRITE_MUSHROOM(struct Sprite* sprite) {
	struct MushroomCustomData* data;
	InitSprite(sprite, FRAME_16x16, mushroom_idx >> 2);
	SetSpriteAnim(sprite, mushroom_anim_hide, 3u);

	sprite->custom_data_idx = StackPop(mushroomCustomDataStack);
	data = &mushroomCustomData[sprite->custom_data_idx];
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
	struct MushroomCustomData* data = &mushroomCustomData[sprite_manager_current_sprite->custom_data_idx];
	UINT8 x;
	
	if(data->time_out > 50) {
		if(sprite_princess && (dist(sprite_princess->x, sprite_manager_current_sprite->x) < 40u)) {
			data->time_out = 0;
			x = ((sprite_princess->x - sprite_manager_current_sprite->x) & 0xF000) ? -2 : 2;

			CreateEnemyBullet(sprite_manager_current_sprite->x, sprite_manager_current_sprite->y, 0, -2);
			CreateEnemyBullet(sprite_manager_current_sprite->x, sprite_manager_current_sprite->y, x,  0);
			
			CreateEnemyBullet(sprite_manager_current_sprite->x, sprite_manager_current_sprite->y, x, -2);
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
	StackPush(mushroomCustomDataStack, sprite_manager_current_sprite->custom_data_idx);
}