#include <pebble.h>
#include "GameLogic.h"
#include "Globals.h"
#include "Collision.h"
#include "ResourceIO.h"

int getTileCoordinateY(int y_pos)
{
  
  if (y_pos / TILE_SIZE >= NUM_TILES_HIGH)
    return NUM_TILES_HIGH -1;
  
  return y_pos / TILE_SIZE;
}

void sendTimeLineHighScore(int high_score)
{
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  if (!iter) {
    // Error creating outbound message
    return;
  }

  int value = high_score;
  dict_write_int(iter, 0, &value, sizeof(int), true);
  dict_write_end(iter);
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Pre sending app msg!");
  app_message_outbox_send();
}

unsigned int getTileCoordinateX(int x_pos)
{

  unsigned int tmp_x = (x_pos / TILE_SIZE);

  while(tmp_x >= MAP_WIDTH_TILES)
    tmp_x -=MAP_WIDTH_TILES;

  return tmp_x;
}

void initGameConfig()
{
  char save_flag = 0;
  memset(text_buf, 0, 50);
  memset(score_buf, 0, 20);
  prev_high_score = loadHighScore();
  if(state == RUNNING)
  {
    state = GAME_OVER;
    //prev_high_score = loadHighScore();
    prev_score = score_cnt;
    if(prev_high_score < score_cnt)
    {
      storeHighScore(score_cnt);
      
      prev_high_score = score_cnt;
       sendTimeLineHighScore(score_cnt);
    }
    
    
   
      persist_write_data(PERSIST_KEY_SAVED_FLAG, &save_flag, sizeof(save_flag));
    layer_mark_dirty((Layer*)bitmap_layer); //render gameover
    return;
  }  
  srand(time(NULL));
  timer_cnt = 0;
  player_x_pos = 20;
  player_y_pos = 70;
  offset_x = 0;
  speed_up = 1;
  is_left_segment = 0;
  player_velocity_y = 0;
  current_parallax = 0;
  parallax_switch = 0;
  parallax_switch_flag = 0;
  score_cnt = 0;
  current_tileset = 0;
  difficulty = 0;
  calcSegmentBounds();
  parallax_repeat_count = 0;
  loadTileSet(current_tileset);
   //TODO: parallaxes need to be hand-assigned...

  setParallax(0);

  //setRightParallax(1);
  #ifdef PBL_COLOR 
       
  
      // parallax2 = gbitmap_create_with_resource(RESOURCE_ID_PARALLAX1);
  #else
    parallax = gbitmap_create_with_resource(RESOURCE_ID_WHITE);
   
  #endif
  
  memset(moving_platforms, 0, sizeof(moving_platforms));
   int i = 0;
  for(i = 0; i < moving_platform_count; i++)
  {
    moving_platforms[i].is_active = 0;
  }
  
//   APP_LOG(APP_LOG_LEVEL_DEBUG, "Done setting moving platforms");
  patchSegment(200,0);
  patchSegment(getRandomSegmentNumber(),1);
  // APP_LOG(APP_LOG_LEVEL_DEBUG, "Done patching segments");
  offsetMovingPlatforms();
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "Done offsetting platforms");
}

void insertMovingPlatform(int x, int y, int dist_x, int dist_y, int velocity_x, int velocity_y)
{
    int i = 0;
  
  for(i = 0; i < moving_platform_count; i++)
          {
            if(!moving_platforms[i].is_active)
            {
               MovingPlatform new_platform;
               new_platform.x_pos_start = x * TILE_SIZE;
               new_platform.x_pos_dest = x * TILE_SIZE + dist_x;
               new_platform.y_pos_start = y * TILE_SIZE;
               new_platform.y_pos_dest = new_platform.y_pos_start + dist_y;
               new_platform.is_active = 1;
               new_platform.velocity_x = velocity_x;
               new_platform.velocity_y = velocity_y;
               new_platform.x_pos = new_platform.x_pos_start;
               new_platform.y_pos = new_platform.y_pos_start;
               moving_platforms[i] = new_platform;

               break;
            }
          }
}


void offsetMovingPlatforms()
{
    int i = 0;
  
  for(i = 0; i < moving_platform_count; i++)
          {
            if(moving_platforms[i].is_active && moving_platforms[i].x_pos_start >= MAP_WIDTH_TILES*TILE_SIZE)
            {
               
               moving_platforms[i].x_pos_start -= MAP_WIDTH_TILES*TILE_SIZE;
               moving_platforms[i].x_pos_dest -= MAP_WIDTH_TILES*TILE_SIZE;
               moving_platforms[i].x_pos -= MAP_WIDTH_TILES*TILE_SIZE;

            }
          }
  
}

