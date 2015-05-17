#include <pebble.h>
#include "Globals.h"
#include "Rendering.h"
#include "ResourceIO.h"
#include "Collision.h"
#include "GameLogic.h"


static void select_pressed(ClickRecognizerRef recognizer, void *context)
{
  is_select_pressed = 1;
  
  
  
}

void focus_handler(bool in_focus) {
  if (!in_focus && state == RUNNING) {
    state = PAUSED;
  }
}

static void select_released(ClickRecognizerRef recognizer, void *context)
{
  is_select_pressed = 0;
  if(state == TITLE_SCREEN || state == PAUSED)
    state = RUNNING;
  
if(state == GAME_OVER)
  {
    initGameConfig();
    title_screen = gbitmap_create_with_resource(RESOURCE_ID_TITLE_SCREEN);
    layer_mark_dirty((Layer*)bitmap_layer);
  }
  
  if(state == GAME_OVER)
    state = TITLE_SCREEN;
  
  if(state != TITLE_SCREEN && title_screen != NULL)
  {
    gbitmap_destroy(title_screen);
    title_screen = NULL;
  }
}
static void up_pressed(ClickRecognizerRef recognizer, void *context)
{
  is_up_pressed = 1;
 
}

static void up_released(ClickRecognizerRef recognizer, void *context)
{
   is_up_pressed = 0;
  
  if(state == TITLE_SCREEN || state == PAUSED)
    state = RUNNING;
  
if(state == GAME_OVER)
  {
    initGameConfig();
    title_screen = gbitmap_create_with_resource(RESOURCE_ID_TITLE_SCREEN);
    layer_mark_dirty((Layer*)bitmap_layer);
  }
  
  if(state == GAME_OVER)
    state = TITLE_SCREEN;
  
  if(state != TITLE_SCREEN && title_screen != NULL)
  {
    gbitmap_destroy(title_screen);
    title_screen = NULL;
  }
}

static void down_pressed(ClickRecognizerRef recognizer, void *context)
{
 is_down_pressed = 1;
}

static void down_released(ClickRecognizerRef recognizer, void *context)
{
 is_down_pressed = 0;
  
  if(state == GAME_OVER)
  {
    initGameConfig();
    title_screen = gbitmap_create_with_resource(RESOURCE_ID_TITLE_SCREEN);
    layer_mark_dirty((Layer*)bitmap_layer);
  }  
  
  if(state == RUNNING)
  {  
    state = PAUSED;
    layer_mark_dirty((Layer*)bitmap_layer);
  }
  else if(state == TITLE_SCREEN || state == PAUSED)
    state = RUNNING;
  else if(state == GAME_OVER)
    state = TITLE_SCREEN;
  
  if(state != TITLE_SCREEN && title_screen != NULL)
  {
    gbitmap_destroy(title_screen);
    title_screen = NULL;
  }
}


static void click_config_provider(void *context) {
  window_raw_click_subscribe(BUTTON_ID_SELECT, select_pressed, select_released, NULL);
  window_raw_click_subscribe(BUTTON_ID_UP, up_pressed, up_released, NULL);
  window_raw_click_subscribe(BUTTON_ID_DOWN, down_pressed, down_released, NULL);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  #ifdef PBL_COLOR
  bitmap_layer = bitmap_layer_create(GRect(0,STATUS_BAR_LAYER_HEIGHT , WIN_WIDTH, WIN_HEIGHT));
  GRect frame = GRect(0, 0, WIN_WIDTH, STATUS_BAR_LAYER_HEIGHT);
  status_bar = status_bar_layer_create();
  layer_set_frame(status_bar_layer_get_layer(status_bar), frame);
  layer_add_child(window_layer, status_bar_layer_get_layer(status_bar));
  #else
  bitmap_layer = bitmap_layer_create(GRect(0,0, WIN_WIDTH, WIN_HEIGHT));
  #endif

    

  
  layer_add_child(window_layer, bitmap_layer_get_layer(bitmap_layer));
  
  
  #ifdef PBL_COLOR 
    bitmap_layer_set_compositing_mode(bitmap_layer, GCompOpSet);
  #endif
 
}

static void window_unload(Window *window) {
  bitmap_layer_destroy(bitmap_layer);
  #ifdef PBL_COLOR
  status_bar_layer_destroy(status_bar);
  #endif
}


static void timer_callback(void *data)
{
  
  game_logic();

  //forces update_proc, which renders game
  if(state == RUNNING)
  layer_mark_dirty((Layer*)bitmap_layer);
 

  event_timer = app_timer_register(MILLISECONDS_PER_FRAME, timer_callback, NULL);

}




static void init(void) {
   
  window = NULL;
 // APP_LOG(APP_LOG_LEVEL_DEBUG, "pre window create: %p", window);
  window = window_create();
 // APP_LOG(APP_LOG_LEVEL_DEBUG, "post window create: %p", window);
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;

  initBitmaps();
 
  //patchSegment(0,0);
  //patchSegment(0,1);

  timer_cnt = 0;
  // APP_LOG(APP_LOG_LEVEL_DEBUG, "Done loading bitmaps");
  initGameConfig();
  //  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initgameconfig");
  loadGameState();
  //  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done loading gamestate");
  deletePersistentKeys();
    //APP_LOG(APP_LOG_LEVEL_DEBUG, "Done deleting persistent keys");

  if(state == TITLE_SCREEN)
    title_screen = gbitmap_create_with_resource(RESOURCE_ID_TITLE_SCREEN);
  layer_set_update_proc(window_get_root_layer(window), layer_update_proc);
    //render once for title screen/pause screen
 // layer_mark_dirty((Layer*)bitmap_layer);
  app_focus_service_subscribe(focus_handler);
  app_message_open(32, 32);
  event_timer = app_timer_register(MILLISECONDS_PER_FRAME, timer_callback, NULL);
 //APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initGameConfig, pushing window: %p", window);
  window_stack_push(window, animated);
 // APP_LOG(APP_LOG_LEVEL_DEBUG, "Done pushing window");
}











static void deinit(void) {
  window_destroy(window);
    if(event_timer != NULL) {
    // Cancel any Timer
    app_timer_cancel(event_timer);
    event_timer = NULL;
  }
}

int main(void) {
  int i = 0;
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);
  
  app_event_loop();
  gbitmap_destroy(parallax);
  gbitmap_destroy(player_bmp);
  
  /*
  for(i = 0; i < 256; i++)
  {
    if(tiles[i] != NULL)
    {
       gbitmap_destroy(tiles[i]);
    }
  }  */

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Pre store!");
  storeGameState();
   APP_LOG(APP_LOG_LEVEL_DEBUG, "Game ending!");
  deinit();
}
