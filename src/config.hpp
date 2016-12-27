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
// camera
#define YOUR_HEIGHT 5.0f
// terrian
#define TERRAIN_SIZE 1200.0f
#define TERRAIN_VERTEX_COUNT 400  // @NOTE 512 will make FPS < 60
#define TERRAIN_STEP TERRAIN_SIZE / (TERRAIN_VERTEX_COUNT - 1)
#define TERRAIN_HEIGHT_SCALE 15.0f

#endif