void patchSegmentNoMovingPlatforms(int segment_number, int offset)
{
  int x = 0;
  int y = 0;
  
  int offsetIdx = 0;

  if(offset)
  {
    segment_right = segment_number;
    offsetIdx = SEGMENT_WIDTH_TILES;

  }  
  else
  {
    segment_left = segment_number;  
  }
    
  loadSegment(segment_number);
  for(x = offsetIdx; x < SEGMENT_WIDTH_TILES + offsetIdx; x++)
  {
    for(y = 0; y < NUM_TILES_HIGH; y++)
    {
      
      if(segment[y][x - offsetIdx] >= 0)
        tile_map[y][x] = segment[y][x - offsetIdx];
      else
      {
        tile_map[y][x] = 0;
      }
    }

  }
}

void patchSegment(int segment_number, int offset)
{

  int x = 0;
  int y = 0;
  
  int offsetIdx = 0;
  int offsetmovingplatforms = MAP_WIDTH_TILES;
  if(offset)
  {
    segment_right = segment_number;
    offsetIdx = SEGMENT_WIDTH_TILES;
    offsetmovingplatforms = 0;
  }  
  else
  {
    segment_left = segment_number;  
  }
    
  loadSegment(segment_number);
  for(x = offsetIdx; x < SEGMENT_WIDTH_TILES + offsetIdx; x++)
  {
    for(y = 0; y < NUM_TILES_HIGH; y++)
    {
      
      if(segment[y][x - offsetIdx] >= 0)
        tile_map[y][x] = segment[y][x - offsetIdx];
      else
      {
        tile_map[y][x] = 0;
   
        if(segment[y][x - offsetIdx] == -1)
        {
          insertMovingPlatform(x + offsetmovingplatforms, y, 0, -3*TILE_SIZE, 0, -2);
        }
      }
    }

  }



}



void move_platforms_x()
{
  int i = 0;
  
  for(i = 0; i < moving_platform_count; i++)
  {
    
       if(!moving_platforms[i].is_active)
      continue;
    
    if(moving_platforms[i].x_pos_start ==  moving_platforms[i].x_pos_dest)
      continue;
     moving_platforms[i].x_pos += moving_platforms[i].velocity_x  * speed_up;
    if(moving_platforms[i].x_pos_start <  moving_platforms[i].x_pos_dest)
    {
       
      if(moving_platforms[i].x_pos >= moving_platforms[i].x_pos_dest)
      {
        int tmp = moving_platforms[i].x_pos_dest;
        moving_platforms[i].x_pos_dest = moving_platforms[i].x_pos_start;
        moving_platforms[i].x_pos_start = tmp;
        moving_platforms[i].velocity_x *=-1;
      }
    }
     
    if(moving_platforms[i].x_pos_start > moving_platforms[i].x_pos_dest)
    {
       
      if(moving_platforms[i].x_pos <= moving_platforms[i].x_pos_dest)
      {
       int tmp = moving_platforms[i].x_pos_dest;
        moving_platforms[i].x_pos_dest = moving_platforms[i].x_pos_start;
        moving_platforms[i].x_pos_start = tmp;
        moving_platforms[i].velocity_x *=-1;
      }
    }
  }
}

/* simple base 10 only itoa */
char *itoa10 (int value, char *result)
{
    char const digit[] = "0123456789";
    char *p = result;
    if (value < 0) {
        *p++ = '-';
        value *= -1;
    }

    /* move number of required chars and null terminate */
    int shift = value;
    do {
        ++p;
        shift /= 10;
    } while (shift);
    *p = '\0';

    /* populate result in reverse order */
    do {
        *--p = digit [value % 10];
        value /= 10;
    } while (value);

    return result;
}

void move_platforms_y()
{
  int i = 0;
  
  for(i = 0; i < moving_platform_count; i++)
  {
       if(!moving_platforms[i].is_active)
      continue;
    
    if(moving_platforms[i].y_pos_start ==  moving_platforms[i].y_pos_dest)
      continue;
     moving_platforms[i].y_pos += moving_platforms[i].velocity_y  * speed_up;
    if(moving_platforms[i].y_pos_start <  moving_platforms[i].y_pos_dest)
    {
       
      if(moving_platforms[i].y_pos >= moving_platforms[i].y_pos_dest)
      {
       int tmp = moving_platforms[i].y_pos_dest;
        moving_platforms[i].y_pos_dest = moving_platforms[i].y_pos_start;
        moving_platforms[i].y_pos_start = tmp;
        moving_platforms[i].velocity_y *=-1;
      }
    }
     
    if(moving_platforms[i].y_pos_start > moving_platforms[i].y_pos_dest)
    {
       
      if(moving_platforms[i].y_pos <= moving_platforms[i].y_pos_dest)
      {
       int tmp = moving_platforms[i].y_pos_dest;
        moving_platforms[i].y_pos_dest = moving_platforms[i].y_pos_start;
        moving_platforms[i].y_pos_start = tmp;
        moving_platforms[i].velocity_y *=-1;
      }
    }
  }
}


