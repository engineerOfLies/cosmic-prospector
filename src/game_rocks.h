#ifndef __GAME_ROCKS__
#define __GAME_ROCKS__
/*
Copyright 2012 Engineer of Lies
This file is part of the Strange Mosaic source (working title) source code
All rights reserved.
*/

#include <eol_entity.h>

enum gameRockCollisionLevels {
  gameRocksCollideAll         = 0,/**<all rocks collide with each other*/
  gameRocksCollideAllDamage   = 1,/**<all rocks damage each other*/
  gameRocksCollideColor       = 2,/**<like color rocks collide with each other*/
  gameRocksCollideColorDamage = 3,/**<like color rocks damage each other*/
  gameRocksCollideNone        = 4 /**<rocks do not collide with each other*/
};

eolEntity *game_rock_spawn( eolLine rock, eolVec3D point);



#endif
