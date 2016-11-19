#include "GBJAM2016.h"

#include "StateMenu.h"
#include "StateGame.h"
#include "StateLiveLost.h"
#include "StateGameOver.h"
#include "StateStageIntro.h"
#include "StateWin.h"

#include "SpritePrincess.h"
#include "SpriteBullet.h"
#include "SpriteMushroom.h"
#include "SpriteEnemyBullet.h"
#include "SpriteCeilingShooter.h"
#include "SpriteShooter.h"
#include "SpriteEnemyParticle.h"
#include "SpritePrincessParticle.h"
#include "SpritePlatform.h"
#include "SpriteFly.h"
#include "SpriteRoller.h"
#include "SpriteOvni.h"
#include "SpriteMissile.h"

#include "../res/src/princess.h"
#include "../res/src/princessBullet.h"
#include "../res/src/princessParticle.h"
#include "../res/src/mushroom.h"
#include "../res/src/enemybullet.h"
#include "../res/src/ceilingshooter.h"
#include "../res/src/wallshooter.h"
#include "../res/src/enemyexplosion.h"
#include "../res/src/mobileplatform.h"
#include "../res/src/flyingbug.h"
#include "../res/src/weirdroller.h"
#include "../res/src/ovni.h"
#include "../res/src/missile.h"

UINT8 next_state = STATE_MENU;

SET_N_STATES(N_STATES);
SET_N_SPRITE_TYPES(N_SPRITE_TYPES);

void InitStates() {
	INIT_STATE(STATE_MENU);
	INIT_STATE(STATE_GAME);
	INIT_STATE(STATE_LIVELOST);
	INIT_STATE(STATE_GAMEOVER);
	INIT_STATE(STATE_STAGEINTRO);
	INIT_STATE(STATE_WIN);
}                                         

void InitSprites() {
	INIT_SPRITE(SPRITE_PRINCESS,     spriteprincess,   3, FRAME_16x16, 10);
	INIT_SPRITE(SPRITE_BULLET,       princessBullet,   3,  FRAME_8x16,  1);
	INIT_SPRITE(SPRITE_PPARTICLE,    princessParticle, 3, FRAME_16x16,  2);
	INIT_SPRITE(SPRITE_MUSHROOM,     mushroom,         3, FRAME_16x16,  2);
	INIT_SPRITE(SPRITE_ENEMY_BULLET, enemyBullet,      3, FRAME_8x16,   1);
	INIT_SPRITE(SPRITE_CSHOOTER,     ceilingshooter,   3, FRAME_16x16,  2);
	INIT_SPRITE(SPRITE_SHOOTER,      wallshooter,      3, FRAME_16x16,  2); 
	INIT_SPRITE(SPRITE_EPARTICLE,    enemyexplosion,   3, FRAME_16x16,  4);
	INIT_SPRITE(SPRITE_PLATFORM,		 mobileplatform,   3, FRAME_16x16,  1);
	INIT_SPRITE(SPRITE_FLY,          flyingbug,        3, FRAME_16x16,  2);
	INIT_SPRITE(SPRITE_ROLLER,       weirdroller,      3, FRAME_16x16,  4);
	INIT_SPRITE(SPRITE_OVNI,         ovni,             3, FRAME_16x16,  1);
	INIT_SPRITE(SPRITE_MISSILE,      missile,          3, FRAME_16x16,  1);
}

UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {
	if(current_state == STATE_GAME) {
		*tile = 0;
		switch(*tile_ptr) {
			case 1:
			case 2:
				if(*(tile_ptr + 1) == 24) 
					*tile = 23;
				return 255u;

			case 3: return SPRITE_MUSHROOM;
			case 4: return SPRITE_PLATFORM;
			case 5: return SPRITE_OVNI;
			case 6: return SPRITE_SHOOTER;
			case 7: return SPRITE_CSHOOTER;
			case 8: return SPRITE_FLY;
			case 9: return SPRITE_ROLLER;
		}
		*tile = *tile_ptr;
	}

	return 255u;
}