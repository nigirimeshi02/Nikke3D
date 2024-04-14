#pragma once

#define SCREEN_WIDTH	1280				//���̒���
#define SCREEN_HEIGHT	720					//�c�̒���

#define FUNC_ERROR  -1						//�G���[

#define X_AXIS_COLOR    0xff0000            //x���̐F
#define Y_AXIS_COLOR    0x00ff00            //y���̐F 
#define Z_AXIS_COLOR    0x0000ff            //z���̐F

//���f���̃t�@�C���p�X
/**********�L�����N�^�[**********/
#define RAPI	"Character/Nikke-Rapi/nikke.pmx"					//���s�̃t�@�C���p�X
#define	ANIS	"Character/Anis.fbm/Anis-Apose.pmx"					//�A�j�X�̃t�@�C���p�X
#define SCARLET	"Character/NIKKE-Hongryeon/Hongryeon-mmd.pmx"		//�g�@�̃t�@�C���p�X
/**********����**********/
#define DESERT_EAGLE	"Weapon/DesertEagle_MMD/DesertEagle.pmx"	//�f�U�[�g�C�[�O���̃t�@�C���p�X
#define SWORD	"Weapon/Sword.mv1"									//���̃t�@�C���p�X

#define MODEL_SCALE (model) model   //���f���̑傫��

//�J���������p�x��0�x��720�x�̂���
#define CAMERA_ANGLE_0			720							//0�x
#define CAMERA_ANGLE_90			CAMERA_ANGLE_0 + 90			//90�x
#define CAMERA_ANGLE_180		CAMERA_ANGLE_0 + 180		//180�x
#define CAMERA_ANGLE_270		CAMERA_ANGLE_0 + 270		//270�x
#define CAMERA_ANGLE_360		CAMERA_ANGLE_0 + 360		//360�x

#define _USE_MATH_DEFINES
#include<math.h>

#define d_r(_d) _d * (DX_PI_F / 180)	//d����r
#define r_d(_r) _r * (180 / DX_PI_F)	//r����d

#include"DxLib.h"

#include<map>			//�A�z�z��
#include<string>		//�����񑀍�
#include<sstream>		//������ϊ�
#include<fstream>		//�t�@�C������

//�x�N�g���̏�Z
inline VECTOR VMult(const VECTOR& vec1, const VECTOR& vec2)
{
    VECTOR ret = {};

    ret.x = vec1.x * vec2.x;
    ret.y = vec1.y * vec2.y;
    ret.z = vec1.z * vec2.z;

    return ret;
}

//�x�N�g���̏��Z
inline VECTOR VDiv(const VECTOR& vec1, const VECTOR& vec2)
{
    VECTOR ret = {};

    ret.x = vec1.x / vec2.x;
    ret.y = vec1.y / vec2.y;
    ret.z = vec1.z / vec2.z;

    return ret;
}

//�x�N�g���̓��ς̉��Z
inline float VDotAdd3(const VECTOR& separateAxis, const VECTOR& e1, const VECTOR& e2, const VECTOR& e3 = {0,0,0})
{
    // 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
   // ������seprateAxis�͕W��������Ă��邱��
    float r1 = fabs(VDot(separateAxis, e1));
    float r2 = fabs(VDot(separateAxis, e2));
    float r3 = &e3 ? (fabs(VDot(separateAxis, e3))) : 0;
    return r1 + r2 + r3;
}