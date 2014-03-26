#include "game_screen.h"
#include "game_player.h"
#include "game_rocks.h"

#include <eol_particle.h>
#include <eol_camera.h>
#include <eol_dialog.h>
#include <eol_input.h>
#include <eol_logger.h>
#include <eol_entity.h>
#include <eol_window.h>
#include <eol_level.h>
#include <eol_config.h>
#include <eol_draw.h>

typedef struct
{
  eolLine title;
  eolLine bgPath;
  eolSprite *bgImage;
  cpSpace *space; /**<level collision space*/
  eolRectFloat  bounds;
}levelData;

/*local global variabls*/

eolWindow *_game_screen = NULL;

/*local function prototypes*/

/*function definitions*/

levelData *game_screen_level_data(eolWindow *win)
{
  if (win == NULL)
  {
    return NULL;
  }
  return (levelData*)win->customData;
}

eolBool game_screen_update(eolWindow *win,GList *updates)
{
  GList *c;
  levelData *level;
  eolComponent *comp = NULL;
  level = game_screen_level_data(win);
  if (!level)
  {
    return eolFalse;
  }
  
  for (c = updates;c != NULL;c = c->next)
  {
    if (c->data == NULL)continue;
    comp = (eolComponent *)c->data;
    switch (comp->id)
    {
      case 0:/*continue*/
        return eolTrue;
    }
  }
  return eolFalse;
}

void game_screen_add_entity_to_space(eolEntity *ent)
{
  levelData *level;
  level = game_screen_level_data(_game_screen);
  if (!level)
  {
    return;
  }
  eol_entity_add_to_space(ent,level->space);
}


void game_screen_draw_bounds(levelData *level)
{
  if (!level)return;
  eolOrientation ori;
  eol_orientation_clear(&ori);
/*  eol_draw_line_3D(eol_vec3d(level->bounds.x,
                             level->bounds.y,
                             0),
                   eol_vec3d(level->bounds.x,
                             level->bounds.y + level->bounds.h,
                             0),
                   1,
                   eol_vec3d(1,0,1),
                   1);
  eol_draw_rect_3D(level->bounds,1,ori);*/
}

void game_screen_draw(eolWindow *win)
{
  levelData *level;
  /*draw always happens unless the level is hidden
   update will not happen if there is a modal window in place*/
  level = game_screen_level_data(win);
  if (!level)
  {
    return;
  }
  
  /*presync*/
  eol_entity_presync_all();
  
  cpSpaceStep(level->space,eol_level_clip_step());
  
  /*post sync*/
  eol_entity_postsync_all();

  eol_sprite_draw(level->bgImage,0,0,0);
  glPushMatrix();
  eol_camera_setup();
  eol_entity_draw_all();
  eol_particle_draw_all();
  
  glPopMatrix();
  
}

void game_screen_free(void *data)
{
  levelData *level;
  level = game_screen_level_data((eolWindow*)data);
  if (!level)
  {
    return;
  }
  cpSpaceFree(level->space);
  _game_screen = NULL;
}

void game_screen_set_bounds(levelData *level)
{
  if (!level)return;
  eol_level_add_segment_to_space(level->bounds.x,
                                 level->bounds.y,
                                 level->bounds.x+level->bounds.w,
                                 level->bounds.y,
                                 level->space);
  eol_level_add_segment_to_space(level->bounds.x,
                                 level->bounds.y+level->bounds.h,
                                 level->bounds.x+level->bounds.w,
                                 level->bounds.y+level->bounds.h,
                                 level->space);
  eol_level_add_segment_to_space(level->bounds.x,
                                 level->bounds.y,
                                 level->bounds.x,
                                 level->bounds.y+level->bounds.h,
                                 level->space);
  eol_level_add_segment_to_space(level->bounds.x+level->bounds.w,
                                 level->bounds.y,
                                 level->bounds.x+level->bounds.w,
                                 level->bounds.y+level->bounds.h,
                                 level->space);
}

void game_screen()
{
  eolWindow *win;
  levelData *level;
  eolConfig *conf;
  int i;
  win = eol_window_load_from_file("ui/game_screen.def");
  if (win == NULL)return;
  win->customData = malloc(sizeof(levelData));
  level = (levelData*)win->customData;
  win->update = game_screen_update;
  win->draw = game_screen_draw;
  win->custom_delete = game_screen_free;
  
  _game_screen = win;
  
  level->space = cpSpaceNew();
  if (level->space == NULL)
  {
    eol_logger_message(
      EOL_LOG_ERROR,
      "Unable to create a physics space for new level!");
    return;
  }
  eol_particle_clear();
  level->space->iterations = eol_level_clip_iterations();
  level->space->sleepTimeThreshold = 999999;
  cpSpaceSetEnableContactGraph(level->space,eolTrue);
  cpSpaceSetCollisionSlop(level->space, eol_level_slop());
  cpSpaceSetCollisionBias(level->space, eol_level_bias());
  
  /*level config*/
  conf = eol_config_load("system/data/level.cfg");
  
  eol_config_get_rectfloat_by_tag(&level->bounds,conf,"bounds");
  if (eol_config_get_line_by_tag(level->bgPath,conf,"background"))
  {
    level->bgImage = eol_sprite_load(level->bgPath,-1,-1);
  }
  game_screen_set_bounds(level);
  eol_entity_add_to_space(spawnPlayer(NULL, eol_vec3d(-3.5,0,0)),level->space);
  for (i = 0; i < 100;i++)
  {
    game_rock_spawn("rock", eol_vec3d(3.5 - crandom(), crandom(),0));
  }
  
}


/*eol@eof*/
