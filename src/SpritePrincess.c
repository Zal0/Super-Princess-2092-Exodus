#pragma bank=2
#include "SpritePrincess.h"
UINT8 bank_SPRITE_PRINCESS = 2;

#include "gb/gb.h"

#include "GBJAM2016.h"
#include "Sprite.h"
#include "Keys.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "SpritePrincessParticle.h"
#include "Math.h"

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
const UINT8 anim_hit[] = {6, 1, 11, 1, 11, 1, 11};

typedef enum  {
	PRINCESS_STATE_NORMAL,
	PRINCESS_STATE_JUMPING,
	PRINCESS_STATE_LADDER,
	PRINCESS_STATE_HIT
}PRINCESS_STATE;
PRINCESS_STATE princes_state;
INT16 princess_accel_y;

extern UINT8 current_level;

INT8 shoot_cooldown = 0;

struct Sprite* sprite_princess = 0;

struct Sprite* princess_parent = 0;
UINT16 princess_old_x, princess_old_y;

void Start_SPRITE_PRINCESS(struct Sprite* sprite) {
	SetSpriteAnim(sprite, anim_idle, 3u);
	sprite->coll_x += 4u;
	sprite->coll_w -= 7u;
	sprite->coll_y += 2u;
	sprite->coll_h -= 2u;

	princess_accel_y = 0;

	scroll_target = sprite;

	sprite_princess = sprite;

	princes_state = PRINCESS_STATE_NORMAL;
}

UINT8 tile_collision;
extern INT8 load_next;
void CheckCollisionTile() {
	switch(tile_collision) {
		case 1u:
			load_next = 1;
			break;

		case 2u:
			load_next = -1;
			break;

		case 33u:
		case 35u:
			princes_state = PRINCESS_STATE_HIT;
			break;

		case 27u:
		case 28u:
			SetState(STATE_WIN);
			break;
	}
}

void MovePrincess(struct Sprite* sprite) {
	if(KEY_PRESSED(J_RIGHT)) {
		tile_collision = TranslateSprite(sprite, 1 << delta_time, 0);
		sprite->flags = 0u;
		CheckCollisionTile();
	} else if(KEY_PRESSED(J_LEFT)) {
		tile_collision = TranslateSprite(sprite, -1 << delta_time, 0);
		sprite->flags = OAM_VERTICAL_FLAG;
		CheckCollisionTile();
	}

#ifndef DEBUG_CONTROLS
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
			sprite->y = sprite->y + 1u;
			princess_accel_y = 0;
			princes_state = PRINCESS_STATE_LADDER;
		}
	}
#endif
#ifdef DEBUG_CONTROLS
	if(KEY_PRESSED(J_UP)) {
		tile_collision = TranslateSprite(sprite, 0, -1 << delta_time);
		CheckCollisionTile();
	} else if(KEY_PRESSED(J_DOWN)) {
		tile_collision = TranslateSprite(sprite, 0, 1 << delta_time);
		CheckCollisionTile();
	}
#endif
}

void Shoot(struct Sprite* sprite) {
	struct Sprite* bullet_sprite = SpriteManagerAdd(SPRITE_BULLET, 0, 0);

	bullet_sprite->flags = sprite->flags;
	if(sprite->flags & OAM_VERTICAL_FLAG) 
		bullet_sprite->x = sprite->x - 8u;
	else
		bullet_sprite->x = sprite->x + 8u; 
	bullet_sprite->y = sprite->y + 1u;
	shoot_cooldown = 10;
}

void Jump() {
	if(princes_state != PRINCESS_STATE_JUMPING) {
		princess_accel_y = -50;
		princes_state = PRINCESS_STATE_JUMPING;
		princess_parent = 0;
	}
}

