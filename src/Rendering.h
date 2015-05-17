#include <pebble.h>
#ifndef REND
  #define REND
void draw_parallax(GContext* ctx);
void draw_moving_platforms(GContext* ctx);
void layer_update_proc(Layer* layer, GContext* ctx);
void draw_2px_border_text(GContext* ctx, char* text, int x, int y, int fontType);
void draw_state_ui(GContext* ctx);
#endif