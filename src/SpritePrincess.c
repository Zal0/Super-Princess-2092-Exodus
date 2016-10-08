#pragma bank=2
#include "SpritePrincess.h"
UINT8 bank_SPRITE_PRINCESS = 2;

#include "gb/gb.h"

#include "GBJAM2016.h"
#include "Sprite.h"
#include "Keys.h"
#include "Scroll.h"
#include "SpriteManager.h"

#include "../res/src/princess.h"

//#define DEBUG_CONTROLS

//Princes anims
const UINT8 anim_walk[]       = {4, 3, 4, 5, 4};
const UINT8 anim_idle[]       = {2, 1, 2};
const UINT8 anim_idle_shoot[] = {1, 0};
const UINT8 anim_jump[]       = {1, 3};
const UINT8 anim_ladder_idle_cooldown[]   = {1, 9};
const UINT8 anim_ladder_moving_cooldown[] = {2, 9, 10};
const UINT8 anim_ladder_idle[]   = {1, 7};
const UINT8 anim_ladder_moving[] = {2, 7, 8};

typedef enum  {
	PRINCESS_STATE_NORMAL,
	PRINCESS_STATE_JUMPING,
	PRINCESS_STATE_LADDER
}PRINCESS_STATE;
PRINCESS_STATE princes_state;
INT16 princess_accel_y;

extern UINT8 princess_idx;
//extern struct Sprite* game_over_particle;

INT8 shoot_cooldown = 0;

void Start_SPRITE_PRINCESS(struct Sprite* sprite) {
	InitSprite(sprite, FRAME_16x16, princess_idx >> 2);
	SetSpriteAnim(sprite, anim_idle, 3u);
	sprite->coll_x += 4u;
	sprite->coll_w -= 7u;
	sprite->coll_y += 2u;
	sprite->coll_h -= 2u;

	princess_accel_y = 0;

	scroll_target = sprite;

	princes_state = PRINCESS_STATE_NORMAL;
}

void Die(struct Sprite* sprite, UINT8 idx) {
	SpriteManagerRemove(idx);
	//game_over_particle = SpriteManagerAdd(SPRITE_DEAD_PARTICLE);
	//game_over_particle->x = sprite->x;
	//game_over_particle->y = sprite->y;

	scroll_target = 0;
}

UINT8 tile_collision;
void CheckCollisionTile(struct Sprite* sprite, UINT8 idx) {
	switch(tile_collision) {
		case 14u:
		case 15u:
			Die(sprite, idx);
			break;
	}
}

void MovePrincess(struct Sprite* sprite, UINT8 idx) {
	if(KEY_PRESSED(J_RIGHT)) {
		tile_collision = TranslateSprite(sprite, 1 << delta_time, 0);
		sprite->flags = 0u;
		CheckCollisionTile(sprite, idx);
	} else if(KEY_PRESSED(J_LEFT)) {
		tile_collision = TranslateSprite(sprite, -1 << delta_time, 0);
		sprite->flags = OAM_VERTICAL_FLAG;
		CheckCollisionTile(sprite, idx);
	}

	if(KEY_PRESSED(J_UP)) {
		UINT8 tile = GetScrollTile((sprite->x + sprite->coll_x) >> 3, (sprite ->y + 15u) >> 3);
		if(tile == 23u )
		{
			sprite->x = ((sprite->x + sprite->coll_x)>> 3) << 3;
			princess_accel_y = 0;
			princes_state = PRINCESS_STATE_LADDER;
		}
	}
	if(KEY_PRESSED(J_DOWN)) {
		UINT8 tile = GetScrollTile((sprite->x + sprite->coll_x) >> 3, (sprite ->y + 16u) >> 3);
		if(tile == 23u )
		{
			sprite->x = ((sprite->x + sprite->coll_x)>> 3) << 3;
			princess_accel_y = 0;
			princes_state = PRINCESS_STATE_LADDER;
		}
	}
	
#ifdef DEBUG_CONTROLS
	if(KEY_PRESSED(J_UP)) {
		tile_collision = TranslateSprite(sprite, 0, -1 << delta_time);
		CheckCollisionTile(sprite, idx);
	} else if(KEY_PRESSED(J_DOWN)) {
		tile_collision = TranslateSprite(sprite, 0, 1 << delta_time);
		CheckCollisionTile(sprite, idx);
	}
#endif
}

void Shoot(struct Sprite* sprite) {
	struct Sprite* bullet_sprite = SpriteManagerAdd(SPRITE_BULLET);

	bullet_sprite->flags = sprite->flags;
	if(sprite->flags & OAM_VERTICAL_FLAG) 
		bullet_sprite->x = sprite->x - 8u;
	else
		bullet_sprite->x = sprite->x + 8u; 
	bullet_sprite->y = sprite->y + 1u;
	shoot_cooldown = 10;
}

