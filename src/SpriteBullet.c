#pragma bank=2
#include "SpriteBullet.h"
UINT8 bank_SPRITE_BULLET = 2;

#include "SpriteManager.h"

#include "GBJAM2016.h"
#include "Scroll.h"

void Start_SPRITE_BULLET() {
	THIS->current_frame = 0;

	THIS->coll_x = 0u;
	THIS->coll_w = 4u;
	THIS->coll_y = 5u;
	THIS->coll_h = 4u;
}

extern UINT8  scroll_collisions[128];
void Update_SPRITE_BULLET() {
	UINT8 i;
	struct Sprite* spr;
	struct Sprite* spr2;
	
	if(THIS->flags & OAM_VERTICAL_FLAG) {
		THIS->x -= 3 << delta_time;
	} else {
		THIS->x += 3 << delta_time;
	}

	if(scroll_collisions[GetScrollTile((THIS->x + 4)>> 3, (THIS->y + 4) >> 3)]) {
		SpriteManagerRemove(sprite_manager_current_index);
		return;
	}

	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SPRITE_MUSHROOM || spr->type == SPRITE_CSHOOTER || spr->type == SPRITE_SHOOTER || spr->type == SPRITE_FLY || 
			 spr->type == SPRITE_ROLLER || spr->type == SPRITE_OVNI || spr->type == SPRITE_MISSILE) {
			if(CheckCollision(THIS, spr)) {
				if(spr->type != SPRITE_MUSHROOM || spr->anim_data[1 + spr->current_frame] == 1u) { //Mushroom can only die on frame 1
					SpriteManagerRemove(i);
				}
				spr2 = SpriteManagerAdd(SPRITE_EPARTICLE, spr->x, spr->y);
				SpriteManagerRemove(sprite_manager_current_index);
				break;
			}
		}
	}
}

void Destroy_SPRITE_BULLET() {
}