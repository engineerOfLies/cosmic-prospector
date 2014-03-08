#include "game_title.h"
#include "game_screen.h"

#include <eol_particle.h>
#include <eol_dialog.h>
#include <eol_input.h>
#include <eol_logger.h>
#include <eol_graphics.h>
#include <eol_sprite.h>
#include <eol_window.h>

typedef struct
{
  eolSprite *background;
}titleData;

/*local global variabls*/

/*local function prototypes*/

/*function definitions*/

eolBool game_title_update(eolWindow *win,GList *updates)
{
  GList *c;
  int i;
  eolComponent *comp = NULL;
  if (win == NULL)return eolFalse;
  
  for (i = 0; i < 10; ++i)
  {
    eol_particle_make_point   (   eol_vec3d (0,0,0),
                                  eol_vec3d (crandom()*0.001,crandom()*0.001,crandom()*0.001),
                                  eol_vec3d (0,0,0),
                                  3,
                                  eol_vec3d (1,1,1),
                                  1,
                                  180);
  }
  for (c = updates;c != NULL;c = c->next)
  {
    if (c->data == NULL)continue;
    comp = (eolComponent *)c->data;
    switch (comp->id)
    {
      case 0:/*continue*/
        return eolTrue;
      case 1:/*new*/
        game_screen();
        eol_window_free(&win);
        return eolTrue;
      case 2:
        return eolTrue;
      case 3:/*quit*/
        eol_dialog_quit();
        return eolTrue;
    }
  }
  return eolFalse;
}

void game_title_draw(eolWindow *win)
{
  titleData *title;
  title = (titleData*)win->customData;
  eol_sprite_draw(title->background,0,0,0);
  eol_particle_draw_all();
}

void game_title_window()
{
  eolWindow *win;
  titleData *title;
  win = eol_window_load_from_file("ui/game_title.def");
  if (win == NULL)return;
  win->customData = malloc(sizeof(titleData));
  title = (titleData*)win->customData;
  win->update = game_title_update;
  win->draw = game_title_draw;
  title->background = eol_sprite_load("images/title_screen.png",-1,-1);
}


/*eol@eof*/
