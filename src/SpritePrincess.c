#pragma bank 2
#include "main.h"
UINT8 bank_SPRITE_PRINCESS = 2;

#include "gb/gb.h"

#include "ZGBMain.h"
#include "Sprite.h"
#include "Keys.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Math.h"
#include "Sound.h"
#include "gbt_player.h"

#include "../res/src/princess.h"

void CreatePParticle(UINT16 x, UINT16 y, INT8 vx, INT8 vy);

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
const UINT8 anim_hit[] = {6, 1, 6, 1, 6, 1, 6};

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

UINT8 bg_hidden = 0;

void Start_SPRITE_PRINCESS() {
	SetSpriteAnim(THIS, anim_idle, 3u);
	THIS->coll_x += 4u;
	THIS->coll_w -= 7u;
	THIS->coll_y += 2u;
	THIS->coll_h -= 2u;

	princess_accel_y = 0;

	scroll_target = THIS;
	sprite_princess = THIS;

	bg_hidden = 0;

	if(GetScrollTile((THIS->x + THIS->coll_x) >> 3, (THIS->y + THIS->coll_y) >> 3) == 23u) {
		princes_state = PRINCESS_STATE_LADDER;
	} else {
		princes_state = PRINCESS_STATE_NORMAL;
	}
}

void Hit() {
	princes_state = PRINCESS_STATE_HIT;
	gbt_stop();

	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume
	PlayFx(CHANNEL_1, 10, 0x5b, 0x7f, 0xf7, 0x15, 0x86);
}

UINT8 tile_collision;
extern INT8 load_next;

extern UINT8 stage_completion;
extern UINT8 current_stage;
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
			Hit();
			break;

		case 27u:
		case 28u:
			SET_BIT(stage_completion, current_stage);
			SetState(STATE_STAGE_SELECT);
			break;
	}
}

void MovePrincess() {
	if(KEY_PRESSED(J_RIGHT)) {
		tile_collision = TranslateSprite(THIS, 1 << delta_time, 0);
		SPRITE_UNSET_VMIRROR(THIS);
		CheckCollisionTile();
	} else if(KEY_PRESSED(J_LEFT)) {
		tile_collision = TranslateSprite(THIS, -1 << delta_time, 0);
		SPRITE_SET_VMIRROR(THIS);
		CheckCollisionTile();
	}

#ifndef DEBUG_CONTROLS
	if(KEY_PRESSED(J_UP)) {
		UINT8 tile = GetScrollTile((THIS->x + THIS->coll_x) >> 3, (THIS ->y + 15u) >> 3);
		if(tile == 23u )
		{
			THIS->x = ((THIS->x + THIS->coll_x)>> 3) << 3;
			princess_accel_y = 0;
			princes_state = PRINCESS_STATE_LADDER;
		}
	}
	if(KEY_PRESSED(J_DOWN)) {
		UINT8 tile = GetScrollTile((THIS->x + THIS->coll_x) >> 3, (THIS ->y + 16u) >> 3);
		if(tile == 23u )
		{
			THIS->x = ((THIS->x + THIS->coll_x)>> 3) << 3;
			THIS->y = THIS->y + 1u;
			princess_accel_y = 0;
			princes_state = PRINCESS_STATE_LADDER;
		}
	}
#endif
#ifdef DEBUG_CONTROLS
	if(KEY_PRESSED(J_UP)) {
		tile_collision = TranslateSprite(THIS, 0, -1 << delta_time);
		CheckCollisionTile();
	} else if(KEY_PRESSED(J_DOWN)) {
		tile_collision = TranslateSprite(THIS, 0, 1 << delta_time);
		CheckCollisionTile();
	}
#endif
}

void Shoot() {
	struct Sprite* bullet_sprite = SpriteManagerAdd(SPRITE_BULLET, 0, 0);

	bullet_sprite->flags = THIS->flags;
	if(SPRITE_GET_VMIRROR(THIS)) 
		bullet_sprite->x = THIS->x - 5u;
	else
		bullet_sprite->x = THIS->x + 5u; 
	bullet_sprite->y = THIS->y + 1u;
	shoot_cooldown = 10;
}

void Jump() {
	if(princes_state != PRINCESS_STATE_JUMPING) {
		princess_accel_y = -50;
		princes_state = PRINCESS_STATE_JUMPING;
		princess_parent = 0;

		PlayFx(CHANNEL_1, 5, 0x17, 0x9f, 0xf3, 0xc9, 0xc4);
	}
}

