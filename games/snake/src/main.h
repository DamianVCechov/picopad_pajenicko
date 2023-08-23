// ****************************************************************************
//
//                                 Main code
//
// ****************************************************************************

#ifndef _MAIN_H
#define _MAIN_H

//Picopad specific libraries
#include "picopad.h"

// Sound files
#include "../snd/eat.h"

// Image files
#include "../img/snake.h"

// Definition of snake
#define WIDTH_SNAKE 80
#define HEIGHT_SNAKE 60
#define SNAKE_SIZE 4

// Sound definition
extern const u8 EatSnd[15781];

// Graphic definition
#define COL_BACKGROUND	RGBTO16(135, 165, 5)
#define COL_BODY        RGBTO16(33, 45, 22)

#endif // _MAIN_H
