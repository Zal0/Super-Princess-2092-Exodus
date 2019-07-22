#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES             \
_STATE(STATE_MENU)         \
_STATE(STATE_GAME)         \
_STATE(STATE_LIVELOST)     \
_STATE(STATE_GAMEOVER)     \
_STATE(STATE_STAGEINTRO)   \
_STATE(STATE_WIN)          \
_STATE(STATE_STAGE_SELECT) \
_STATE(STATE_ENDING)       \
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SPRITE_PRINCESS,     spriteprincess,   3, FRAME_16x16, 11) \
_SPRITE_DMG(SPRITE_BULLET,       princessBullet,   3,  FRAME_8x16,  1) \
_SPRITE_DMG(SPRITE_MUSHROOM,     mushroom,         3, FRAME_16x16,  2) \
_SPRITE_DMG(SPRITE_ENEMY_BULLET, enemyBullet,      3, FRAME_8x16,   1) \
_SPRITE_DMG(SPRITE_CSHOOTER,     ceilingshooter,   3, FRAME_16x16,  2) \
_SPRITE_DMG(SPRITE_SHOOTER,      wallshooter,      3, FRAME_16x16,  2) \
_SPRITE_DMG(SPRITE_EPARTICLE,    enemyexplosion,   3, FRAME_16x16,  4) \
_SPRITE_DMG(SPRITE_PPARTICLE,    princessParticle, 3, FRAME_16x16,  2) \
_SPRITE_DMG(SPRITE_PLATFORM,     mobileplatform,   3, FRAME_16x16,  1) \
_SPRITE_DMG(SPRITE_FLY,          flyingbug,        3, FRAME_16x16,  2) \
_SPRITE_DMG(SPRITE_ROLLER,       weirdroller,      3, FRAME_16x16,  4) \
_SPRITE_DMG(SPRITE_OVNI,         ovni,             3, FRAME_16x16,  1) \
_SPRITE_DMG(SPRITE_MISSILE,      missile,          3, FRAME_16x16,  1) \
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif
