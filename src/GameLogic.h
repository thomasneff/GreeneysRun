#ifndef GLOG
  #define GLOG
unsigned int getTileCoordinateX(int x_pos);
int getTileCoordinateY(int y_pos);
void initGameConfig();
void insertMovingPlatform(int x, int y, int dist_x, int dist_y, int velocity_x, int velocity_y);
void offsetMovingPlatforms();
void patchSegment(int segment_number, int offset);
void patchSegmentNoMovingPlatforms(int segment_number, int offset);
void move_platforms_x();
void move_platforms_y();
void do_jump();
char getRandomSegmentNumber();
void game_logic();
char *itoa10 (int value, char *result);
void sendTimeLineHighScore(int high_score);
#endif