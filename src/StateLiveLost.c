#include "Banks/SetBank2.h"
#include "main.h"

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/pressstart.h"
#include "../res/src/menuBG.h"
#include "../res/src/font.h"

#include "Print.h"

extern const unsigned char* exo_stage_mod_Data[];
extern UINT8 n_lives;

void Start_StateLiveLost() {
	InitScroll(&menuBG, 0, 0);
	SHOW_BKG;

	INIT_FONT(font, PRINT_BKG);
	PRINT_POS(4, 8);
	Printf("%d LIFES LEFT", (UINT16)(n_lives));

	PlayMusic(exo_stage_mod_Data, 4, 0);
}

void Update_StateLiveLost() {
	if(KEY_TICKED(J_START) | KEY_TICKED(J_A) | KEY_TICKED(J_B)) {
		SetState(StateGame);
	}
}