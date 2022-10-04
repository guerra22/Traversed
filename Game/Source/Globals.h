#pragma once
#include <windows.h>
#include <stdio.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define PI 3.1415926535898f
#define SQUARETOCIRCLE 0.7853981f

#define PIXELS_PER_METERS 10.0f
#define METERS_PER_PIXELS 1.0f/PIXELS_PER_METERS

#define METERS_TO_PIXELS(x) ((int) floor(x * PIXELS_PER_METERS))
#define PIXELS_TO_METERS(x) ((float)(x * METERS_PER_PIXELS))

typedef unsigned int uint;

enum UpdateStatus
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

#define IN_RANGE( value, min, max ) ( ((value) >= (min) && (value) <= (max)) ? 1 : 0 )
#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define TO_BOOL( a )  ( (a != 0) ? true : false )



// Deletes a buffer
#define RELEASE( x ) \
    {                        \
    if( x != NULL )        \
        {                      \
      delete x;            \
      x = NULL;              \
        }                      \
    }

// Configuration -----------
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 758
#define SCREEN_SIZE 1
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE false
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "Physic Engine"