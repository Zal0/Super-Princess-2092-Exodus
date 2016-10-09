#pragma bank=2
#include "SpriteBullet.h"
UINT8 bank_SPRITE_BULLET = 2;

#include "SpriteManager.h"

#include "GBJAM2016.h"
#include "Scroll.h"

extern UINT8 princess_idx;
const UINT8 bullet_anim_idle[] = {1, 6};

void Start_SPRITE_BULLET(struct Sprite* sprite) {
	InitSprite(sprite, FRAME_16x16, princess_idx >> 2);
	SetSpriteAnim(sprite, bullet_anim_idle, 3u);
}

extern UINT8  scroll_collisions[128];
void Update_SPRITE_BULLET() {
	UINT8 i;
	struct Sprite* spr;
	struct Sprite* spr2;
	
	if(sprite_manager_current_sprite->flags & OAM_VERTICAL_FLAG) {
		sprite_manager_current_sprite->x -= 3 << delta_time;
	} else {
		sprite_manager_current_sprite->x += 3 << delta_time;
	}

	if(scroll_collisions[GetScrollTile((sprite_manager_current_sprite->x + 8)>> 3, sprite_manager_current_sprite->y >> 3)]) {
		SpriteManagerRemove(sprite_manager_current_index);
		return;
	}

	for(i = 0u; i != sprite_manager_updatables[0]; ++i) {
		spr = sprite_manager_sprites[sprite_manager_updatables[i + 1u]];
		if(spr->type == SPRITE_MUSHROOM || spr->type == SPRITE_CSHOOTER || spr->type == SPRITE_SHOOTER) {
			if(CheckCollision(sprite_manager_current_sprite, spr)) {
				if(spr->type == SPRITE_MUSHROOM && spr->data[1 + spr->current_frame] != 1u) {
					//Mushroom can only die on frame 1
					SpriteManagerRemove(sprite_manager_current_index);
					break;
				} else {
					spr2 = SpriteManagerAdd(SPRITE_EPARTICLE);
					spr2->x = spr->x;
					spr2->y = spr->y;
				
					SpriteManagerRemove(i);
				}
			}
		}
	}
}

void Destroy_SPRITE_BULLET() {
}