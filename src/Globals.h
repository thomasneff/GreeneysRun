
#include <pebble.h>
  
#ifndef GLOBA
  #define GLOBA
#define WIN_WIDTH 144
#define WIN_HEIGHT 144

//or 24?
#define TILE_SIZE 12 
#define PLAYER_SIZE 12
//about 30 fps
#define MILLISECONDS_PER_FRAME 33 

#define NUM_TILES_HIGH 12
#define NUM_TILES_WIDE 12

#define SEGMENT_WIDTH_TILES 56
#define MAP_WIDTH_TILES 112

#define PERSIST_HIGH_SCORE 1337
#define PARALLAX_REPEAT 2
#define MAX_PARALLAX_INDEX 8
#define SPEED_UP_LIMIT 2


//can be changed for difficulty
extern char highest_segment;
extern char lowest_segment;
char difficulty;

extern float speed_up;

extern float TILE_SCROLL_SPEED;
#define PARALLAX_SCROLL_SPEED 2
#define NUM_SEGMENTS 21
#define PARALLAX_WIDTH 415
#define PARALLAX_HEIGHT 152

//leaves 28 TILES for death tiles
#define DEATH_TILE_INDEX 100 
#define POWER_JUMP_MIN 90
#define POWER_JUMP_MAX 93

  
#define PERSIST_KEY_SAVED_FLAG 0
#define PERSIST_KEY_DIFFICULTY 1
#define PERSIST_KEY_SPEED_UP 2
#define PERSIST_KEY_OFFSET_X 3
#define PERSIST_KEY_OFFSET_PARALLAX 4
#define PERSIST_KEY_IS_LEFT_SEGMENT 5
#define PERSIST_KEY_SEGMENT_LEFT 6
#define PERSIST_KEY_SEGMENT_RIGHT 7
#define PERSIST_KEY_PARALLAX_SWITCH 8
#define PERSIST_KEY_PARALLAX_SWITCH_FLAG 9
#define PERSIST_KEY_CURRENT_PARALLAX 10
#define PERSIST_KEY_PLAYER_X_POS 11
#define PERSIST_KEY_PLAYER_Y_POS 12
#define PERSIST_KEY_PLAYER_VELOCITY_Y 13
#define PERSIST_KEY_JUMP_COUNT 14
#define PERSIST_KEY_SCORE_COUNT 15
#define PERSIST_KEY_TIMER_COUNT 16
#define PERSIST_KEY_GAME_STATE 17
#define PERSIST_KEY_CURRENT_TILESET 18
#define PERSIST_KEY_MOVING_PLATFORM_COUNT 999  
#define PERSIST_KEY_MOVING_PLATFORM_START 1000

  
char tile_map[NUM_TILES_HIGH][MAP_WIDTH_TILES];

extern float offset_x;
extern float offset_parallax;
extern int is_left_segment;

typedef struct _MovingPlatform_
{
  int x_pos_start;
  int x_pos_dest;
  int x_pos;
  char y_pos_start;
  char y_pos_dest;
  char y_pos;
  signed char velocity_x;
  signed char velocity_y;
  char is_active;
  char was_on_screen;
}MovingPlatform;

MovingPlatform moving_platforms[50];
extern char moving_platform_count;

signed char segment[NUM_TILES_HIGH][SEGMENT_WIDTH_TILES];
extern char segment_left;
extern char segment_right;

#define NUM_PARRALAX 12
GBitmap *parallax;
GBitmap *title_screen;
char parallax_switch;
char parallax_switch_flag;
int prev_high_score;
int prev_score;


extern char current_parallax;

Window *window;
BitmapLayer *bitmap_layer;

#define RENDER_OFFSET_Y 8

#ifdef PBL_COLOR
StatusBarLayer *status_bar;
#define OFFSET_Y 16
#else
#define OFFSET_Y 0
#endif
TextLayer *text_layer;
AppTimer *event_timer;
GBitmap *player_bmp;
extern float player_x_pos;
extern float player_y_pos;
extern char is_select_pressed;
extern char is_down_pressed;
extern char is_up_pressed;

extern float player_velocity_y;
extern float gravity_acceleration;
extern char jump_count;
extern float jump_velocity;

typedef enum {TITLE_SCREEN, PAUSED, RUNNING, GAME_OVER} GameState;

GameState state;

GBitmap* tiles[256];

char text_buf[50];
char score_buf[20];
int timer_cnt;
float score_cnt;
extern int parallax_repeat_count;
uint16_t last_ms;
extern float score_cnt;
char current_tileset;
#endif
