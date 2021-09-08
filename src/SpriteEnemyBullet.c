#include "Banks/SetAutoBank.h"
#include "main.h"

#include "SpriteManager.h"
#include "ZGBMain.h"
#include "Sound.h"

struct EnemyBulletCustomData {
	INT8 vx;
	INT8 vy;
};

void CreateEnemyBullet(UINT16 x, UINT16 y, INT8 vx, INT8 vy) BANKED {
	struct Sprite* spr = SpriteManagerAdd(SpriteEnemyBullet, x, y);
	struct EnemyBulletCustomData* data = (struct EnemyBulletCustomData*)spr->custom_data;

	data->vx = vx;
	data->vy = vy;

	PlayFx(CHANNEL_1, 10, 0x2C, 0xD8, 0xF3, 0x62, 0xC7);
}

void Start_SpriteEnemyBullet() {
}

void Update_SpriteEnemyBullet() {
	struct EnemyBulletCustomData* data = (struct EnemyBulletCustomData*)THIS->custom_data;
	
	THIS->x += (INT16)data->vx << delta_time;
	THIS->y += (INT16)data->vy << delta_time;
}

void Destroy_SpriteEnemyBullet() {
}
