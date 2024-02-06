#pragma once

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define _USE_MATH_DEFINES
#include<math.h>

#define d_r(_d) _d * (M_PI / 180)	//d‚©‚çr
#define r_d(_r) _r * (180 / M_PI)	//r‚©‚çd

#include"DxLib.h"
#include"../../InputControl/Key/KeyInput.h"
#include"../../InputControl/Pad/PadInput.h"
