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

#include "../res/src/princess.h"
#include "../res/src/mushroom.h"
#include "../res/src/enemybullet16x16.h"
#include "../res/src/ceilingshooter.h"
#include "../res/src/wallshooter.h"
#include "../res/src/enemyexplosion.h"

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
	INIT_SPRITE(SPRITE_PRINCESS,     spriteprincess,   3, FRAME_16x16, 14 * 4);
	INIT_SPRITE(SPRITE_BULLET,       spriteprincess,   3, FRAME_16x16, 14 * 4);
	INIT_SPRITE(SPRITE_PPARTICLE,    spriteprincess,   3, FRAME_16x16, 14 * 4);
	INIT_SPRITE(SPRITE_MUSHROOM,     mushroom,         3, FRAME_16x16,  2 * 4);
	INIT_SPRITE(SPRITE_ENEMY_BULLET, enemybullet16x16, 3, FRAME_16x16,  1 * 4);
	INIT_SPRITE(SPRITE_CSHOOTER,     ceilingshooter,   3, FRAME_16x16,  2 * 4);
	INIT_SPRITE(SPRITE_SHOOTER,      wallshooter,      3, FRAME_16x16,  2 * 4); 
	INIT_SPRITE(SPRITE_EPARTICLE,    enemyexplosion,   3, FRAME_16x16,  4 * 4);
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