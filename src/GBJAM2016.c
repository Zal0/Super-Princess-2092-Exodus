#include "GBJAM2016.h"

#include "StateMenu.h"
#include "StateGame.h"
#include "StateLiveLost.h"
#include "StateGameOver.h"

#include "SpritePrincess.h"
#include "SpriteBullet.h"
#include "SpriteMushroom.h"
#include "SpriteEnemyBullet.h"
#include "SpriteCeilingShooter.h"
#include "SpriteShooter.h"
#include "SpriteEnemyParticle.h"
#include "SpritePrincessParticle.h"

UINT8 next_state = STATE_MENU;

SET_N_STATES(N_STATES);
SET_N_SPRITE_TYPES(N_SPRITE_TYPES);

void InitStates() {
	INIT_STATE(STATE_MENU);
	INIT_STATE(STATE_GAME);
	INIT_STATE(STATE_LIVELOST);
	INIT_STATE(STATE_GAMEOVER);
}

void InitSprites() {
	INIT_SPRITE(SPRITE_PRINCESS);
	INIT_SPRITE(SPRITE_BULLET);
	INIT_SPRITE(SPRITE_MUSHROOM);
	INIT_SPRITE(SPRITE_ENEMY_BULLET);
	INIT_SPRITE(SPRITE_CSHOOTER);
	INIT_SPRITE(SPRITE_SHOOTER);
	INIT_SPRITE(SPRITE_EPARTICLE);
	INIT_SPRITE(SPRITE_PPARTICLE);
}

UINT8 GetTileReplacement(UINT8 t) {
	if(current_state == STATE_GAME) {
		switch(t) {
			case 1: return 254u;
			case 2: return 254u;
			case 3: return SPRITE_MUSHROOM;
			case 6: return SPRITE_SHOOTER;
			case 7: return SPRITE_CSHOOTER;
		}
	}
	return 255u;
}