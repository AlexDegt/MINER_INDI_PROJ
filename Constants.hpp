#pragma once

#include <iostream>
#include <string>
#include <assert.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include <Destination.hpp>

#define NUM_OF_ITEMS_ON_SCREEN 3
#define NUM_OF_PICTURES_ON_SCREEN 4

#define DECREMENT 16000
#define INDENT 20
#define CHARACTER_SIZE_WORD 40
#define OBJ_ARRAY_CAPACITY 85
#define PHYS_OBJ_ARRAY_CAPACITY 85
#define HEIGHT_MAP_1 11
#define WIDHT_MAP_1 40
#define CHAR_SPEED 5
#define ZOOM_VALUE 10
#define DELTA_DIMENSION_INC 200
#define DELTA_DIMENSION_DEC 500
#define DIMENSION_SCREEN_X 640
#define DIMENSION_SCREEN_Y 480
#define COEFF_SPEED 0.2
#define COEFF_ATTACK_SPEED 0.2
#define MAP_TILESET_WIDHT 32
#define DISTANCE 20
#define IS_FIGHTING 1
#define IS_RUNNING 1
#define DAMAGE_BULLET 10
#define ACCELERATION 4
#define COLLIS_CORRECTION 20

enum DIRECTION
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum TYPESOFBUTTONINMAINWINDOW
{
    PLAY = 1,
    GO_TO_NEXT_LEVEL_OF_OPTIONS,
    EXIT
};

enum TYPESOFBUTTON
{
    OPTION1 = 1,
    OPTION2,
    BACK
};

enum WINDOW
{
    CLOSED_WINDOW = -1,
    LAUNCH_WINDOW, // game window
    FIRST_LEVEL_OF_OPTIONS, // first level - start
    SECOND_LEVEL_OF_OPTIONS, // second level
    THIRD_LEVEL_OF_OPTIONS // third level - finish
    
};

enum LAUNCH
{
    NOTENDOFLAUNCH = 0,
    ENDOFLAUNCH_SECCESS,
    ENDOFLAUNCH_CLOSED
};
