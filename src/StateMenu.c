#pragma bank=2
#include "StateMenu.h"
UINT8 bank_STATE_MENU = 2;

#include <gb/gb.h>
#include "GBJAM2016.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/pressstarttilemap.h"
#include "../res/src/pressstarttileset.h"

extern const unsigned char* exo_start_mod_Data[];

void Start_STATE_MENU() {
	InitScrollTiles(0, 128, pressstarttileset, 3);
	InitScroll(pressstarttilemapWidth, pressstarttilemapHeight, pressstarttilemap, 0, 0, 3);
	SHOW_BKG;

	PlayMusic(exo_start_mod_Data, 4, 0);
}

extern struct LevelInfo levels_1[];
extern struct LevelInfo levels_2[];
extern struct LevelInfo levels_3[];
extern struct LevelInfo* levels;

extern UINT8 current_level;
extern UINT8 n_lives;
void Update_STATE_MENU() {
	if(KEY_TICKED(J_START)) {
		levels = levels_2;
		current_level = 0;
		n_lives = 3;

		SetState(STATE_STAGEINTRO);
	}
}