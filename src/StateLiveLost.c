#include "Banks/SetAutoBank.h"
#include "main.h"

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "Music.h"

IMPORT_MAP(menuBG);
IMPORT_TILES(font);

#include "Print.h"

DECLARE_MUSIC(exo_stage);
extern UINT8 n_lives;

void Start_StateLiveLost() {
	InitScroll(BANK(menuBG), &menuBG, 0, 0);

	INIT_FONT(font, PRINT_BKG);
	PRINT_POS(4, 8);
	Printf("%d LIFES LEFT", (UINT16)(n_lives));

	PlayMusic(exo_stage, 0);
}

void Update_StateLiveLost() {
	if(KEY_TICKED(J_START) | KEY_TICKED(J_A) | KEY_TICKED(J_B)) {
		SetState(StateGame);
	}
}