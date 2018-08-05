#pragma bank 2
#include "main.h"
UINT8 bank_STATE_STAGEINTRO = 2;

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/pressstarttileset.h"
#include "../res/src/menuBG.h"
#include "../res/src/font.h"

#include "Print.h"

extern const unsigned char* exo_stage_mod_Data[];
extern UINT8 current_stage;
extern UINT8 n_lives;

void Start_STATE_STAGEINTRO() {
	InitScrollTiles(0, 128, pressstarttileset, 3);
	InitScroll(menuBGWidth, menuBGHeight, menuBG, 0, 0, 3);
	SHOW_BKG;

	INIT_FONT(font, 3, PRINT_BKG);
	PRINT_POS(6, 6);
	Printf("STAGE %d", (UINT16)(current_stage + 1));
	PRINT(8, 8, "GO!");
	PRINT_POS(4, 13);
	Printf("%d LIFES LEFT", (UINT16)(n_lives));

	PlayMusic(exo_stage_mod_Data, 4, 0);
}

void Update_STATE_STAGEINTRO() {
	if(KEY_TICKED(J_START) | KEY_TICKED(J_A) | KEY_TICKED(J_B)) {
		SetState(STATE_GAME);
	}
}