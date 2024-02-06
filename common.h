#pragma once

#define SCREEN_WIDTH	1280				//横の長さ
#define SCREEN_HEIGHT	720					//縦の長さ

//カメラ水平角度が0度が720度のため
#define CAMERA_ANGLE_0			720							//0度
#define CAMERA_ANGLE_90			CAMERA_ANGLE_0 + 90			//90度
#define CAMERA_ANGLE_180		CAMERA_ANGLE_0 + 180		//180度
#define CAMERA_ANGLE_270		CAMERA_ANGLE_0 + 270		//270度
#define CAMERA_ANGLE_360		CAMERA_ANGLE_0 + 360		//360度

#define _USE_MATH_DEFINES
#include<math.h>

#include"DxLib.h"
#include"../../InputControl/Key/KeyInput.h"
#include"../../InputControl/Pad/PadInput.h"