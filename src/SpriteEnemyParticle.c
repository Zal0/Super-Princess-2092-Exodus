#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_EPARTICLE = 2;

#include "../res/src/enemyexplosion.h"
#include "SpriteManager.h"

const UINT8 eparticle_anim[] = {5, 0, 1, 2, 3, 3};

void Start_SPRITE_EPARTICLE() {
	SetSpriteAnim(THIS, eparticle_anim, 33);
}

void Update_SPRITE_EPARTICLE() {
	if(THIS->current_frame == 4) {
		SpriteManagerRemove(THIS_IDX);
	}
}

void Destroy_SPRITE_EPARTICLE () {
}