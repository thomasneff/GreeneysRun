#include <pebble.h>
#include "ResourceIO.h"
#include "Globals.h"
#include "GameLogic.h"
void loadSegment(int segment_number)
{
  ResHandle handle;
  size_t res_size;

  switch(segment_number)
  {
    case 0: handle = resource_get_handle(RESOURCE_ID_seg_0_0); break;
    case 1: handle = resource_get_handle(RESOURCE_ID_seg_0_1); break;
    case 2: handle = resource_get_handle(RESOURCE_ID_seg_0_2); break;
    case 3: handle = resource_get_handle(RESOURCE_ID_seg_0_3); break;
    case 4: handle = resource_get_handle(RESOURCE_ID_seg_0_4); break;
    case 5: handle = resource_get_handle(RESOURCE_ID_seg_0_5); break;
    case 6: handle = resource_get_handle(RESOURCE_ID_seg_1_0); break;
    case 7: handle = resource_get_handle(RESOURCE_ID_seg_1_1); break;
    case 8: handle = resource_get_handle(RESOURCE_ID_seg_1_2); break;
    case 9: handle = resource_get_handle(RESOURCE_ID_seg_1_3); break;
    case 10: handle = resource_get_handle(RESOURCE_ID_seg_1_4); break;
    case 11: handle = resource_get_handle(RESOURCE_ID_seg_1_5); break;
    case 12: handle = resource_get_handle(RESOURCE_ID_seg_1_6); break;
    case 13: handle = resource_get_handle(RESOURCE_ID_seg_1_7); break;
    case 14: handle = resource_get_handle(RESOURCE_ID_seg_1_8); break;
    case 15: handle = resource_get_handle(RESOURCE_ID_seg_2_0); break;
    case 16: handle = resource_get_handle(RESOURCE_ID_seg_2_1); break;
    case 17: handle = resource_get_handle(RESOURCE_ID_seg_2_2); break;
    case 18: handle = resource_get_handle(RESOURCE_ID_seg_2_3); break;
    case 19: handle = resource_get_handle(RESOURCE_ID_seg_2_4); break;
    case 20: handle = resource_get_handle(RESOURCE_ID_seg_2_5); break;
    default: handle = resource_get_handle(RESOURCE_ID_seg_tileset_floor); break;
  }
  
  res_size = resource_size(handle);
  
  resource_load(handle, (uint8_t*)segment, res_size);
}

void storeHighScore(int high_score)
{
  persist_write_int(PERSIST_HIGH_SCORE, high_score);
}

int loadHighScore()
{
  return persist_read_int(PERSIST_HIGH_SCORE);
}


int getParallaxIndex(int left)
{
    return current_parallax;
}
void setParallax(int index)
{
  
  increaseDifficultyForParallaxIndex(index);
  #ifdef PBL_COLOR
    
 
  if(parallax != NULL)
  {
    gbitmap_destroy(parallax);
    parallax = NULL;
  }  
  
  parallax = loadParallaxFromIndex(index);
  // parallax = gbitmap_create_with_resource(RESOURCE_ID_PARALLAX1);
   #endif
}

int incrementParallaxIndex()
{
  parallax_repeat_count++;
  if(parallax_repeat_count >= PARALLAX_REPEAT)
  {
    parallax_repeat_count = 0;
    current_parallax++;
    
    if(current_parallax > MAX_PARALLAX_INDEX)
      current_parallax = 0;
    return 1;
  }
  
  return 0;
}

