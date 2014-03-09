/*
Copyright 2014 Engineer of Lies
This file is part of the Strange Mosaic source (working title) source code
All rights reserved.
*/

/*game includes*/
#include "game_title.h"

/*eol includes*/
#include <eol.h>
#include <eol_graphics.h>
#include <eol_input.h>
#include <eol_camera.h>
#include <eol_mouse.h>
#include <eol_window.h>
#include <eol_level.h>
#include <eol_entity.h>
#include <eol_dialog.h>
#include <eol_lighting.h>
#include <eol_particle.h>
#include <eol_font.h>
#include <string.h>
#include <stdio.h>

void Init_All(const char *argv);
void Setup_All();

int main(int argc, char *argv[])
{
  int done;
  eolLine fps;
  int i;
  for(i = 1;i < argc;i++)
  {
    if(strcmp(argv[i],"-fs")== 0)
    {
    }
    if(strcmp(argv[i],"-wm")== 0)
    {
    }
  }
  Init_All(argv[0]);
  Setup_All();
  done = 0;
  do
  {
    eol_input_update();
    eol_mouse_update();

    eol_level_update_active();

    eol_entity_think_all();
    eol_entity_update_all();

    eol_particle_update_all();
    eol_camera_update();
    eol_window_update_all();

    eol_graphics_frame_begin();
    {
      eol_window_draw_all();
    }

    sprintf(fps,"FPS: %f",eol_graphics_get_FPS());
    eol_font_draw_text_justify(
      fps,
      640,
      0,
      eol_vec3d(1,0,0),
      1,
      2,
      eolJustifyLeft);

    eol_graphics_frame_end();

    
    if((eol_input_quit_check()) ||
      ((eol_input_is_key_released(SDLK_F4)) && (eol_input_is_mod_held(KMOD_ALT))) ||
      ((eol_input_is_key_released(SDLK_q)) && (eol_input_is_mod_held(KMOD_ALT))))
    {
      eol_dialog_quit();
    }
  }while(!done);
  exit(0);
  return 0;
}

void Setup_All()
{
  eol_mouse_show();
  eol_lighting_setup_rep_plot();
  game_title_window();
}

void Init_All(const char *argv)
{
  eol_init(EOL_ALL);
  eol_entity_config();
  eol_entity_init();
  eol_level_config();
  eol_level_init();
  eol_camera_config();
  eol_camera_init();
}

/*eol @ eof*/
