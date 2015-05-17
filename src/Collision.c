#include <pebble.h>
#include "Collision.h"
#include "Globals.h"
  #include "GameLogic.h"
int collisionBot()
{
  int right_x = player_x_pos + offset_x + PLAYER_SIZE;
  int left_x = player_x_pos + offset_x;
  int up_y = player_y_pos;
  int down_y = player_y_pos + PLAYER_SIZE;

  int tileLeftX = getTileCoordinateX(left_x);
  int tileRightX = getTileCoordinateX(right_x);
  int tileUpY = getTileCoordinateY(up_y);
  int tileDownY = getTileCoordinateY(down_y);
  
  int tileLeftX1 = getTileCoordinateX(left_x + TILE_SIZE);
  int tileRightX1 = getTileCoordinateX(right_x - TILE_SIZE);
  
   //bot
    if(tile_map[tileDownY][tileLeftX] > 0  && tile_map[tileDownY][tileLeftX] < POWER_JUMP_MIN)
     {
      //initGameConfig();
      jump_count = 1;
      player_velocity_y = 0;
      player_y_pos--;
   
      return 1;
    }
    
   if(tile_map[tileDownY][tileLeftX1] > 0  && tile_map[tileDownY][tileLeftX1] < POWER_JUMP_MIN)
     {
      //initGameConfig();
      jump_count = 1;
      player_velocity_y = 0;
      player_y_pos--;
     
      return 1;
    }
   

    //bot
    if(tile_map[tileDownY][tileRightX] > 0  && tile_map[tileDownY][tileRightX] < POWER_JUMP_MIN)
     {
      //initGameConfig();
      jump_count = 1;
      player_velocity_y = 0;
      player_y_pos--;
    
      return 1;
    }
   //bot
    if(tile_map[tileDownY][tileRightX1] > 0  && tile_map[tileDownY][tileRightX1] < POWER_JUMP_MIN)
     {
      //initGameConfig();
      jump_count = 1;
      player_velocity_y = 0;
      player_y_pos--;
    
      return 1;
    }

     //check top
    if(tile_map[tileUpY][tileLeftX] > 0  && tile_map[tileUpY][tileLeftX] < POWER_JUMP_MIN)
    {
      player_velocity_y = 0;
      player_y_pos++;
      
      return 1;
    }
    //check top
    if(tile_map[tileUpY][tileLeftX1] > 0  && tile_map[tileUpY][tileLeftX1] < POWER_JUMP_MIN)
    {
      player_velocity_y = 0;
      player_y_pos++;
    
      return 1;
    }

     //check top
    if(tile_map[tileUpY][tileRightX] > 0  && tile_map[tileUpY][tileRightX] < POWER_JUMP_MIN)
    {
      player_velocity_y = 0;
      player_y_pos++;
     
      return 1;
    }
    //check top
    if(tile_map[tileUpY][tileRightX1] > 0  && tile_map[tileUpY][tileRightX1] < POWER_JUMP_MIN)
    {
      player_velocity_y = 0;
      player_y_pos++;

      return 1;
    }
  return 0;
}

int collisionMovingPlatformY()
{
  int right_x = player_x_pos + offset_x + PLAYER_SIZE;
  int left_x = player_x_pos + offset_x;
  int up_y = player_y_pos;
  int down_y = player_y_pos + PLAYER_SIZE;

  int i = 0;
  
  for(i = 0; i < moving_platform_count; i++)
  {
       if(!moving_platforms[i].is_active)
      continue;
    for(left_x = player_x_pos + offset_x; left_x <= right_x; left_x += TILE_SIZE)
    {
       if((right_x >= moving_platforms[i].x_pos && right_x <= moving_platforms[i].x_pos + TILE_SIZE) ||
          (left_x >= moving_platforms[i].x_pos && left_x <= moving_platforms[i].x_pos + TILE_SIZE))
        {
          if(down_y >= moving_platforms[i].y_pos && down_y <= moving_platforms[i].y_pos + TILE_SIZE)  
          {
            jump_count = 1;
            player_velocity_y = 0;
            player_y_pos--;
            
            return 1;
          }
        }
    }
   
  }
   for(i = 0; i < moving_platform_count; i++)
  {
        if(!moving_platforms[i].is_active)
      continue;
    for(left_x = player_x_pos + offset_x; left_x <= right_x; left_x += TILE_SIZE)
    {
       if((right_x >= moving_platforms[i].x_pos && right_x <= moving_platforms[i].x_pos + TILE_SIZE) ||
          (left_x >= moving_platforms[i].x_pos && left_x <= moving_platforms[i].x_pos + TILE_SIZE))
        {
          if(up_y >= moving_platforms[i].y_pos && up_y <= moving_platforms[i].y_pos + TILE_SIZE)  
          {
            player_velocity_y = 0;
            player_y_pos++;
            
            return 1;
          }
        }
    }
   
  }
   
  return 0;
}

