#include "game_player.h"
#include "game_projectiles.h"

#include <eol_mouse.h>
#include <eol_logger.h>
#include <eol_font.h>
#include <eol_particle.h>

/*local global variabls*/

/*local function prototypes*/
void game_player_update(eolEntity *self);
void game_player_think(eolEntity *self);
void game_player_levelTouch(eolEntity * self,eolTrace *trace);
void game_player_die(eolEntity * self);


/*function definitions*/

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

eolEntity *spawnPlayer(playerData *player, eolVec3D point)
{
  eolEntity *self;
  eolConfig *conf;
  eolLine   actor;
  self = eol_entity_new();
  if (!self)
  {
    return NULL;
  }
  self->customData = player;
  conf = eol_config_load("system/data/player.cfg");
  self->team = 1;
  
  eol_line_cpy(actor,"models/player.actor");
  eol_config_get_line_by_tag(actor,conf,"actor");
  eol_entity_add_actor(self,eol_actor_load(actor));
  eol_entity_set_actor_bounds(self);
  eol_config_get_float_by_tag(&self->radius,conf,"radius");
  eol_actor_set_action(self->actor,"aimleft");
    
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
  
  self->levelTouch = game_player_levelTouch;
  self->die = game_player_die;
  self->update = game_player_update;
  self->think = game_player_think;
  self->thinkRate = 15;
  
  return self;
  
  /*load player stats from file*/

}

void game_player_update(eolEntity *self)
{
  /*run cooldowns, fire projectiles*/
  eolInt y = 0;
  eolUint h = 0;
  eolFloat targetY;
  eolFloat percentGoal;
  eol_mouse_get_position(NULL,&y);
  eol_graphics_get_size(NULL, &h);
  if (h)
  {
    percentGoal = (eolFloat)y / (eolFloat)h;
  }
  targetY = (-6.0 * percentGoal) + 3.0;
  self->vector.position.y = (targetY - self->ori.position.y)/8;
  
  self->ori.position.y += self->vector.position.y;
}

void game_player_think(eolEntity *self)
{
  /*gather input and set vectors*/
  if (eol_mouse_input_held(0))
  {
    game_projectile_spawn("bullet",
                          self,
                          eol_vec3d(
                            self->ori.position.x + 0.25,
                            self->ori.position.y + 0.2,
                            self->ori.position.z
                          ),
                          0,
                          15,
                          1,
                          eol_vec4d(1,1,1,1));
  }
}

void game_player_levelTouch(eolEntity * self,eolTrace *trace)
{
  /*probably not needed*/
}

void game_player_die(eolEntity * self)
{
  /*probably not needed*/
}

/*eol@eof*/
