#include "Banks/SetBank2.h"
#include "main.h"

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/pressstart.h"
#include "../res/src/endingtilemap.h"

extern const unsigned char* exo_gameover_mod_Data[];

void Start_StateWin() {
	InitScrollTiles(0, &pressstart);
	InitScroll(&endingtilemap, 0, 0);
	SHOW_BKG;

	PlayMusic(exo_gameover_mod_Data, 4, 0);
}

void Update_StateWin() {
	if(KEY_TICKED(J_START)) {
		SetState(StateMenu);
	}
}