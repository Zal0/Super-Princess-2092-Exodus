#pragma bank 2
#include "main.h"
UINT8 bank_STATE_GAMEOVER = 2;

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/pressstarttileset.h"
#include "../res/src/gameovertilemap.h"

extern const unsigned char* exo_gameover_mod_Data[];

void Start_STATE_GAMEOVER() {
	InitScrollTiles(0, &pressstarttileset);
	InitScroll(&gameovertilemap, 0, 0);
	SHOW_BKG;

	PlayMusic(exo_gameover_mod_Data, 4, 0);
}

void Update_STATE_GAMEOVER() {
	if(KEY_TICKED(J_START) | KEY_TICKED(J_A) | KEY_TICKED(J_B)) {
		SetState(STATE_MENU);
	}
}