void deletePersistentKeys()
{
  int mov_plat_idx = 0;
  persist_delete(PERSIST_KEY_SAVED_FLAG);
  persist_delete(PERSIST_KEY_DIFFICULTY);
  persist_delete(PERSIST_KEY_SPEED_UP);
  persist_delete(PERSIST_KEY_OFFSET_X);
  persist_delete(PERSIST_KEY_OFFSET_PARALLAX);
  persist_delete(PERSIST_KEY_IS_LEFT_SEGMENT);
  persist_delete(PERSIST_KEY_SEGMENT_LEFT);
  persist_delete(PERSIST_KEY_SEGMENT_RIGHT);
  persist_delete(PERSIST_KEY_PARALLAX_SWITCH);
  persist_delete(PERSIST_KEY_PARALLAX_SWITCH_FLAG);
  persist_delete(PERSIST_KEY_CURRENT_PARALLAX);
  persist_delete(PERSIST_KEY_PLAYER_X_POS);
  persist_delete(PERSIST_KEY_PLAYER_Y_POS);
  persist_delete(PERSIST_KEY_PLAYER_VELOCITY_Y);
  persist_delete(PERSIST_KEY_JUMP_COUNT);
  persist_delete(PERSIST_KEY_SCORE_COUNT);
  persist_delete(PERSIST_KEY_TIMER_COUNT);
  persist_delete(PERSIST_KEY_GAME_STATE);
  persist_delete(PERSIST_KEY_CURRENT_TILESET);
  persist_delete(PERSIST_KEY_MOVING_PLATFORM_COUNT);  
  for(mov_plat_idx = 0; mov_plat_idx < moving_platform_count; mov_plat_idx++)
  {
    persist_delete(PERSIST_KEY_MOVING_PLATFORM_START + mov_plat_idx);
  }
}
void storeGameState()
{

  char save_flag = 1;
  
  GameState pauseState = PAUSED;
  
  if(state == TITLE_SCREEN || state == GAME_OVER)
    return;
  
  persist_write_data(PERSIST_KEY_SAVED_FLAG, &save_flag, sizeof(save_flag));
  persist_write_data(PERSIST_KEY_DIFFICULTY, &difficulty, sizeof(difficulty));
  persist_write_data(PERSIST_KEY_SPEED_UP, &speed_up, sizeof(speed_up));
  persist_write_data(PERSIST_KEY_OFFSET_X, &offset_x, sizeof(offset_x));
  persist_write_data(PERSIST_KEY_OFFSET_PARALLAX, &offset_parallax, sizeof(offset_parallax));
  persist_write_data(PERSIST_KEY_IS_LEFT_SEGMENT, &is_left_segment, sizeof(is_left_segment));
  persist_write_data(PERSIST_KEY_SEGMENT_LEFT, &segment_left, sizeof(segment_left));
  persist_write_data(PERSIST_KEY_SEGMENT_RIGHT, &segment_right, sizeof(segment_right));
  persist_write_data(PERSIST_KEY_PARALLAX_SWITCH, &parallax_switch, sizeof(parallax_switch));
  persist_write_data(PERSIST_KEY_PARALLAX_SWITCH_FLAG, &parallax_switch_flag, sizeof(parallax_switch_flag));
  persist_write_data(PERSIST_KEY_CURRENT_PARALLAX, &current_parallax, sizeof(current_parallax));
  persist_write_data(PERSIST_KEY_PLAYER_X_POS, &player_x_pos, sizeof(player_x_pos));
  persist_write_data(PERSIST_KEY_PLAYER_Y_POS, &player_y_pos, sizeof(player_y_pos));
  persist_write_data(PERSIST_KEY_PLAYER_VELOCITY_Y, &player_velocity_y, sizeof(player_velocity_y));
  persist_write_data(PERSIST_KEY_JUMP_COUNT, &jump_count, sizeof(jump_count));
  persist_write_data(PERSIST_KEY_SCORE_COUNT, &score_cnt, sizeof(score_cnt));
  persist_write_data(PERSIST_KEY_TIMER_COUNT, &timer_cnt, sizeof(timer_cnt));
  persist_write_data(PERSIST_KEY_GAME_STATE, &pauseState, sizeof(state));
  persist_write_data(PERSIST_KEY_CURRENT_TILESET, &current_tileset, sizeof(current_tileset));
  persist_write_data(PERSIST_KEY_MOVING_PLATFORM_COUNT, &moving_platform_count, sizeof(moving_platform_count));
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Pre store movobj!");
  persist_write_data(PERSIST_KEY_MOVING_PLATFORM_START, &moving_platforms[0], sizeof(MovingPlatform)*12);
  persist_write_data(PERSIST_KEY_MOVING_PLATFORM_START + 1, &moving_platforms[12], sizeof(MovingPlatform)*12);
  persist_write_data(PERSIST_KEY_MOVING_PLATFORM_START + 2, &moving_platforms[24], sizeof(MovingPlatform)*12);
  persist_write_data(PERSIST_KEY_MOVING_PLATFORM_START + 3, &moving_platforms[36], sizeof(MovingPlatform)*12);
  persist_write_data(PERSIST_KEY_MOVING_PLATFORM_START + 4, &moving_platforms[48], sizeof(MovingPlatform)*2);
 /* persist_write_data(PERSIST_KEY_MOVING_PLATFORM_START + 5, &moving_platforms[60], sizeof(MovingPlatform)*12);
  persist_write_data(PERSIST_KEY_MOVING_PLATFORM_START + 6, &moving_platforms[72], sizeof(MovingPlatform)*12);
  persist_write_data(PERSIST_KEY_MOVING_PLATFORM_START + 7, &moving_platforms[84], sizeof(MovingPlatform)*12);
  persist_write_data(PERSIST_KEY_MOVING_PLATFORM_START + 8, &moving_platforms[96], sizeof(MovingPlatform)*4);*/
  
 
  
}

void loadGameState()
{
  char save_flag = 0;
  int mov_plat_idx = 0;
  persist_read_data(PERSIST_KEY_SAVED_FLAG, &save_flag, sizeof(save_flag));
  
  if(save_flag == 0)
    return;
  
  persist_read_data(PERSIST_KEY_DIFFICULTY, &difficulty, sizeof(difficulty));
  
  calcSegmentBounds();
  
  persist_read_data(PERSIST_KEY_SPEED_UP, &speed_up, sizeof(speed_up));
  persist_read_data(PERSIST_KEY_OFFSET_X, &offset_x, sizeof(offset_x));
  persist_read_data(PERSIST_KEY_OFFSET_PARALLAX, &offset_parallax, sizeof(offset_parallax));
  persist_read_data(PERSIST_KEY_IS_LEFT_SEGMENT, &is_left_segment, sizeof(is_left_segment));
  persist_read_data(PERSIST_KEY_SEGMENT_LEFT, &segment_left, sizeof(segment_left));
  persist_read_data(PERSIST_KEY_SEGMENT_RIGHT, &segment_right, sizeof(segment_right));
  persist_read_data(PERSIST_KEY_PARALLAX_SWITCH, &parallax_switch, sizeof(parallax_switch));
  persist_read_data(PERSIST_KEY_PARALLAX_SWITCH_FLAG, &parallax_switch_flag, sizeof(parallax_switch_flag));
  persist_read_data(PERSIST_KEY_CURRENT_PARALLAX, &current_parallax, sizeof(current_parallax));
  persist_read_data(PERSIST_KEY_PLAYER_X_POS, &player_x_pos, sizeof(player_x_pos));
  persist_read_data(PERSIST_KEY_PLAYER_Y_POS, &player_y_pos, sizeof(player_y_pos));
  persist_read_data(PERSIST_KEY_PLAYER_VELOCITY_Y, &player_velocity_y, sizeof(player_velocity_y));
  persist_read_data(PERSIST_KEY_JUMP_COUNT, &jump_count, sizeof(jump_count));
  persist_read_data(PERSIST_KEY_SCORE_COUNT, &score_cnt, sizeof(score_cnt));
  persist_read_data(PERSIST_KEY_TIMER_COUNT, &timer_cnt, sizeof(timer_cnt));
  persist_read_data(PERSIST_KEY_GAME_STATE, &state, sizeof(state));
  persist_read_data(PERSIST_KEY_MOVING_PLATFORM_COUNT, &moving_platform_count, sizeof(moving_platform_count));
  persist_read_data(PERSIST_KEY_CURRENT_TILESET, &current_tileset, sizeof(current_tileset));
  
  persist_read_data(PERSIST_KEY_MOVING_PLATFORM_START, &moving_platforms[0], sizeof(MovingPlatform)*12);
  persist_read_data(PERSIST_KEY_MOVING_PLATFORM_START + 1, &moving_platforms[12], sizeof(MovingPlatform)*12);
  persist_read_data(PERSIST_KEY_MOVING_PLATFORM_START + 2, &moving_platforms[24], sizeof(MovingPlatform)*12);
  persist_read_data(PERSIST_KEY_MOVING_PLATFORM_START + 3, &moving_platforms[36], sizeof(MovingPlatform)*12);
  persist_read_data(PERSIST_KEY_MOVING_PLATFORM_START + 4, &moving_platforms[48], sizeof(MovingPlatform)*2);
 /*  persist_read_data(PERSIST_KEY_MOVING_PLATFORM_START + 5, &moving_platforms[60], sizeof(MovingPlatform)*12);
 persist_read_data(PERSIST_KEY_MOVING_PLATFORM_START + 6, &moving_platforms[72], sizeof(MovingPlatform)*12);
  persist_read_data(PERSIST_KEY_MOVING_PLATFORM_START + 7, &moving_platforms[84], sizeof(MovingPlatform)*12);
  persist_read_data(PERSIST_KEY_MOVING_PLATFORM_START + 8, &moving_platforms[96], sizeof(MovingPlatform)*4);*/
  
  patchSegmentNoMovingPlatforms(segment_left, 0);
  patchSegmentNoMovingPlatforms(segment_right, 1);
  setParallax(current_parallax);
  loadTileSet(current_tileset);
}


void loadTileSet(int tileset)
{
  #ifdef PBL_COLOR
    
  gbitmap_destroy(tiles[2]);
  //gbitmap_destroy(tiles[3]);
  gbitmap_destroy(tiles[4]);
  gbitmap_destroy(tiles[5]);
  gbitmap_destroy(tiles[6]);
  gbitmap_destroy(tiles[7]);
  gbitmap_destroy(tiles[8]);
  gbitmap_destroy(tiles[9]);
  gbitmap_destroy(tiles[10]);
  gbitmap_destroy(tiles[11]);
  if(tileset == 0)
  {
    tiles[2] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile1);
    //tiles[3] =  gbitmap_create_with_resource(RESOURCE_ID_valleyTile2);
    tiles[3] = tiles[2];
    tiles[4] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile3);
    tiles[5] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile4);
    tiles[6] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile5);
    tiles[7] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile6);
    tiles[8] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile7);
    tiles[9] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile8);
    tiles[10] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile9);
    tiles[11] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile10);
  }
  else
  {
    tiles[2] = gbitmap_create_with_resource(RESOURCE_ID_desertTile1);
   // tiles[3] = gbitmap_create_with_resource(RESOURCE_ID_desertTile2);
    tiles[3] = tiles[2];
    tiles[4] = gbitmap_create_with_resource(RESOURCE_ID_desertTile3);
    tiles[5] = gbitmap_create_with_resource(RESOURCE_ID_desertTile4);
    tiles[6] = gbitmap_create_with_resource(RESOURCE_ID_desertTile5);
    tiles[7] = gbitmap_create_with_resource(RESOURCE_ID_desertTile6);
    tiles[8] = gbitmap_create_with_resource(RESOURCE_ID_desertTile7);
    tiles[9] = gbitmap_create_with_resource(RESOURCE_ID_desertTile8);
    tiles[10] = gbitmap_create_with_resource(RESOURCE_ID_desertTile9);
    tiles[11] = gbitmap_create_with_resource(RESOURCE_ID_desertTile10);
  }
  
    
  #endif
}
void calcSegmentBounds()
{
    highest_segment = 6 + difficulty * 7;
  if(highest_segment >= NUM_SEGMENTS)
    highest_segment = NUM_SEGMENTS;
  lowest_segment = 0 + difficulty / 4;
  if(lowest_segment >= 4)
    lowest_segment = 4;
}
void increaseDifficulty()
{
  difficulty++;
  calcSegmentBounds();
}
void increaseDifficultyForParallaxIndex(int index)
{
  switch(index)
    {   
      case 3: increaseDifficulty(); 
              return; 
      
      case 6: increaseDifficulty(); 
              return;
    
      default : return;
    }
}
GBitmap* loadParallaxFromIndex(int index)
  {
    
    if(current_tileset == 0 && index >=3 && index <=5)
    {
      current_tileset = 1;
      loadTileSet(current_tileset);
    }
     if(current_tileset == 1 && (index <3 || index >5))
    {
      current_tileset = 0;
      loadTileSet(current_tileset);
    }
    switch(index)
    {
      case 0: return gbitmap_create_with_resource(RESOURCE_ID_VALLEY) ;
      case 1: return gbitmap_create_with_resource(RESOURCE_ID_VALLEY_EVENING) ;
      case 2: return gbitmap_create_with_resource(RESOURCE_ID_VALLEY_NIGHT) ;
      case 3: return gbitmap_create_with_resource(RESOURCE_ID_DESERT) ;
      case 4: return gbitmap_create_with_resource(RESOURCE_ID_DESERT_EVENING) ;
      case 5: return gbitmap_create_with_resource(RESOURCE_ID_DESERT_NIGHT) ;
      case 6: return gbitmap_create_with_resource(RESOURCE_ID_WOODS) ;
      case 7: return gbitmap_create_with_resource(RESOURCE_ID_WOODS_EVENING) ;
      case 8: return gbitmap_create_with_resource(RESOURCE_ID_WOODS_NIGHT) ;
      default : return gbitmap_create_with_resource(RESOURCE_ID_VALLEY) ;
    }
    
  }

void initBitmaps()
{
  int tilecnt = 0;
  
  player_bmp = gbitmap_create_with_resource(RESOURCE_ID_Player);
  tiles[0] = NULL;//gbitmap_create_with_resource(RESOURCE_ID_redWall2);
  for(tilecnt = 0; tilecnt < 256; tilecnt++)
    tiles[tilecnt] = tiles[0];
  tiles[1] = gbitmap_create_with_resource(RESOURCE_ID_redWall2);
  
 // #ifdef PBL_COLOR
  tiles[2] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile1);
  tiles[3] = tiles[2];
  //tiles[3] =  gbitmap_create_with_resource(RESOURCE_ID_valleyTile2);
  tiles[4] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile3);
  tiles[5] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile4);
  tiles[6] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile5);
  tiles[7] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile6);
  tiles[8] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile7);
  tiles[9] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile8);
  tiles[10] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile9);
  tiles[11] = gbitmap_create_with_resource(RESOURCE_ID_valleyTile10);
//  #endif
  //tileID >= 200 -> death. see collisionDeath()
  tiles[100] = gbitmap_create_with_resource(RESOURCE_ID_lavaDeath2x1);
  tiles[101] = tiles[100];
  
  tiles[103] = gbitmap_create_with_resource(RESOURCE_ID_lavaDeath2x4);
  tiles[102] = tiles[103];
  tiles[POWER_JUMP_MIN] = gbitmap_create_with_resource(RESOURCE_ID_powerJump1);
  tiles[POWER_JUMP_MIN+1] = gbitmap_create_with_resource(RESOURCE_ID_powerJump2);
  tiles[POWER_JUMP_MAX-1] = gbitmap_create_with_resource(RESOURCE_ID_powerJump3);
  tiles[POWER_JUMP_MAX] = gbitmap_create_with_resource(RESOURCE_ID_powerJump4);
  parallax = gbitmap_create_with_resource(RESOURCE_ID_VALLEY);
  //title_screen = gbitmap_create_with_resource(RESOURCE_ID_TITLE_SCREEN);
    
  tiles[255] = gbitmap_create_with_resource(RESOURCE_ID_vertPlatform);
}