int collisionMovingPlatformX()
{
  int right_x = player_x_pos + offset_x + PLAYER_SIZE;
  int left_x = player_x_pos + offset_x;
  int up_y = player_y_pos;
  int down_y = player_y_pos + PLAYER_SIZE;


  int i = 0;
  
  for(i = 0; i < moving_platform_count; i++)
  {
    if(!moving_platforms[i].is_active)
      continue;
    for(left_x = player_x_pos + offset_x; left_x <= right_x; left_x += TILE_SIZE)
    {
       if((down_y >= moving_platforms[i].y_pos && down_y <= moving_platforms[i].y_pos + TILE_SIZE)  ||
          (up_y >= moving_platforms[i].y_pos && up_y <= moving_platforms[i].y_pos + TILE_SIZE))
        {
          if(right_x >= moving_platforms[i].x_pos && right_x <= moving_platforms[i].x_pos + TILE_SIZE)  
          {
            initGameConfig();

            return 0;
          }
        }
    }
   
  }
  
   
  return 0;
}


int collisionRight()
{
  int right_x = player_x_pos + offset_x + PLAYER_SIZE;
  int left_x = player_x_pos + offset_x;
  int up_y = player_y_pos;
  int down_y = player_y_pos + PLAYER_SIZE;

  int tileLeftX = getTileCoordinateX(left_x);
  int tileRightX = getTileCoordinateX(right_x);
  int tileUpY = getTileCoordinateY(up_y);
  int tileDownY = getTileCoordinateY(down_y);
  

    for(int i = tileUpY; i <= tileDownY; i++)
  {


    //right
    if(tile_map[i][tileRightX] > 0  && tile_map[i][tileRightX] < POWER_JUMP_MIN)
     {
      initGameConfig();
   
     // strcpy(text_buf,"CRight: 2");
      return 0;
    }
  
  }
  return 0;
}


