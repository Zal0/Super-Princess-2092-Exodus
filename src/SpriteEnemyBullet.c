#pragma bank=2
#include "SpriteEnemyBullet.h"
UINT8 bank_SPRITE_ENEMY_BULLET = 2;

#include "../res/src/enemybullet.h"
#include "SpriteManager.h"
#include "GBJAM2016.h"

struct EnemyBulletCustomData {
	INT8 vx;
	INT8 vy;
};

void CreateEnemyBullet(UINT16 x, UINT16 y, INT8 vx, INT8 vy){
	struct Sprite* spr = SpriteManagerAdd(SPRITE_ENEMY_BULLET, x, y);
	struct EnemyBulletCustomData* data = (struct EnemyBulletCustomData*)spr->custom_data;

	data->vx = vx;
	data->vy = vy;
}

void Start_SPRITE_ENEMY_BULLET(struct Sprite* sprite) {
	sprite->coll_x = 2u;
	sprite->coll_w = 4u;
	sprite->coll_y = 6u;
	sprite->coll_h = 4u;
}

void Update_SPRITE_ENEMY_BULLET() {
	struct EnemyBulletCustomData* data = (struct EnemyBulletCustomData*)THIS->custom_data;
	
	THIS->x += (INT16)data->vx << delta_time;
	THIS->y += (INT16)data->vy << delta_time;
}

void Destroy_SPRITE_ENEMY_BULLET() {
}
