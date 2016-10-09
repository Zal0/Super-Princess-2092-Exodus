#pragma bank=2
#include "StateLiveLost.h"
UINT8 bank_STATE_LIVELOST = 2;

#include <gb/gb.h>
#include "GBJAM2016.h"
#include "Scroll.h"
#include "Keys.h"

#include "../res/src/pressstarttileset.h"
#include "../res/src/lifesleft.h"
#include "../res/src/numbers.h"

//extern const unsigned char * start_mod_Data[];

void Start_STATE_LIVELOST() {
	InitScrollTiles(0, 128, pressstarttileset, 3);
	InitScroll(lifesleftWidth, lifesleftHeight, lifesleft, 0, 0, 3);
	SHOW_BKG;

	SPRITES_8x16;
	LoadSprite(3 * 4, numbers, 3);
	SHOW_SPRITES;


	//PlayMusic(start_mod_Data, 2, 1);
}

extern UINT8 n_lives;
void Update_STATE_LIVELOST() {
	DrawFrame(0, FRAME_8x16, n_lives - 1, 36, 64, 0); 

	if(KEY_TICKED(J_START)) {
		SetState(STATE_GAME);
	}
}