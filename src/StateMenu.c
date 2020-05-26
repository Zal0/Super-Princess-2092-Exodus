#include "Banks/SetBank2.h"
#include "main.h"

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/pressstarttilemap.h"

extern const unsigned char* exo_start_mod_Data[];

void Start_StateMenu() {
	InitScroll(&pressstarttilemap, 0, 0);
	SHOW_BKG;

	PlayMusic(exo_start_mod_Data, 4, 0);
}

extern UINT8 stage_completion;
void Update_StateMenu() {
	if(KEY_TICKED(J_START)) {
		stage_completion = 0;
		SetState(StateStageSelect);
	}
}