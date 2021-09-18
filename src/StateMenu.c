#include "Banks/SetAutoBank.h"
#include "main.h"

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "Music.h"

IMPORT_MAP(pressstarttilemap);

DECLARE_MUSIC(exo_start);

void START() {
	InitScroll(BANK(pressstarttilemap), &pressstarttilemap, 0, 0);

	PlayMusic(exo_start, 0);
}

extern UINT8 stage_completion;
void UPDATE() {
	if(KEY_TICKED(J_START)) {
		stage_completion = 0;
		SetState(StateStageSelect);
	}
}