void collisionDeath()
{
   int right_x = player_x_pos + offset_x + PLAYER_SIZE;
  int left_x = player_x_pos + offset_x;
  int up_y = player_y_pos;
  int down_y = player_y_pos + PLAYER_SIZE;

  int tileLeftX = getTileCoordinateX(left_x);
  int tileRightX = getTileCoordinateX(right_x);
  int tileUpY = getTileCoordinateY(up_y);
  int tileDownY = getTileCoordinateY(down_y-1);
  int tmpTile = 0;


    for(int i = tileUpY; i <= tileDownY; i++)
  {

      i++;
      if((tile_map[i][tileRightX] >= POWER_JUMP_MIN) &&  (tile_map[i][tileRightX] <= POWER_JUMP_MAX))
      {
        jump_count++;
        tile_map[i][tileRightX] = 0;
        
        
        tmpTile = getTileCoordinateX(right_x + TILE_SIZE);
        if((tile_map[i][tmpTile] >= POWER_JUMP_MIN) &&  (tile_map[i][tmpTile] <= POWER_JUMP_MAX))
        {
            tile_map[i][tmpTile] = 0;
        }
        if(i+1 < NUM_TILES_HIGH)
        {
            if((tile_map[i+1][tmpTile] >= POWER_JUMP_MIN) &&  (tile_map[i+1][tmpTile] <= POWER_JUMP_MAX))
            {
                tile_map[i+1][tmpTile] = 0;
            }
            
             if((tile_map[i+1][tileRightX] >= POWER_JUMP_MIN) &&  (tile_map[i+1][tileRightX] <= POWER_JUMP_MAX))
            {
                tile_map[i+1][tileRightX] = 0;
            }
        }
        if(i-1 >= 0)
        {
            if((tile_map[i-1][tmpTile] >= POWER_JUMP_MIN) &&  (tile_map[i-1][tmpTile] <= POWER_JUMP_MAX))
            {
                tile_map[i-1][tmpTile] = 0;
            }
            
             if((tile_map[i-1][tileRightX] >= POWER_JUMP_MIN) &&  (tile_map[i-1][tileRightX] <= POWER_JUMP_MAX))
            {
                tile_map[i-1][tileRightX] = 0;
            }
        }
        return;
      }
      
      i--;
    //right
    if(tile_map[i][tileRightX] >= DEATH_TILE_INDEX)
     {
      initGameConfig();
     // strcpy(text_buf,"CRight: 2");
  
      return;
    }
     
  }
  
     for(int i = tileLeftX; i <= tileRightX; i++)
  {
 
       
       if((tile_map[tileDownY][i] >= POWER_JUMP_MIN) &&  (tile_map[tileDownY][i] <= POWER_JUMP_MAX))
      {
        jump_count++;
        tile_map[tileDownY][i] = 0;
        tmpTile = getTileCoordinateX(tileDownY + TILE_SIZE);
        if((tile_map[tmpTile][i] >= POWER_JUMP_MIN) &&  (tile_map[tmpTile][i] <= POWER_JUMP_MAX))
        {
            tile_map[tmpTile][i] = 0;
        }
         if(i+1 < MAP_WIDTH_TILES)
        {
            if((tile_map[tmpTile][i+1] >= POWER_JUMP_MIN) &&  (tile_map[tmpTile][i+1] <= POWER_JUMP_MAX))
            {
                tile_map[tmpTile][i+1] = 0;
            }
            if((tile_map[tileDownY][i+1] >= POWER_JUMP_MIN) &&  (tile_map[tileDownY][i+1] <= POWER_JUMP_MAX))
            {
                tile_map[tileDownY][i+1] = 0;
            }
         }
         if(i-1 >= 0)
        {
            if((tile_map[tmpTile][i-1] >= POWER_JUMP_MIN) &&  (tile_map[tmpTile][i-1] <= POWER_JUMP_MAX))
          {
              tile_map[tmpTile][i-1] = 0;
          }
           if((tile_map[tileDownY][i-1] >= POWER_JUMP_MIN) &&  (tile_map[tileDownY][i-1] <= POWER_JUMP_MAX))
          {
              tile_map[tileDownY][i-1] = 0;
          }
         }
        return;
      }
       
        if((tile_map[tileUpY][i] >= POWER_JUMP_MIN) &&  (tile_map[tileUpY][i] <= POWER_JUMP_MAX))
      {
        jump_count++;
        tile_map[tileUpY][i] = 0;
        tmpTile = getTileCoordinateX(tileUpY - TILE_SIZE);
        if((tile_map[tmpTile][i] >= POWER_JUMP_MIN) &&  (tile_map[tmpTile][i] <= POWER_JUMP_MAX))
        {
            tile_map[tmpTile][i] = 0;
        }
         if(i+1 < MAP_WIDTH_TILES)
        {
            if((tile_map[tmpTile][i+1] >= POWER_JUMP_MIN) &&  (tile_map[tmpTile][i+1] <= POWER_JUMP_MAX))
            {
                tile_map[tmpTile][i+1] = 0;
            }
            if((tile_map[tileUpY][i+1] >= POWER_JUMP_MIN) &&  (tile_map[tileUpY][i+1] <= POWER_JUMP_MAX))
            {
                tile_map[tileUpY][i+1] = 0;
            }
         }
         if(i-1 >= 0)
        {
            if((tile_map[tmpTile][i-1] >= POWER_JUMP_MIN) &&  (tile_map[tmpTile][i-1] <= POWER_JUMP_MAX))
          {
              tile_map[tmpTile][i-1] = 0;
          }
           if((tile_map[tileUpY][i-1] >= POWER_JUMP_MIN) &&  (tile_map[tileUpY][i-1] <= POWER_JUMP_MAX))
          {
              tile_map[tileUpY][i-1] = 0;
          }
         }
        return;
      }

    if(tile_map[tileDownY][i] >= DEATH_TILE_INDEX)
     {
      initGameConfig();
  
      return;
    }
    
     if(tile_map[tileUpY][i] >= DEATH_TILE_INDEX)
     {
      initGameConfig();
      
      return;
    }
  }
  return;
  
}
