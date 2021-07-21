#include "Banks/SetBank7.h"
#include "main.h"

#include "../res/src/pressstart.h"
#include "../res/src/stageSelect.h"
#include "../res/src/font.h"

#include "ZGBMain.h"
#include "Print.h"
#include "Scroll.h"
#include "Keys.h"
#include "Math.h"
#include "Music.h"
#include "Sound.h"

extern UINT8 current_stage;
extern UINT8 current_level;
extern UINT8 n_lives;
extern UINT8 stage_completion;

DECLARE_MUSIC(levelselect);

void SetStage(UINT8 stage) {
	current_stage = stage;

	PRINT_POS(6, 13);
	Printf("STAGE %d", (UINT16)stage + 1);
	PlayFx(CHANNEL_1, 10, 0x17, 0x81, 0xF3, 0x62, 0x87);
}

void Start_StateStageSelect() {
	StopMusic;
	if(stage_completion == 7) {
		SetState(StateEnding);
	} else {
		InitScrollTiles(0, &pressstart);
		InitScroll(&stageSelect, 0, 0);
		SHOW_BKG;
	
		INIT_FONT(font, PRINT_BKG);
		PRINT(4, 11, "STAGE SELECT");

		for(current_stage = 0; current_stage != 3; current_stage += 1) {
			if(GET_BIT(stage_completion, current_stage) == 0) {
				SetStage(current_stage);
				break;
			}
		}

		PlayMusic(levelselect, 1);
	}
}

void Update_StateStageSelect() {
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


	if(KEY_TICKED(J_START) | KEY_TICKED(J_A) | KEY_TICKED(J_B)) {
		current_level = 0;
		n_lives = 3;

		SetState(StateStageIntro);
	}
}
