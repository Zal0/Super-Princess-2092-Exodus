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
#include "Math.h"
#include "gbt_player.h"

extern struct LevelInfo* stages[];
extern UINT8 current_stage;
extern UINT8 current_level;
extern UINT8 n_lives;
extern UINT8 stage_completion;

extern const unsigned char* levelselect_mod_Data[];

void SetStage(UINT8 stage) {
	current_stage = stage;

	PRINT_POS(6, 13);
	Printf("STAGE %d", (UINT16)stage + 1);
}

void Start_STATE_STAGE_SELECT() {
	gbt_stop();
	if(stage_completion == 7) {
		SetState(STATE_ENDING);
	} else {
		InitScrollTiles(0, 128, pressstarttileset, 3);
		InitScroll(menuBGWidth, menuBGHeight, menuBG, 0, 0, 3);
		SHOW_BKG;
	
		INIT_FONT(font, 3, PRINT_BKG);
		PRINT(4, 11, "STAGE SELECT");

		for(current_stage = 0; current_stage != 3; current_stage += 1) {
			if(GET_BIT(stage_completion, current_stage) == 0) {
				SetStage(current_stage);
				break;
			}
		}

		PlayMusic(levelselect_mod_Data, 4, 1);
	}
}

void Update_STATE_STAGE_SELECT() {
	UINT8 tmp;
	if(KEY_TICKED(J_LEFT)) {
		for(tmp = current_stage - 1; tmp != 255; -- tmp) {
			if(GET_BIT(stage_completion, tmp) == 0) {
				SetStage(tmp);
				break;
			}
		}
	}

	if(KEY_TICKED(J_RIGHT)) {
		for(tmp = current_stage + 1; tmp != 3; ++ tmp) {
			if(GET_BIT(stage_completion, tmp) == 0) {
				SetStage(tmp);
				break;
			}
		}
	}


	if(KEY_TICKED(J_START)) {
		current_level = 0;
		n_lives = 3;

		SetState(STATE_STAGEINTRO);
	}
}
