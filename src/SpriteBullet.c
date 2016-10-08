#pragma bank=2
#include "SpriteBullet.h"
UINT8 bank_SPRITE_BULLET = 2;

#include "SpriteManager.h"

extern UINT8 princess_idx;
const UINT8 bullet_anim_idle[] = {1, 6};

void Start_SPRITE_BULLET(struct Sprite* sprite) {
	InitSprite(sprite, FRAME_16x16, princess_idx >> 2);
	SetSpriteAnim(sprite, bullet_anim_idle, 3u);
}

void Update_SPRITE_BULLET() {
	if(sprite_manager_current_sprite->flags & OAM_VERTICAL_FLAG) {
		sprite_manager_current_sprite->x -= 3 << delta_time;
	} else {
		sprite_manager_current_sprite->x += 3 << delta_time;
	}
}