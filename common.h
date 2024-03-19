#pragma once

#define SCREEN_WIDTH	1280				//横の長さ
#define SCREEN_HEIGHT	720					//縦の長さ

#define FUNC_ERROR	-1						//エラー

//モデルのファイルパス
/**********キャラクター**********/
#define RAPI	"Character/Nikke-Rapi/nikke.pmx"					//ラピのファイルパス
#define	ANIS	"Character/Anis.fbm/Anis-Apose.pmx"					//アニスのファイルパス
#define SCARLET	"Character/NIKKE-Hongryeon/Hongryeon-mmd.pmx"		//紅蓮のファイルパス
/**********武器**********/
#define DESERT_EAGLE	"Weapon/DesertEagle_MMD/DesertEagle.pmx"	//デザートイーグルのファイルパス
#define SWORD	"Weapon/Sword.mv1"									//剣のファイルパス

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

//ベクトルの乗算
inline VECTOR VMult(const VECTOR& vec1, const VECTOR& vec2)
{
    VECTOR ret = {};

    ret.x = vec1.x * vec2.x;
    ret.y = vec1.y * vec2.y;
    ret.z = vec1.z * vec2.z;

    return ret;
}

//ベクトルの除算
inline VECTOR VDiv(const VECTOR& vec1, const VECTOR& vec2)
{
    VECTOR ret = {};

    ret.x = vec1.x / vec2.x;
    ret.y = vec1.y / vec2.y;
    ret.z = vec1.z / vec2.z;

    return ret;
}

//ベクトルの内積の加算
inline float VDotAdd3(const VECTOR& separateAxis, const VECTOR& e1, const VECTOR& e2, const VECTOR& e3 = {0,0,0})
{
    // 3つの内積の絶対値の和で投影線分長を計算
   // 分離軸seprateAxisは標準化されていること
    float r1 = fabs(VDot(separateAxis, e1));
    float r2 = fabs(VDot(separateAxis, e2));
    float r3 = &e3 ? (fabs(VDot(separateAxis, e3))) : 0;
    return r1 + r2 + r3;
}