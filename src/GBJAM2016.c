#include "GBJAM2016.h"

#include "StateMenu.h"
#include "StateGame.h"

#include "SpritePrincess.h"
#include "SpriteBullet.h"
#include "SpriteMushroom.h"

UINT8 next_state = STATE_MENU;// STATE_GAME

SET_N_STATES(N_STATES);
SET_N_SPRITE_TYPES(N_SPRITE_TYPES);

void InitStates() {
	INIT_STATE(STATE_MENU);
	INIT_STATE(STATE_GAME);;
}

void InitSprites() {
	INIT_SPRITE(SPRITE_PRINCESS);
	INIT_SPRITE(SPRITE_BULLET);
	INIT_SPRITE(SPRITE_MUSHROOM);
}

UINT8 GetTileReplacement(UINT8 t) {
	if(current_state == STATE_GAME) {
		switch(t) {
				case 3: return SPRITE_MUSHROOM;
		}
	}
	return 255u;
}