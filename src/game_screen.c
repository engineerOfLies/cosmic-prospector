#include "game_screen.h"

#include <eol_particle.h>
#include <eol_dialog.h>
#include <eol_input.h>
#include <eol_logger.h>
#include <eol_entity.h>
#include <eol_window.h>
#include <eol_level.h>

typedef struct
{
  eolLine title;
  cpSpace *space; /**<level collision space*/
}levelData;

/*local global variabls*/

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

  eol_entity_draw_all();
  eol_particle_draw_all();
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
}

void game_screen()
{
  eolWindow *win;
  levelData *level;
  win = eol_window_load_from_file("ui/game_screen.def");
  if (win == NULL)return;
  win->customData = malloc(sizeof(levelData));
  level = (levelData*)win->customData;
  win->update = game_screen_update;
  win->draw = game_screen_draw;
  win->custom_delete = game_screen_free;
  level->space = cpSpaceNew();
  if (level->space == NULL)
  {
    eol_logger_message(
      EOL_LOG_ERROR,
      "Unable to create a physics space for new level!");
    return;
  }
  level->space->iterations = eol_level_clip_iterations();
  level->space->sleepTimeThreshold = 999999;
  cpSpaceSetEnableContactGraph(level->space,eolTrue);
  cpSpaceSetCollisionSlop(level->space, eol_level_slop());
  cpSpaceSetCollisionBias(level->space, eol_level_bias());
}


/*eol@eof*/
