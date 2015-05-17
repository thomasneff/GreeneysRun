#include <pebble.h>
#include "Rendering.h"
#include "Globals.h"
#include "GameLogic.h"
  
  
void draw_2px_border_text(GContext* ctx, char* text, int x, int y, int fontType)
{
  GFont font;
  if(!fontType)
    font = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  else
    font = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
      graphics_context_set_text_color(ctx, GColorBlack);
      
      graphics_draw_text(ctx, text, font, GRect(x, y + OFFSET_Y,144,42), GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);

      
    //  graphics_draw_text(ctx, text_buf, font, GRect(x, y + OFFSET_Y,144,20), GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
    graphics_draw_text(ctx, text, font, GRect(x, y -2 + OFFSET_Y,144,42), GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
  graphics_draw_text(ctx, text, font, GRect(x, y + 2 + OFFSET_Y,144,42), GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
     graphics_draw_text(ctx, text, font, GRect(x  -2, y + 0 + OFFSET_Y,144,42), GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
  //graphics_draw_text(ctx, text_buf, font, GRect(x  -2, y -2 + OFFSET_Y,144,20), GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
 // graphics_draw_text(ctx, text_buf, font, GRect(x  -2, y + 2 + OFFSET_Y,144,20), GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
     graphics_draw_text(ctx, text, font, GRect(x + 2, y + 0 + OFFSET_Y,144,42), GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
  //graphics_draw_text(ctx, text_buf, font, GRect(x + 2, y + 2 + OFFSET_Y,144,20), GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
  //graphics_draw_text(ctx, text_buf, font, GRect(x + 2,  y + 2 + OFFSET_Y,144,20), GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);
  

        graphics_context_set_text_color(ctx, GColorWhite);
 
    
      graphics_draw_text(ctx, text, font, GRect(x, y + OFFSET_Y,144,42), GTextOverflowModeWordWrap,GTextAlignmentCenter, NULL);

}
void draw_parallax(GContext* ctx)
{     int x = 0;
  int y = 0;
  
    #ifdef PBL_COLOR 
     graphics_draw_bitmap_in_rect(ctx, parallax, GRect(0 - ((int)offset_parallax) % PARALLAX_WIDTH, 0+ OFFSET_Y,PARALLAX_WIDTH, PARALLAX_HEIGHT));
    graphics_draw_bitmap_in_rect(ctx, parallax, GRect(PARALLAX_WIDTH - ((int)offset_parallax) % PARALLAX_WIDTH, 0+ OFFSET_Y, WIN_WIDTH, PARALLAX_HEIGHT));
  #else
 
  for(x = 0; x < WIN_WIDTH; x+=TILE_SIZE)
  {
    for(y = -TILE_SIZE; y < WIN_HEIGHT; y+=TILE_SIZE)
    {
        graphics_draw_bitmap_in_rect(ctx, parallax, GRect(x, y + OFFSET_Y+RENDER_OFFSET_Y, TILE_SIZE,TILE_SIZE));
    }
  }
  #endif
  
}

void draw_moving_platforms(GContext* ctx)
{
     int i = 0;
  for(i = 0; i < moving_platform_count; i++)
          {
            if(moving_platforms[i].is_active)
            {
    
              if(moving_platforms[i].x_pos - offset_x < -TILE_SIZE && moving_platforms[i].was_on_screen)
              {
                moving_platforms[i].is_active = 0;
                moving_platforms[i].was_on_screen = 0;
              }
               
               
               if((moving_platforms[i].x_pos - offset_x) >= -TILE_SIZE && moving_platforms[i].x_pos - offset_x <= WIN_WIDTH + TILE_SIZE)
               {
                 
                 graphics_draw_bitmap_in_rect(ctx, tiles[255], GRect(moving_platforms[i].x_pos - offset_x, moving_platforms[i].y_pos+ OFFSET_Y+RENDER_OFFSET_Y, TILE_SIZE,TILE_SIZE));
                 moving_platforms[i].was_on_screen = 1;
               }
              
              
            }
          }
}


void draw_state_ui(GContext* ctx)
{
 
  if(state == TITLE_SCREEN)
  {
  graphics_draw_bitmap_in_rect(ctx, title_screen, GRect(9, 9+ OFFSET_Y, WIN_WIDTH-18,WIN_HEIGHT-18));
    char tmp_buf[25];
    strcpy(tmp_buf,"High Score: "); 
    itoa10(prev_high_score, score_buf);
      strcat(tmp_buf, score_buf);
    draw_2px_border_text(ctx, tmp_buf, 0, WIN_HEIGHT-14, 1);
    
  }
  else if(state == GAME_OVER)
  {
    draw_2px_border_text(ctx, "GAME OVER", 0, WIN_HEIGHT/2 + WIN_HEIGHT/4 -10, 0);
    char tmp_buf[25];
    strcpy(tmp_buf,"High Score: "); 
    draw_2px_border_text(ctx,  tmp_buf, 0, 52, 0);
    
      strcpy(tmp_buf,"");
     itoa10(prev_high_score, score_buf);
      strcat(tmp_buf, score_buf);
     draw_2px_border_text(ctx,  tmp_buf, 0, 73, 0);
    
     strcpy(tmp_buf,"Score:");
  
  
    draw_2px_border_text(ctx,  tmp_buf, 0, 10, 0);
    
    strcpy(tmp_buf,"");
    
     itoa10(prev_score, score_buf);
      strcat(tmp_buf, score_buf);
    draw_2px_border_text(ctx,  tmp_buf, 0, 31, 0);
  }
  else if(state == PAUSED)
  {
    char tmp_buf[20];
    strcpy(tmp_buf, "Score: ");
     itoa10(score_cnt, score_buf);
      strcat(tmp_buf, score_buf);
    draw_2px_border_text(ctx, tmp_buf, 0, 0, 0);
    draw_2px_border_text(ctx, "PAUSED", 0, WIN_HEIGHT/2 -10, 0);
  }
  
  
}

void layer_update_proc(Layer* layer, GContext* ctx)
{
 

  int x = 0;
  int y = 0;
  #ifdef PBL_COLOR 
  graphics_context_set_compositing_mode(ctx, GCompOpSet);
  #endif
  draw_parallax(ctx);

  int mod_off = ((int)offset_x) % TILE_SIZE; //calc only once for performance
  for(x = 0; x < WIN_WIDTH + TILE_SIZE; x+=TILE_SIZE)
  {
    for(y = 0; y < WIN_HEIGHT; y+=TILE_SIZE)
    {
      
      
      int tileType = (int)tile_map[getTileCoordinateY(y)][getTileCoordinateX(x+offset_x)];
      if(tileType != 0)
        graphics_draw_bitmap_in_rect(ctx, tiles[tileType], GRect(x - mod_off, y + OFFSET_Y+RENDER_OFFSET_Y, TILE_SIZE,TILE_SIZE));
      
      if(y == 0)
      {
        if(tileType == 9)
          {
            graphics_draw_bitmap_in_rect(ctx, tiles[6], GRect(x - mod_off, y + OFFSET_Y+RENDER_OFFSET_Y - TILE_SIZE, TILE_SIZE,TILE_SIZE));
          }
        if(tileType == 11)
          {
            graphics_draw_bitmap_in_rect(ctx, tiles[4], GRect(x - mod_off, y + OFFSET_Y+RENDER_OFFSET_Y - TILE_SIZE, TILE_SIZE,TILE_SIZE));
          }
         if(tileType == 10)
          {
            graphics_draw_bitmap_in_rect(ctx, tiles[8], GRect(x - mod_off, y + OFFSET_Y+RENDER_OFFSET_Y - TILE_SIZE, TILE_SIZE,TILE_SIZE));
          }
         if(tileType == 4)
          {
            graphics_draw_bitmap_in_rect(ctx, tiles[4], GRect(x - mod_off, y + OFFSET_Y+RENDER_OFFSET_Y - TILE_SIZE, TILE_SIZE,TILE_SIZE));
          }
         if(tileType == 6)
          {
            graphics_draw_bitmap_in_rect(ctx, tiles[6], GRect(x - mod_off, y + OFFSET_Y+RENDER_OFFSET_Y - TILE_SIZE, TILE_SIZE,TILE_SIZE));
          }
         if(tileType == 8)
          {
            graphics_draw_bitmap_in_rect(ctx, tiles[8], GRect(x - mod_off, y + OFFSET_Y+RENDER_OFFSET_Y - TILE_SIZE, TILE_SIZE,TILE_SIZE));
          }
      }
      
    }
  }
  
  
     
      graphics_draw_bitmap_in_rect(ctx, player_bmp, GRect(player_x_pos, player_y_pos + OFFSET_Y+RENDER_OFFSET_Y, PLAYER_SIZE,PLAYER_SIZE));
  
      draw_moving_platforms(ctx);
  draw_2px_border_text(ctx, text_buf, 0, 0, 0);
      draw_state_ui(ctx);
  
}
