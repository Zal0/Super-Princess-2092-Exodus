#pragma bank=2
#include "SpriteEnemyBullet.h"
UINT8 bank_SPRITE_ENEMY_BULLET = 2;

#include "../res/src/enemybullet16x16.h"
#include "SpriteManager.h"
#include "GBJAM2016.h"

struct EnemyBulletCustomData {
	INT8 vx;
	INT8 vy;
};

void CreateEnemyBullet(UINT16 x, UINT16 y, INT8 vx, INT8 vy){
	struct Sprite* spr = SpriteManagerAdd(SPRITE_ENEMY_BULLET);
	struct EnemyBulletCustomData* data = (struct EnemyBulletCustomData*)spr->custom_data;
	spr->x = x;
	spr->y = y;

	spr->coll_x = 5u;
	spr->coll_w = 4u;
	spr->coll_y = 5u;
	spr->coll_h = 4u;

	data->vx = vx;
	data->vy = vy;
}

void Start_SPRITE_ENEMY_BULLET(struct Sprite* sprite) {
}

void Update_SPRITE_ENEMY_BULLET() {
	struct EnemyBulletCustomData* data = (struct EnemyBulletCustomData*)sprite_manager_current_sprite->custom_data;
	
	sprite_manager_current_sprite->x += (INT16)data->vx << delta_time;
	sprite_manager_current_sprite->y += (INT16)data->vy << delta_time;
}

void Destroy_SPRITE_ENEMY_BULLET() {
}