void Update_SPRITE_PRINCESS() {
	UINT8 i;
	struct Sprite* spr;

	princess_old_x = THIS->x;
	princess_old_y = THIS->y;

	switch(princes_state) {
		case PRINCESS_STATE_NORMAL:
			MovePrincess();
	
			//Choose idle anim or walk
			if(KEY_PRESSED(J_RIGHT) || KEY_PRESSED(J_LEFT) ) {
				SetSpriteAnim(THIS, anim_walk, 33u);
			} else {
				if(shoot_cooldown) {
					SetSpriteAnim(THIS, anim_idle_shoot, 3u);
				} else {
					SetSpriteAnim(THIS, anim_idle, 3u);
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
				SetSpriteAnim(THIS, shoot_cooldown ? anim_ladder_moving_cooldown : anim_ladder_moving, 12u);
				tile_collision = TranslateSprite(THIS, 0, -1 << delta_time);
				CheckCollisionTile();
				i = GetScrollTile((THIS->x + THIS->coll_x) >> 3, (THIS->y + 15u) >> 3);
			} else if(KEY_PRESSED(J_DOWN)) {
				SetSpriteAnim(THIS, shoot_cooldown ? anim_ladder_moving_cooldown : anim_ladder_moving, 12u);
				tile_collision = TranslateSprite(THIS, 0, 1 << delta_time);
				CheckCollisionTile();
				i = GetScrollTile((THIS->x + THIS->coll_x) >> 3, (THIS->y + 16u) >> 3);
			} else {
				SetSpriteAnim(THIS, shoot_cooldown ? anim_ladder_idle_cooldown : anim_ladder_idle, 12u);
			}
			if(KEY_PRESSED(J_RIGHT)) {
				SPRITE_UNSET_VMIRROR(THIS);
			} else if(KEY_PRESSED(J_LEFT)) {
				SPRITE_SET_VMIRROR(THIS);
			}

			//Check the end of the ladder
			if(i != 23u && i != 1u && i != 2u)
			{
				//TranslateSprite(THIS, 0, 1 << delta_time);
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

			SetSpriteAnim(THIS, anim_jump, 33u);
			MovePrincess();
			break;

		case PRINCESS_STATE_HIT:
			SetSpriteAnim(THIS, anim_hit, 15u);
			if((THIS->current_frame + 1) % 2){
				if(!bg_hidden) {
					HIDE_BKG;
					bg_hidden = 1;
				}
			} else {
				if(bg_hidden) {
					SHOW_BKG;
					bg_hidden = 0;
					PlayFx(CHANNEL_1, 10, 0x5b, 0x7f, 0xf7, 0x15, 0x86);
				}
			}

			if(THIS->current_frame == 5) {
				SpriteManagerRemove(THIS_IDX);
				scroll_target = 0;

				CreatePParticle(THIS->x, THIS->y,  1,  1);
				CreatePParticle(THIS->x, THIS->y,  1, -1);
				CreatePParticle(THIS->x, THIS->y, -1,  1);
				CreatePParticle(THIS->x, THIS->y, -1, -1);
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
		tile_collision = TranslateSprite(THIS, 0, (princess_accel_y >> 4));
		if(!tile_collision && delta_time != 0 && princess_accel_y < 40) { //Do another iteration if there is no collision
			princess_accel_y += 2;
			tile_collision = TranslateSprite(THIS, 0, (princess_accel_y >> 4));
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

	if(princes_state != PRINCESS_STATE_HIT) {
		//Check enemy collision
		SPRITEMANAGER_ITERATE(i, spr) {
			if(spr->type == SPRITE_MUSHROOM || spr->type == SPRITE_ENEMY_BULLET || spr->type == SPRITE_CSHOOTER || spr->type == SPRITE_SHOOTER ||
				 spr->type == SPRITE_FLY || spr->type == SPRITE_ROLLER || spr->type == SPRITE_OVNI || spr->type == SPRITE_MISSILE) {
				if(CheckCollision(THIS, spr)) {
					Hit();
				}
			}
		}


		if(shoot_cooldown) {
			shoot_cooldown -= 1u;
		} else {
			if(KEY_TICKED(J_B)) {
				Shoot();
			}
		}
	}
}

void Destroy_SPRITE_PRINCESS() {
	sprite_princess = 0;
}


