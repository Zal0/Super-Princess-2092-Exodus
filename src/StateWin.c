#pragma bank 2
#include "StateWin.h"
UINT8 bank_STATE_WIN = 2;

#include <gb/gb.h>
#include "GBJAM2016.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/pressstarttileset.h"
#include "../res/src/endingtilemap.h"

extern const unsigned char* exo_gameover_mod_Data[];

void Start_STATE_WIN() {
	InitScrollTiles(0, 128, pressstarttileset, 3);
	InitScroll(endingtilemapWidth, endingtilemapHeight, endingtilemap, 0, 0, 3);
	SHOW_BKG;

	PlayMusic(exo_gameover_mod_Data, 4, 0);
}

void Update_STATE_WIN() {
	if(KEY_TICKED(J_START)) {
		SetState(STATE_MENU);
	}
}