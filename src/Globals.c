#include <pebble.h>

#include "Globals.h"


//can be changed for difficulty
char highest_segment = 5;
char lowest_segment = 0;

float speed_up = 1.0;

float TILE_SCROLL_SPEED = 4;


float offset_x = 0;
float offset_parallax = 0;
int is_left_segment = 0;

char moving_platform_count = 50;

float player_x_pos = 0;
float player_y_pos = 0;
char is_select_pressed = 0;
char is_down_pressed = 0;
char is_up_pressed = 0;

float player_velocity_y = 0;
float gravity_acceleration = 1;
char jump_count = 0;
float jump_velocity = -10;

char segment_left = 0;
char segment_right = 0;
char current_parallax = 0;
int parallax_repeat_count = 0;
float score_cnt = 0;