#pragma bank=2
#include "StateStageSelect.h"
UINT8 bank_STATE_STAGE_SELECT = 2;

#include "../res/src/pressstarttileset.h"
#include "../res/src/menuBG.h"
#include "../res/src/font.h"

#include "GBJAM2016.h"
#include "Print.h"
#include "Scroll.h"
#include "Keys.h"

extern struct LevelInfo levels_1[];
extern struct LevelInfo levels_2[];
extern struct LevelInfo levels_3[];
extern struct LevelInfo* levels;

extern UINT8 current_level;
extern UINT8 n_lives;

void SetStage(UINT8 stage) {
	struct LevelInfo* lvls[] = {levels_1, levels_2, levels_3};
	levels = lvls[stage];

	print_x = 6;
	print_y = 13;
	Printf("STAGE %d", (UINT16)stage + 1);
}

UINT8 GetStageIdx() {
	if(levels == levels_1) {
		return 0;
	}
	
	if(levels == levels_2) {
		return 1;
	}

	if(levels == levels_3) {
		return 2;
	}

	return 0;
}

void Start_STATE_STAGE_SELECT() {
	InitScrollTiles(0, 128, pressstarttileset, 3);
	InitScroll(menuBGWidth, menuBGHeight, menuBG, 0, 0, 3);
	SHOW_BKG;
	
	font_idx = 255 - 45;
	InitScrollTiles(255 - 45, 45, font, 3);

	print_target = PRINT_BKG;
	print_x = 4;
	print_y = 11;
	Printf("STAGE SELECT");
	SetStage(0);
}

void Update_STATE_STAGE_SELECT() {
	UINT8 stage_idx = 0;

	if(KEY_TICKED(J_LEFT)) {
		stage_idx = GetStageIdx();
		if(stage_idx != 0)
			SetStage(stage_idx - 1);
	}

	if(KEY_TICKED(J_RIGHT)) {
		stage_idx = GetStageIdx();
		if(stage_idx != 2)
			SetStage(stage_idx + 1);
	}


	if(KEY_TICKED(J_START)) {
		current_level = 0;
		n_lives = 3;

		SetState(STATE_STAGEINTRO);
	}
}
