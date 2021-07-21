#include "Banks/SetBank2.h"
#include "main.h"

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "Music.h"

#include "../res/src/pressstart.h"
#include "../res/src/endingtilemap.h"

DECLARE_MUSIC(exo_gameover);

void Start_StateWin() {
	InitScrollTiles(0, &pressstart);
	InitScroll(&endingtilemap, 0, 0);
	SHOW_BKG;

	PlayMusic(exo_gameover, 0);
}

void Update_StateWin() {
	if(KEY_TICKED(J_START)) {
		SetState(StateMenu);
	}
}