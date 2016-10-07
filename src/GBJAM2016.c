#include "GBJAM2016.h"

#include "StateMenu.h"
#include "StateGame.h"

//#include "SpritePrincess.h"

UINT8 next_state = STATE_MENU;// STATE_GAME

SET_N_STATES(N_STATES);
SET_N_SPRITE_TYPES(N_SPRITE_TYPES);

void InitStates() {
	//INIT_STATE(STATE_DISCLAIMER);
	INIT_STATE(STATE_MENU);
	INIT_STATE(STATE_GAME);
	//INIT_STATE(STATE_GAME_OVER);
	//INIT_STATE(STATE_WIN);
	//INIT_STATE(STATE_TESTS);
}

void InitSprites() {
	//INIT_SPRITE(SPRITE_PRINCESS);
	//INIT_SPRITE(SPRITE_ZURRAPA);
	//INIT_SPRITE(SPRITE_DEAD_PARTICLE);
	//INIT_SPRITE(SPRITE_AXE);
	//INIT_SPRITE(SPRITE_AZNAR);
	//INIT_SPRITE(SPRITE_FLAG);
}

UINT8 GetTileReplacement(UINT8 t) {
	/*if(current_state == STATE_GAME) {
		switch(t) {
				case 54: return SPRITE_ZURRAPA;
				case 55: return SPRITE_AZNAR;
				case 60: return SPRITE_FLAG;
		}
	}*/
	return 255u;
}