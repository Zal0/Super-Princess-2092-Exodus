#pragma bank 2
#include "main.h"
UINT8 bank_STATE_WIN = 2;

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/pressstarttileset.h"
#include "../res/src/endingtilemap.h"

extern const unsigned char* exo_gameover_mod_Data[];

void Start_STATE_WIN() {
	InitScrollTiles(0, &pressstarttileset);
	InitScroll(&endingtilemap, 0, 0);
	SHOW_BKG;

	PlayMusic(exo_gameover_mod_Data, 4, 0);
}

void Update_STATE_WIN() {
	if(KEY_TICKED(J_START)) {
		SetState(STATE_MENU);
	}
}