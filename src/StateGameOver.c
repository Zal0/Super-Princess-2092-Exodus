#pragma bank=2
#include "StateGameOver.h"
UINT8 bank_STATE_GAMEOVER = 2;

#include <gb/gb.h>
#include "GBJAM2016.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/pressstarttileset.h"
#include "../res/src/gameovertilemap.h"

//extern const unsigned char * start_mod_Data[];

void Start_STATE_GAMEOVER() {
	InitScrollTiles(0, 128, pressstarttileset, 3);
	InitScroll(gameovertilemapWidth, gameovertilemapHeight, gameovertilemap, 0, 0, 3);
	SHOW_BKG;

	//PlayMusic(start_mod_Data, 2, 1);
}

void Update_STATE_GAMEOVER() {
	if(KEY_TICKED(J_START)) {
		SetState(STATE_MENU);
	}
}