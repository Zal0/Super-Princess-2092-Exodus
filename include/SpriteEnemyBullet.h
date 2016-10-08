#ifndef SPRITE_ENEMY_BULLET_H
#define SPRITE_ENEMY_BULLET_H

#include "main.h"

DECLARE_SPRITE(SPRITE_ENEMY_BULLET);

void EnemyBulletResetCustomData();
void CreateEnemyBullet(UINT16 x, UINT16 y, INT8 vx, INT8 vy);

#endif