#include "game_rocks.h"
#include "game_screen.h"

#include <eol_level.h>
#include <eol_config.h>
#include <eol_logger.h>
/*local type definitions*/

/*local variables*/
eolUint _game_rocks_collision_level = 0;

/*local function prototypes*/
void game_rocks_draw(eolEntity *self);
void game_rocks_update(eolEntity *self);
void game_rocks_think(eolEntity *self);
void game_rocks_touch(eolEntity * self,eolEntity * other);
void game_rocks_levelTouch(eolEntity * self,eolTrace *trace);
void game_rocks_activate(eolEntity * self,eolEntity * other);
void game_rocks_die(eolEntity * self);

/*function definitions*/

void game_rocks_config()
{
  eolConfig *conf = NULL;
  _game_rocks_collision_level = 0;
  conf = eol_config_load("system/rocks.cfg");
  if (!conf)return;
  eol_config_get_uint_by_tag(&_game_rocks_collision_level,conf,"collisionLevel");
  eol_config_free(&conf);
}

eolEntity *game_rock_spawn( eolLine rock,
                            eolVec3D point)
{
  eolLine path;
  eolConfig *conf;
  eolEntity *self;
  eolLine buffer;

  self = eol_entity_new();
  if (!self)
  {
    eol_logger_message(
      EOL_LOG_WARN,
      "game_rocks:unable to spawn rock entity\n");
    return NULL;
  }

  snprintf(path,EOLLINELEN,"system/data/%s.def",rock);
  conf = eol_config_load(path);
  if (!conf)return NULL;

  self->team = 2;

  eol_line_clear(buffer);
  eol_config_get_line_by_tag(buffer,conf,"actor");
  eol_entity_add_actor(self,eol_actor_load(buffer));
  eol_entity_set_actor_bounds(self);
  
  eol_vec3d_copy(self->ori.position, point);

  eol_vec3d_set(self->ori.scale,0.3,0.3,0.3);
  eol_config_get_vec3d_by_tag(&self->ori.color,conf,"color");

  eol_config_get_bool_by_tag(&self->bounces,conf,"bounce");
  eol_config_get_bool_by_tag(&self->drawTrail,conf,"drawTrail");
  eol_config_get_float_by_tag(&self->trailWidth,conf,"trailWidth");

  self->mass = 10;
  self->trackTrail = eolTrue;
  
  eol_entity_set_collision_mask(self,CP_ALL_LAYERS);
  eol_entity_shape_make_circle(self);

  // self->touch = game_rocks_touch;
  // self->levelTouch = game_rocks_levelTouch;
  self->die = game_rocks_die;
  self->update = game_rocks_update;

  eol_config_free(&conf);
  game_screen_add_entity_to_space(self);
  return self;
}

void game_rocks_update(eolEntity *self)
{
  /*tick down times life...*/
}

void game_rocks_think(eolEntity *self)
{
  /*adjust course for homing / acquire target*/
}

void game_rocks_touch(eolEntity * self,eolEntity * other)
{

}

void game_rocks_levelTouch(eolEntity * self,eolTrace *trace)
{

}

void game_rocks_activate(eolEntity * self,eolEntity * other)
{
  
}

void game_rocks_die(eolEntity * self)
{
  self->state = eolEntityDead;
}

/*eol@eof*/
