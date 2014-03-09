#ifndef __GAME_PROJECTILES__
#define __GAME_PROJECTILES__
/*
Copyright 2012 Engineer of Lies
This file is part of the Strange Mosaic source (working title) source code
All rights reserved.
*/

#include <eol_entity.h>

enum gameProjectileCollisionLevels {
  gameProjectilesCollideAll         = 0,/**<all projectiles collide with each other*/
  gameProjectilesCollideAllDamage   = 1,/**<all projectiles damage each other*/
  gameProjectilesCollideColor       = 2,/**<like color projectiles collide with each other*/
  gameProjectilesCollideColorDamage = 3,/**<like color projectiles damage each other*/
  gameProjectilesCollideNone        = 4 /**<projectiles do not collide with each other*/
};

eolEntity *game_projectile_spawn(eolLine filename,
                                 eolEntity *owner,
                                 eolVec3D point,
                                 eolFloat angle,
                                 eolFloat speed,
                                 eolFloat damage,
                                 eolVec4D dColor);



#endif