void do_jump()
{
  if(jump_count)
  {
    jump_count--;
    player_velocity_y = jump_velocity * speed_up;
  }
}



char getRandomSegmentNumber()
{
  
  return lowest_segment + rand() % (highest_segment - lowest_segment);
  
}

void game_logic()
{
 //int tmpdigit = 0;
   
  if(state != RUNNING)
    return;
  
   score_cnt+= (TILE_SCROLL_SPEED * speed_up*speed_up*speed_up*speed_up) * 0.7;
  timer_cnt++;
   strcpy(text_buf,"Score: ");
  uint16_t ms = 0;
  
  time_ms(NULL, &ms);
  int dif = (int)ms - (int)last_ms;
  if(dif < 0)
    dif = ms;
  last_ms = ms;

    /*
 tmpdigit = (int) speed_up;
   itoa10(tmpdigit, score_buf);
  strcat(text_buf, score_buf);
   strcat(text_buf, ".");
   tmpdigit = ((int) (speed_up * 10)) % 10;
   itoa10(tmpdigit, score_buf);
  strcat(text_buf, score_buf);
     tmpdigit = ((int) (speed_up * 100)) % 100;
   itoa10(tmpdigit, score_buf);
  strcat(text_buf, score_buf);
  strcat(text_buf,"x");*/
 //itoa10(dif, score_buf);
  //strcat(text_buf, score_buf);
  //strcat (text_buf, " / ");
  itoa10(score_cnt, score_buf);
  strcat(text_buf, score_buf);
  
  if(((int)timer_cnt) % 1000 == 0)
  {
    timer_cnt = 0;
    speed_up += 0.05;
    if(speed_up > SPEED_UP_LIMIT)
      speed_up = SPEED_UP_LIMIT;
  }
  
 
  
  move_platforms_y();
  while(collisionMovingPlatformY());
  
  
  
  
  
  
  player_velocity_y += gravity_acceleration * speed_up * speed_up;
  
  if(is_select_pressed || is_up_pressed)
  {
     do_jump();
  }
  
  if(player_velocity_y >= TILE_SIZE-2)
    player_velocity_y = (TILE_SIZE-2);
  
  signed int tmp = player_y_pos;
  tmp += player_velocity_y;
  
  if(tmp < 0)
  {
    player_velocity_y = 0;
    player_y_pos = 0;
  }  
  
  player_y_pos += player_velocity_y;
  
  
  
  
  if((player_y_pos) > WIN_HEIGHT)
   {
    initGameConfig();
   // strcpy(text_buf,"PYPOS: 3");
  } 
  
  
  while(collisionMovingPlatformY());
  while(collisionBot());
  
  collisionDeath();
  
  
  


  //if(player_x_pos < 0)
   // player_x_pos = 0;
  
  move_platforms_x();

  while(collisionMovingPlatformX());
  
  offset_x += TILE_SCROLL_SPEED * speed_up;
  offset_parallax += PARALLAX_SCROLL_SPEED * speed_up;
  if(offset_parallax >= PARALLAX_WIDTH)
    offset_parallax = 0;
  
 
  if(offset_x > PARALLAX_WIDTH && !parallax_switch_flag)
  {
    parallax_switch = !parallax_switch;
    parallax_switch_flag = 1;
    if(incrementParallaxIndex())
      setParallax(getParallaxIndex(0));
  }
  
  if(offset_x < PARALLAX_WIDTH && parallax_switch_flag)
  {
    parallax_switch_flag = 0;  
  }
  
  
  
  
  if((getTileCoordinateX(offset_x) >= SEGMENT_WIDTH_TILES) && !is_left_segment)
   {
      is_left_segment = 1;
      
      patchSegment(getRandomSegmentNumber(), !is_left_segment);
   }

  if((offset_x / TILE_SIZE > MAP_WIDTH_TILES + 1) && is_left_segment)
  {
    offset_x -= MAP_WIDTH_TILES * TILE_SIZE;
    offsetMovingPlatforms();
    is_left_segment = 0;
    patchSegment(getRandomSegmentNumber(), !is_left_segment);
  }
  while(collisionMovingPlatformX());
  collisionRight();
   
}