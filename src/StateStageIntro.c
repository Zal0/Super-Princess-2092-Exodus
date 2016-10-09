#pragma bank=2
#include "StateStageIntro.h"
UINT8 bank_STATE_STAGEINTRO = 2;

#include <gb/gb.h>
#include "GBJAM2016.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/pressstarttileset.h"
#include "../res/src/stagenumber.h"
#include "../res/src/numbers.h"

extern const unsigned char* exo_stage_mod_Data[];

void Start_STATE_STAGEINTRO() {
	InitScrollTiles(0, 128, pressstarttileset, 3);
	InitScroll(stagenumberWidth, stagenumberHeight, stagenumber, 0, 0, 3);
	SHOW_BKG;

	SPRITES_8x16;
	LoadSprite(3 * 4, numbers, 3);
	SHOW_SPRITES;


	PlayMusic(exo_stage_mod_Data, 4, 0);
}

extern UINT8 n_lives;
void Update_STATE_STAGEINTRO() {
	DrawFrame(0, FRAME_8x16, 0, 96, 64, 0); 

	if(KEY_TICKED(J_START)) {
		SetState(STATE_GAME);
	}
}