void Update_SPRITE_PRINCESS() {
	UINT8 i;
	struct Sprite* spr;

	switch(princes_state) {
		case PRINCESS_STATE_NORMAL:
			MovePrincess(sprite_manager_current_sprite, sprite_manager_current_index);
	
			//Choose idle anim or walk
			if(KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT) ) {
				SetSpriteAnim(sprite_manager_current_sprite, anim_walk, 33u);
			} else {
				if(shoot_cooldown) {
					SetSpriteAnim(sprite_manager_current_sprite, anim_idle_shoot, 3u);
				} else {
					SetSpriteAnim(sprite_manager_current_sprite, anim_idle, 3u);
				}
			}

			//Check jumping
			if(KEY_TICKED(J_A)) {
				princess_accel_y = -50;
				princes_state = PRINCESS_STATE_JUMPING;
			} 

			//Check falling
			if((princess_accel_y >> 4) > 1) {
				princes_state = PRINCESS_STATE_JUMPING;
			}
			break;

		case PRINCESS_STATE_LADDER:
			if(KEY_PRESSED(J_UP)) {
				SetSpriteAnim(sprite_manager_current_sprite, shoot_cooldown ? anim_ladder_moving_cooldown : anim_ladder_moving, 12u);
				sprite_manager_current_sprite->y -= 1 << delta_time;
			} else if(KEY_PRESSED(J_DOWN)) {
				SetSpriteAnim(sprite_manager_current_sprite, shoot_cooldown ? anim_ladder_moving_cooldown : anim_ladder_moving, 12u);
				sprite_manager_current_sprite->y += 1 << delta_time;
			} else {
				SetSpriteAnim(sprite_manager_current_sprite, shoot_cooldown ? anim_ladder_idle_cooldown : anim_ladder_idle, 12u);
			}
			if(KEY_PRESSED(J_RIGHT)) {
				sprite_manager_current_sprite->flags = 0u;
			} else if(KEY_PRESSED(J_LEFT)) {
				sprite_manager_current_sprite->flags = OAM_VERTICAL_FLAG;
			}

			//Check the end of the ladder
			i = GetScrollTile((sprite_manager_current_sprite->x + sprite_manager_current_sprite->coll_x) >> 3, (sprite_manager_current_sprite->y + 16u) >> 3);
			if(i != 23u )
			{
				TranslateSprite(sprite_manager_current_sprite, 0, 1 << delta_time);
				princes_state = PRINCESS_STATE_NORMAL;
			}

			//Check jumping
			if(KEY_TICKED(J_A)) {
				princess_accel_y = -50;
				princes_state = PRINCESS_STATE_JUMPING;
			}
			break;

		case PRINCESS_STATE_JUMPING:
			SetSpriteAnim(sprite_manager_current_sprite, anim_jump, 33u);
			MovePrincess(sprite_manager_current_sprite, sprite_manager_current_index);
			break;
	}

#ifndef DEBUG_CONTROLS
	if(princes_state != PRINCESS_STATE_LADDER) {
		//Simple gravity physics 
		if(princess_accel_y < 40) {
			princess_accel_y += 2 << delta_time;
		}
		if(tile_collision = TranslateSprite(sprite_manager_current_sprite, 0, (princess_accel_y >> 4) << delta_time)) {
			princess_accel_y = 0;
			if(princes_state == PRINCESS_STATE_JUMPING) {
				princes_state = PRINCESS_STATE_NORMAL;
			}

			CheckCollisionTile(sprite_manager_current_sprite, sprite_manager_current_index);
		}
	}
#endif

	//Check enemy collision
	/*for(i = 0u; i != sprite_manager_updatables[0]; ++i) {
		spr = sprite_manager_sprites[sprite_manager_updatables[i + 1u]];
		if(spr->type == SPRITE_ZURRAPA || spr->type == SPRITE_AZNAR) {
			if(CheckCollision(sprite_manager_current_sprite, spr)) {
				Die(sprite_manager_current_sprite, sprite_manager_current_index);
			}
		} else if(spr->type == SPRITE_FLAG) {
			if(CheckCollision(sprite_manager_current_sprite, spr)) {
				reset_x = spr->x;
				reset_y = spr->y;
			}
		}
	}*/

	if(shoot_cooldown) {
		shoot_cooldown -= 1u;
	} else {
		if(KEY_TICKED(J_B)) {
			Shoot(sprite_manager_current_sprite);
		}
	}
}

void Destroy_SPRITE_PRINCESS() {

}


