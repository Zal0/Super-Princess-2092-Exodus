#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_BULLET = 2;

#include "SpriteManager.h"

#include "ZGBMain.h"
#include "Scroll.h"

#include "Sound.h"

void Start_SPRITE_BULLET() {
	THIS->coll_x = 0u;
	THIS->coll_w = 4u;
	THIS->coll_y = 5u;
	THIS->coll_h = 4u;

	PlayFx(CHANNEL_1, 10, 0x2C, 0xD8, 0xF3, 0x62, 0xC7);
}

extern UINT8  scroll_collisions[128];
void Update_SPRITE_BULLET() {
	UINT8 i;
	struct Sprite* spr;
	struct Sprite* spr2;
	
	if(SPRITE_GET_VMIRROR(THIS)) {
		THIS->x -= 3 << delta_time;
	} else {
		THIS->x += 3 << delta_time;
	}

	if(scroll_collisions[GetScrollTile((THIS->x + 4)>> 3, (THIS->y + 4) >> 3)]) {
		SpriteManagerRemove(THIS_IDX);
		return;
	}

	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SPRITE_MUSHROOM || spr->type == SPRITE_CSHOOTER || spr->type == SPRITE_SHOOTER || spr->type == SPRITE_FLY || 
			 spr->type == SPRITE_ROLLER || spr->type == SPRITE_OVNI || spr->type == SPRITE_MISSILE) {
			if(CheckCollision(THIS, spr)) {
				if(spr->type != SPRITE_MUSHROOM || spr->anim_data[1 + spr->anim_frame] == 1u) { //Mushroom can only die on frame 1
					SpriteManagerRemove(i);
					PlayFx(CHANNEL_4, 20, 0x0d, 0xff, 0x7d, 0xc0);
				}
				spr2 = SpriteManagerAdd(SPRITE_EPARTICLE, spr->x, spr->y);
				SpriteManagerRemove(THIS_IDX);
				break;
			}
		}
	}
}

void Destroy_SPRITE_BULLET() {
}