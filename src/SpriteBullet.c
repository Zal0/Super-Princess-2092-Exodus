#include "Banks/SetAutoBank.h"
#include "main.h"

#include "SpriteManager.h"

#include "ZGBMain.h"
#include "Scroll.h"

#include "Sound.h"

void Start_SpriteBullet() {
	PlayFx(CHANNEL_1, 10, 0x2C, 0xD8, 0xF3, 0x62, 0xC7);
}

extern UINT8  scroll_collisions[128];
void Update_SpriteBullet() {
	UINT8 i;
	struct Sprite* spr;
	struct Sprite* spr2;
	
	if(THIS->mirror ==  V_MIRROR) {
		THIS->x -= 3 << delta_time;
	} else {
		THIS->x += 3 << delta_time;
	}

	if(scroll_collisions[GetScrollTile((THIS->x + 4)>> 3, (THIS->y + 4) >> 3)]) {
		SpriteManagerRemove(THIS_IDX);
		return;
	}

	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SpriteMushroom || spr->type == SpriteCeilingShooter || spr->type == SpriteShooter || spr->type == SpriteFly || 
			 spr->type == SpriteRoller || spr->type == SpriteOvni || spr->type == SpriteMissile) {
			if(CheckCollision(THIS, spr)) {
				if(spr->type != SpriteMushroom || spr->anim_data[1 + spr->anim_frame] == 1u) { //Mushroom can only die on frame 1
					SpriteManagerRemove(i);
					PlayFx(CHANNEL_4, 20, 0x0d, 0xff, 0x7d, 0xc0);
				}
				spr2 = SpriteManagerAdd(SpriteEnemyParticle, spr->x, spr->y);
				SpriteManagerRemove(THIS_IDX);
				break;
			}
		}
	}
}

void Destroy_SpriteBullet() {
}