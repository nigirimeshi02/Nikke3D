#pragma once

#define SCREEN_WIDTH	1280				//���̒���
#define SCREEN_HEIGHT	720					//�c�̒���

//�J���������p�x��0�x��720�x�̂���
#define CAMERA_ANGLE_0			720							//0�x
#define CAMERA_ANGLE_90			CAMERA_ANGLE_0 + 90			//90�x
#define CAMERA_ANGLE_180		CAMERA_ANGLE_0 + 180		//180�x
#define CAMERA_ANGLE_270		CAMERA_ANGLE_0 + 270		//270�x
#define CAMERA_ANGLE_360		CAMERA_ANGLE_0 + 360		//360�x

#define _USE_MATH_DEFINES
#include<math.h>

#include"DxLib.h"
#include"../../InputControl/Key/KeyInput.h"
#include"../../InputControl/Pad/PadInput.h"