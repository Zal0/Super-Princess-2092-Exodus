#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES             \
_STATE(StateMenu)         \
_STATE(StateGame)         \
_STATE(StateLiveLost)     \
_STATE(StateGameOver)     \
_STATE(StateStageIntro)   \
_STATE(StateWin)          \
_STATE(StateStageSelect) \
_STATE(StateEnding)       \
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePrincess,         spriteprincess  ) \
_SPRITE_DMG(SpriteBullet,           princessBullet  ) \
_SPRITE_DMG(SpriteMushroom,         mushroom        ) \
_SPRITE_DMG(SpriteEnemyBullet,      enemyBullet     ) \
_SPRITE_DMG(SpriteCeilingShooter,   ceilingshooter  ) \
_SPRITE_DMG(SpriteShooter,          wallshooter     ) \
_SPRITE_DMG(SpriteEnemyParticle,    enemyexplosion  ) \
_SPRITE_DMG(SpritePrincessParticle, princessParticle) \
_SPRITE_DMG(SpritePlatform,         mobileplatform  ) \
_SPRITE_DMG(SpriteFly,              flyingbug       ) \
_SPRITE_DMG(SpriteRoller,           weirdroller     ) \
_SPRITE_DMG(SpriteOvni,             ovni            ) \
_SPRITE_DMG(SpriteMissile,          missile         ) \
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif
