#include "Banks/SetBank2.h"
#include "main.h"

#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "Music.h"

#include "../res/src/pressstart.h"
#include "../res/src/gameovertilemap.h"

DECLARE_MUSIC(exo_gameover);

void Start_StateGameOver() {
	InitScroll(&gameovertilemap, 0, 0);
	SHOW_BKG;

	PlayMusic(exo_gameover, 0);
}

void Update_StateGameOver() {
	if(KEY_TICKED(J_START) | KEY_TICKED(J_A) | KEY_TICKED(J_B)) {
		SetState(StateMenu);
	}
}