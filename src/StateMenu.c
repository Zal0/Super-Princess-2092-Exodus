#pragma bank 2
#include "main.h"
UINT8 bank_STATE_MENU = 2;

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/pressstarttilemap.h"
#include "../res/src/pressstarttileset.h"

extern const unsigned char* exo_start_mod_Data[];

void Start_STATE_MENU() {
	InitScrollTiles(0, 255, pressstarttileset, 3);
	InitScroll(pressstarttilemapWidth, pressstarttilemapHeight, pressstarttilemap, 0, 0, 3);
	SHOW_BKG;

	PlayMusic(exo_start_mod_Data, 4, 0);
}

extern UINT8 stage_completion;
void Update_STATE_MENU() {
	if(KEY_TICKED(J_START)) {
		stage_completion = 0;
		SetState(STATE_STAGE_SELECT);
	}
}