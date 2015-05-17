#ifndef RESH
  #define RESH
  #include <pebble.h>
void loadSegment(int segment_number);
void initBitmaps();
void storeHighScore(int high_score);
int loadHighScore();
int getParallaxIndex(int left);
GBitmap* loadParallaxFromIndex(int index);
void setParallax(int index);
int incrementParallaxIndex();
void storeGameState();
void loadGameState();
void deletePersistentKeys();
void loadTileSet(int tileset);
void increaseDifficulty();
void calcSegmentBounds();
void increaseDifficultyForParallaxIndex(int index);
#endif