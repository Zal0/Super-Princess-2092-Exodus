#pragma bank=2
#include "SpriteEnemyBullet.h"
UINT8 bank_SPRITE_ENEMY_BULLET = 2;

#include "SpriteManager.h"
#include "../res/src/enemybullet16x16.h"
#include "GBJAM2016.h"

extern UINT8 enemy_bullet_idx;
const UINT8 enemybullet_anim_idle[] = {1, 0};

#define NUM_ENEMY_BULLET_CUSTOM_DATA 10
struct EnemyBulletCustomData {
	INT8 vx;
	INT8 vy;
} EnemyBulletCustomData[NUM_ENEMY_BULLET_CUSTOM_DATA];
DECLARE_STACK(EnemyBulletCustomDataStack, NUM_ENEMY_BULLET_CUSTOM_DATA);

void CreateEnemyBullet(UINT16 x, UINT16 y, INT8 vx, INT8 vy){
	struct EnemyBulletCustomData* data;
	struct Sprite* spr = SpriteManagerAdd(SPRITE_ENEMY_BULLET);
	spr->x = x;
	spr->y = y;

	data = &EnemyBulletCustomData[spr->custom_data_idx];
	data->vx = vx;
	data->vy = vy;
}

void EnemyBulletResetCustomData() {
	UINT8 i;
	EnemyBulletCustomDataStack[0] = 0;
	for(i = 0; i < NUM_ENEMY_BULLET_CUSTOM_DATA; ++i) {
		StackPush(EnemyBulletCustomDataStack, i);
	}
}

void Start_SPRITE_ENEMY_BULLET(struct Sprite* sprite) {
	InitSprite(sprite, FRAME_16x16, enemy_bullet_idx >> 2);
	SetSpriteAnim(sprite, enemybullet_anim_idle, 3u);

	sprite->custom_data_idx = StackPop(EnemyBulletCustomDataStack);
}

void Update_SPRITE_ENEMY_BULLET() {
	struct EnemyBulletCustomData* data = &EnemyBulletCustomData[sprite_manager_current_sprite->custom_data_idx];
	
	sprite_manager_current_sprite->x += (INT16)data->vx << delta_time;
	sprite_manager_current_sprite->y += (INT16)data->vy << delta_time;
}

void Destroy_SPRITE_ENEMY_BULLET() {
	StackPush(EnemyBulletCustomDataStack, sprite_manager_current_sprite->custom_data_idx);
}
