#pragma bank=2
#include "StateMenu.h"
UINT8 bank_STATE_MENU = 2;

#include <gb/gb.h>
#include "GBJAM2016.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/splash.h"
#include "../res/src/splashtiles.h"

//extern const unsigned char * start_mod_Data[];

//extern UINT8 level;
//extern UINT16 reset_x;
//extern UINT16 reset_y;

void Start_STATE_MENU() {
	InitScrollTiles(0, 102, splashtiles, 3);
	InitScroll(splashmapWidth, splashmapHeight, splashmap, 0, 0, 3);
	SHOW_BKG;

	//level = 0;
	//PlayMusic(start_mod_Data, 2, 1);
}

void Update_STATE_MENU() {
	if(KEY_TICKED(J_START)) {
		//reset_x = 32;
		//reset_y = 112;
		SetState(STATE_GAME);
	}
}