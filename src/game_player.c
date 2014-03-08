#include "game_player.h"

#include <eol_logger.h>

playerData *newPlayer()
{
  playerData* player;
  player = (playerData *)malloc(sizeof(playerData));
  if (!player)
  {
    eol_logger_message(
      EOL_LOG_ERROR,
      "game_player: newPlayer: unable to allocate player data!"
    );
    return NULL;
  }
  memset(player,0,sizeof(playerData));
  return player;
}

void freePlayer(playerData **player)
{
  free(*player);
  *player = NULL;
}

eolEntity *spawnPlayer(playerData *player)
{
  eolEntity *self;
  self = eol_entity_new();
  if (!self)
  {
    return NULL;
  }
  self->customData = player;
  conf = eol_config_load("system/data/player.cfg");
  data->player = playerData;
  self->team = (eolUint)playerData;
  
  eol_line_cpy(actor,"models/player.actor");
  eol_config_get_line_by_tag(actor,conf,"actor");
  eol_entity_add_actor(self,eol_actor_load(actor));
  eol_entity_set_actor_bounds(self);
  eol_config_get_float_by_tag(&self->radius,conf,"radius");
  eol_actor_set_action(self->actor,"idle");
    
  eol_vec3d_copy(self->ori.position,point);
  self->ori.rotation.z = 0;
  
  eol_vec3d_set(self->ori.color,1,1,1);
  eol_config_get_vec3d_by_tag(&self->ori.color,conf,"color");
  
  self->moveSpeed = 8;
  self->topSpeed = 32;
  self->terminalSpeed = 4;
  eol_vec3d_set(self->gravityAccel,0,-1,0);
  self->dampening = 2;
  
  eol_config_get_float_by_tag(&self->moveSpeed,conf,"moveSpeed");
  eol_config_get_float_by_tag(&self->topSpeed,conf,"topSpeed");
  eol_config_get_vec3d_by_tag(&self->gravityAccel,conf,"gravity");
  eol_config_get_float_by_tag(&self->terminalSpeed,conf,"gravityMax");
  
  self->bounces = eolFalse;
  self->mass = 10;
  self->trackTrail = eolTrue;
  self->drawTrail = eolFalse;
  eol_entity_set_collision_mask(self,CP_ALL_LAYERS);
  
  eol_entity_shape_make_circle(self);
  eol_level_add_entity_to_active_layer(self);
  
  self->levelTouch = game_player_levelTouch;
  self->die = game_player_die;
  self->update = game_player_update;
  self->think = game_player_think;
  self->thinkRate = 15;
  
  _game_player_local = self;

  return self;
  
  /*load player stats from file*/

}


/*eol@eof*/
