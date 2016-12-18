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
#define FIELD_OF_VIEW 70
#define Z_NEAR 0.1
#define Z_FAR 1000.0
// light
#define LIGHT_HEIGHT 800.0
#define SKY_R 0.2
#define SKY_G 0.4
#define SKY_B 0.6
// camera
#define YOUR_HEIGHT 5.0
#endif
