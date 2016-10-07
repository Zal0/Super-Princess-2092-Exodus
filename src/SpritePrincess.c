#pragma bank=2
#include "SpritePrincess.h"
UINT8 bank_SPRITE_PRINCESS = 2;

#include "../res/src/sprite_test.h"
#include "SpriteManager.h"
#include "Scroll.h"
#include "Keys.h"

extern UINT8 princess_idx;
const UINT8 anim_princess_walk[] = {2, 0, 1};

void Start_SPRITE_PRINCESS(struct Sprite* sprite) {
	InitSprite(sprite, FRAME_16x16, princess_idx >> 2);
	SetSpriteAnim(sprite, anim_princess_walk, 20u);

	sprite->coll_x += 4;
	sprite->coll_w -= 8;
	sprite->lim_x = 160u;
	sprite->lim_y = 160u;
}

void Update_SPRITE_PRINCESS() {
	/*if(sprite_manager_current_sprite->flags & OAM_VERTICAL_FLAG) {
		//moving left
		if(TranslateSprite(sprite_manager_current_sprite, -1, 0)) {
			sprite_manager_current_sprite->flags = 0u;
		} else	if(!scroll_collisions[GetScrollTile(((sprite_manager_current_sprite->x + sprite_manager_current_sprite->coll_x) >> 3), (sprite_manager_current_sprite->y >> 3) + 2u)]) {
			sprite_manager_current_sprite->flags = 0u;
		}
	} else {
		//moving right
		if(TranslateSprite(sprite_manager_current_sprite, +1, 0)) {
			sprite_manager_current_sprite->flags |= OAM_VERTICAL_FLAG;
		} else if(!scroll_collisions[GetScrollTile(((sprite_manager_current_sprite->x + sprite_manager_current_sprite->coll_x + sprite_manager_current_sprite->coll_w) >> 3), (sprite_manager_current_sprite->y >> 3) + 2u)]) {
			sprite_manager_current_sprite->flags |= OAM_VERTICAL_FLAG;
		}
	}*/
	if(KEY_PRESSED(J_UP)) {
		TranslateSprite(sprite_manager_current_sprite, 0, -1);
	}
	if(KEY_PRESSED(J_DOWN)) {
		TranslateSprite(sprite_manager_current_sprite, 0,  1);
	}
	if(KEY_PRESSED(J_LEFT)) {
		TranslateSprite(sprite_manager_current_sprite, -1, 0);
	}
	if(KEY_PRESSED(J_RIGHT)) {
		TranslateSprite(sprite_manager_current_sprite, 1, 0);
	}
}