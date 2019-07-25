#pragma bank 2
#include "main.h"
UINT8 bank_STATE_LIVELOST = 2;

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/pressstarttileset.h"
#include "../res/src/menuBG.h"
#include "../res/src/font.h"

#include "Print.h"

extern const unsigned char* exo_stage_mod_Data[];
extern UINT8 n_lives;

void Start_STATE_LIVELOST() {
	InitScrollTiles(0, &pressstarttileset, bank_pressstarttileset);
	InitScroll(menuBGWidth, menuBGHeight, menuBG, 0, 0, 3);
	SHOW_BKG;

	INIT_FONT(font, PRINT_BKG);
	PRINT_POS(4, 8);
	Printf("%d LIFES LEFT", (UINT16)(n_lives));

	PlayMusic(exo_stage_mod_Data, 4, 0);
}

void Update_STATE_LIVELOST() {
	if(KEY_TICKED(J_START) | KEY_TICKED(J_A) | KEY_TICKED(J_B)) {
		SetState(STATE_GAME);
	}
}