void Update_SPRITE_PRINCESS() {
	UINT8 i;
	struct Sprite* spr;

	princess_old_x = sprite_manager_current_sprite->x;
	princess_old_y = sprite_manager_current_sprite->y;

	switch(princes_state) {
		case PRINCESS_STATE_NORMAL:
			MovePrincess(sprite_manager_current_sprite);
	
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
				Jump();
			} 

			//Check falling
			if((princess_accel_y >> 4) > 1) {
				princes_state = PRINCESS_STATE_JUMPING;
			}
			break;

		case PRINCESS_STATE_LADDER:
			i = 23;
			if(KEY_PRESSED(J_UP)) {
				SetSpriteAnim(sprite_manager_current_sprite, shoot_cooldown ? anim_ladder_moving_cooldown : anim_ladder_moving, 12u);
				tile_collision = TranslateSprite(sprite_manager_current_sprite, 0, -1 << delta_time);
				CheckCollisionTile();
				i = GetScrollTile((sprite_manager_current_sprite->x + sprite_manager_current_sprite->coll_x) >> 3, (sprite_manager_current_sprite->y + 15u) >> 3);
			} else if(KEY_PRESSED(J_DOWN)) {
				SetSpriteAnim(sprite_manager_current_sprite, shoot_cooldown ? anim_ladder_moving_cooldown : anim_ladder_moving, 12u);
				tile_collision = TranslateSprite(sprite_manager_current_sprite, 0, 1 << delta_time);
				CheckCollisionTile();
				i = GetScrollTile((sprite_manager_current_sprite->x + sprite_manager_current_sprite->coll_x) >> 3, (sprite_manager_current_sprite->y + 16u) >> 3);
			} else {
				SetSpriteAnim(sprite_manager_current_sprite, shoot_cooldown ? anim_ladder_idle_cooldown : anim_ladder_idle, 12u);
			}
			if(KEY_PRESSED(J_RIGHT)) {
				sprite_manager_current_sprite->flags = 0u;
			} else if(KEY_PRESSED(J_LEFT)) {
				sprite_manager_current_sprite->flags = OAM_VERTICAL_FLAG;
			}

			//Check the end of the ladder
			if(i != 23u && i != 1u && i != 2u)
			{
				//TranslateSprite(sprite_manager_current_sprite, 0, 1 << delta_time);
				princes_state = PRINCESS_STATE_NORMAL;
			}

			//Check jumping
			if(KEY_TICKED(J_A)) {
				Jump();
			}
			break;

		case PRINCESS_STATE_JUMPING:
			if((princess_accel_y < 0) && !KEY_PRESSED(J_A)) {
				princess_accel_y = 0;
			}

			SetSpriteAnim(sprite_manager_current_sprite, anim_jump, 33u);
			MovePrincess(sprite_manager_current_sprite);
			break;

		case PRINCESS_STATE_HIT:
			SetSpriteAnim(sprite_manager_current_sprite, anim_hit, 15u);
			if((sprite_manager_current_sprite->current_frame + 1) % 2)
				HIDE_BKG;
			else
				SHOW_BKG;

			if(sprite_manager_current_sprite->current_frame == 5) {
				SpriteManagerRemove(sprite_manager_current_index);
				scroll_target = 0;

				CreatePParticle(sprite_manager_current_sprite->x, sprite_manager_current_sprite->y,  1,  1);
				CreatePParticle(sprite_manager_current_sprite->x, sprite_manager_current_sprite->y,  1, -1);
				CreatePParticle(sprite_manager_current_sprite->x, sprite_manager_current_sprite->y, -1,  1);
				CreatePParticle(sprite_manager_current_sprite->x, sprite_manager_current_sprite->y, -1, -1);
				SHOW_BKG;
			}
			break;
	}

#ifndef DEBUG_CONTROLS
	if(princess_parent == 0 && princes_state != PRINCESS_STATE_LADDER && princes_state != PRINCESS_STATE_HIT) {
		//Simple gravity physics 
		if(princess_accel_y < 60) {
			princess_accel_y += 2;
		}
		tile_collision = TranslateSprite(sprite_manager_current_sprite, 0, (princess_accel_y >> 4));
		if(!tile_collision && delta_time != 0 && princess_accel_y < 40) { //Do another iteration if there is no collision
			princess_accel_y += 2;
			tile_collision = TranslateSprite(sprite_manager_current_sprite, 0, (princess_accel_y >> 4));
		}
		if(tile_collision) {
			if(tile_collision != 1u && tile_collision != 2u) {
				princess_accel_y = 0;
				if(princes_state == PRINCESS_STATE_JUMPING) {
					princes_state = PRINCESS_STATE_NORMAL;
				}
			}

			CheckCollisionTile();
		}
	}
	if(princess_parent && princes_state == PRINCESS_STATE_JUMPING) {
		princess_accel_y = 0;
		princes_state = PRINCESS_STATE_NORMAL;
	}
#endif

	//Check enemy collision
	for(i = 0u; i != sprite_manager_updatables[0]; ++i) {
		spr = sprite_manager_sprites[sprite_manager_updatables[i + 1u]];
		if(spr->type == SPRITE_MUSHROOM || spr->type == SPRITE_ENEMY_BULLET || spr->type == SPRITE_CSHOOTER || spr->type == SPRITE_SHOOTER) {
			if(CheckCollision(sprite_manager_current_sprite, spr)) {
				princes_state = PRINCESS_STATE_HIT;
			}
		}
	}

	if(princes_state != PRINCESS_STATE_HIT) {
		if(shoot_cooldown) {
			shoot_cooldown -= 1u;
		} else {
			if(KEY_TICKED(J_B)) {
				Shoot(sprite_manager_current_sprite);
			}
		}
	}
}

void Destroy_SPRITE_PRINCESS() {
	sprite_princess = 0;
}


