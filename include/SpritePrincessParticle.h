#ifndef SPRITE_PPARTICLE_H
#define SPRITE_PPARTICLE_H

#include "main.h"

DECLARE_SPRITE(SPRITE_PPARTICLE);

void PParticleResetCustomData();
void CreatePParticle(UINT16 x, UINT16 y, INT8 vx, INT8 vy);

#endif