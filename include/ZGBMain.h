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
_SPRITE_DMG(SPRITE_PRINCESS,     spriteprincess  ) \
_SPRITE_DMG(SPRITE_BULLET,       princessBullet  ) \
_SPRITE_DMG(SPRITE_MUSHROOM,     mushroom        ) \
_SPRITE_DMG(SPRITE_ENEMY_BULLET, enemyBullet     ) \
_SPRITE_DMG(SPRITE_CSHOOTER,     ceilingshooter  ) \
_SPRITE_DMG(SPRITE_SHOOTER,      wallshooter     ) \
_SPRITE_DMG(SPRITE_EPARTICLE,    enemyexplosion  ) \
_SPRITE_DMG(SPRITE_PPARTICLE,    princessParticle) \
_SPRITE_DMG(SPRITE_PLATFORM,     mobileplatform  ) \
_SPRITE_DMG(SPRITE_FLY,          flyingbug       ) \
_SPRITE_DMG(SPRITE_ROLLER,       weirdroller     ) \
_SPRITE_DMG(SPRITE_OVNI,         ovni            ) \
_SPRITE_DMG(SPRITE_MISSILE,      missile         ) \
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif
