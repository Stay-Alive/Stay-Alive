#ifndef CONFIG_HPP
#define CONFIG_HPP

#define DEBUG 1
// window
#define FULLSCREEN 0
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define ASPECT WINDOW_WIDTH * 1.0 / WINDOW_HEIGHT
// resources
#define WINDOW_TITLE "Stay Alive"
#define SHADERS_DIR "./shaders/"
#define TEXTURES_DIR "./textures/"
#define MODELS_DIR "./models/"
// perspective
#define FIELD_OF_VIEW 70.0f
#define Z_NEAR 0.1f
#define Z_FAR 1000.0f
// light
#define LIGHT_HEIGHT 800.0f
#define SKY_R 0.2f
#define SKY_G 0.4f
#define SKY_B 0.6f
#define PI 3.14f
#define SKY_SIZE 1200.0f
#define SKY_VERTEX_COUNT 256  // @NOTE 512 will make FPS < 60
#define SKY_STEP SKY_SIZE / (SKY_VERTEX_COUNT - 1)
#define SKY_HEIGHT_SCALE 0.0f
// camera
#define YOUR_HEIGHT 5.0f
// terrian
#define TERRAIN_SIZE 1200.0f
#define TERRAIN_VERTEX_COUNT 256  // @NOTE 512 will make FPS < 60
#define TERRAIN_STEP TERRAIN_SIZE / (TERRAIN_VERTEX_COUNT - 1)
#define TERRAIN_HEIGHT_SCALE 15.0f
// font
#define FONT_SIZE 12.0f
// game
#define GAME_START 0
#define GAME_RUNNING 1
#define GAME_OVER 2
#define GAME_NEAR_WIN 3
#define GAME_WIN 4
#define STATUS_STRING_LENGTH 50
#define DELTA_ENERGY 1
#define LIFE_TREE_COVER_RADIUS 50

//time
#define CLOKC_HOUR 0.5
//sky
#define SKY_COUNT 512*3
#define SKY_DATA_SIZE 12288

// random entities
#define ENTITY_POS_MAX_X TERRAIN_SIZE * 3 / 4
#define ENTITY_POS_MAX_Z TERRAIN_SIZE * 3 / 4
#endif
