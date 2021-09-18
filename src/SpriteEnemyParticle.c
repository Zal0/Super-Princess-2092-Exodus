#include "Banks/SetAutoBank.h"
#include "main.h"

#include "SpriteManager.h"

const UINT8 eparticle_anim[] = {5, 0, 1, 2, 3, 3};

void START() {
	SetSpriteAnim(THIS, eparticle_anim, 33);
}

void UPDATE() {
	if(THIS->anim_frame == 4) {
		SpriteManagerRemove(THIS_IDX);
	}
}

void DESTROY () {
}