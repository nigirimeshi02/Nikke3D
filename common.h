#pragma once

#define SCREEN_WIDTH	1280				//横の長さ
#define SCREEN_HEIGHT	720					//縦の長さ

#define FuncError	-1

//モデルのファイルパス
/**********キャラクター**********/
#define Rapi	"Character/Nikke-Rapi/nikke.pmx"				//ラピのファイルパス
#define	Anis	"Character/Anis.fbm/Anis-Apose.pmx"				//アニスのファイルパス
/**********武器**********/
#define DesertEagle	"Weapon/DesertEagle_MMD/DesertEagle.pmx"	//デザートイーグルのファイルパス
#define Sword	"Weapon/Sword.mv1"								//剣のファイルパス

//カメラ水平角度が0度が720度のため
#define CAMERA_ANGLE_0			720							//0度
#define CAMERA_ANGLE_90			CAMERA_ANGLE_0 + 90			//90度
#define CAMERA_ANGLE_180		CAMERA_ANGLE_0 + 180		//180度
#define CAMERA_ANGLE_270		CAMERA_ANGLE_0 + 270		//270度
#define CAMERA_ANGLE_360		CAMERA_ANGLE_0 + 360		//360度

#define _USE_MATH_DEFINES
#include<math.h>

#define d_r(_d) _d * (M_PI / 180)	//dからr
#define r_d(_r) _r * (180 / M_PI)	//rからd

#include"DxLib.h"
#include"../../InputControl/Key/KeyInput.h"
#include"../../InputControl/Pad/PadInput.h"

#include<map>			//連想配列
#include<string>		//文字列操作
#include<sstream>		//文字列変換
#include<fstream>		//ファイル操作