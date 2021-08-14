#include "Banks/SetBank2.h"
#include "main.h"

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "Music.h"
#include "Print.h"

IMPORT_MAP(menuBG);
IMPORT_TILES(font);

DECLARE_MUSIC(exo_stage);
extern UINT8 current_stage;
extern UINT8 n_lives;

void Start_StateStageIntro() {
	InitScroll(BANK(menuBG), &menuBG, 0, 0);
	SHOW_BKG;

	INIT_FONT(font, PRINT_BKG);
	PRINT_POS(6, 6);
	Printf("STAGE %d", (UINT16)(current_stage + 1));
	PRINT(8, 8, "GO!");
	PRINT_POS(4, 13);
	Printf("%d LIFES LEFT", (UINT16)(n_lives));

	PlayMusic(exo_stage, 0);
}

void Update_StateStageIntro() {
	if(KEY_TICKED(J_START) | KEY_TICKED(J_A) | KEY_TICKED(J_B)) {
		SetState(StateGame);
	}
}