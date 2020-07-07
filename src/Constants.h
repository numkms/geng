#ifndef CONSTANTS_H 
#define CONSTANTS_H 
#include <string>
#include <SDL2/SDL.h>
#include <vector>
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

const unsigned int FPS = 60;
const unsigned int FRAME_TARGET_TIME = 1000 / FPS;

const std::string SCORE_FILE_PATH = "./score";

const SDL_Color WHITE_COLOR = {255, 255, 255, 255};
const SDL_Color GREEN_COLOR = {0, 255, 0, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255, 255};
const SDL_Color RED_COLOR = {255, 0, 0, 255};
const SDL_Color CIYAN_COLOR = {102, 205, 170, 255};
const SDL_Color REDWHITE_COLOR = {240, 128, 128, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0,255};
const SDL_Color PINK_COLOR = {255, 105, 180, 255};
const SDL_Color KHAKI_COLOR = {240, 230, 140, 255};
const SDL_Color LIGHTSEAGREEN_COLOR = {32, 178, 170, 255};
const SDL_Color GOLD_COLOR = {255,215,0,255};

const std::vector<SDL_Color> COLOR_PALLETE = {
        CIYAN_COLOR, 
        REDWHITE_COLOR,
        ORANGE_COLOR,
        PINK_COLOR,
        KHAKI_COLOR,
        LIGHTSEAGREEN_COLOR,
        GOLD_COLOR
};

enum CollisionType {
    NO, 
    PLAYER_ENEMY,
    PLAYER_PROJECTILE,
    ENEMY_PROJECTILE,
    PLAYER_VEGETATION,
    PLAYER_LEVEL_COMPLETE
};

enum LayerType {
    TILEMAP = 0,
    VEGETATION = 1,
    ENEMY = 2,
    PLAYER = 3,
    PROJECTILE = 4,
    UI = 5
};

const unsigned int NUM_LAYERS = 6;

const bool SETTING_IS_SOUND_ENABLED = true;
#endif