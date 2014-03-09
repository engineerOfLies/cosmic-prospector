#ifndef __GAME_PLAYER__
#define __GAME_PLAYER__

#include <eol_entity.h>

typedef struct
{
  eolLine name;
  eolLine shipname;
  eolFloat minMove,maxMove;
  eolFloat moveSpeed;
  eolInt  credits;
  eolInt  cargoSpace;
  eolFloat  oxygenLevel;
  eolInt  laserPower;
  eolWord secondaryWeapon;
  eolInt  seccondaryShots;
}playerData;

playerData *newPlayer();

void freePlayer(playerData **player);

eolEntity *spawnPlayer(playerData *player,eolVec3D point);


#endif
