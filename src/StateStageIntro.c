#pragma bank=2
#include "StateStageIntro.h"
UINT8 bank_STATE_STAGEINTRO = 2;

#include <gb/gb.h>
#include "GBJAM2016.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/pressstarttileset.h"
#include "../res/src/menuBG.h"
#include "../res/src/font.h"

#include "Print.h"

extern const unsigned char* exo_stage_mod_Data[];
extern UINT8 current_stage;

void Start_STATE_STAGEINTRO() {
	InitScrollTiles(0, 128, pressstarttileset, 3);
	InitScroll(menuBGWidth, menuBGHeight, menuBG, 0, 0, 3);
	SHOW_BKG;

	INIT_FONT(font, 3, PRINT_BKG);
	PRINT_POS(6, 8);
	Printf("STAGE %d", (UINT16)(current_stage + 1));
	PRINT(8, 10, "GO!");

	PlayMusic(exo_stage_mod_Data, 4, 0);
}

void Update_STATE_STAGEINTRO() {
	if(KEY_TICKED(J_START)) {
		SetState(STATE_GAME);
	}
}