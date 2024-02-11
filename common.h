#pragma once

#define SCREEN_WIDTH	1280				//���̒���
#define SCREEN_HEIGHT	720					//�c�̒���

#define FUNC_ERROR	-1

//���f���̃t�@�C���p�X
/**********�L�����N�^�[**********/
#define RAPI	"Character/Nikke-Rapi/nikke.pmx"				//���s�̃t�@�C���p�X
#define	ANIS	"Character/Anis.fbm/Anis-Apose.pmx"				//�A�j�X�̃t�@�C���p�X
/**********����**********/
#define DESERT_EAGLE	"Weapon/DesertEagle_MMD/DesertEagle.pmx"	//�f�U�[�g�C�[�O���̃t�@�C���p�X
#define SWORD	"Weapon/Sword.mv1"								//���̃t�@�C���p�X

//�J���������p�x��0�x��720�x�̂���
#define CAMERA_ANGLE_0			720							//0�x
#define CAMERA_ANGLE_90			CAMERA_ANGLE_0 + 90			//90�x
#define CAMERA_ANGLE_180		CAMERA_ANGLE_0 + 180		//180�x
#define CAMERA_ANGLE_270		CAMERA_ANGLE_0 + 270		//270�x
#define CAMERA_ANGLE_360		CAMERA_ANGLE_0 + 360		//360�x

#define _USE_MATH_DEFINES
#include<math.h>

#define d_r(_d) _d * (M_PI / 180)	//d����r
#define r_d(_r) _r * (180 / M_PI)	//r����d

#include"DxLib.h"
#include"../../InputControl/Key/KeyInput.h"
#include"../../InputControl/Pad/PadInput.h"

#include<map>			//�A�z�z��
#include<string>		//�����񑀍�
#include<sstream>		//������ϊ�
#include<fstream>		//�t�@�C������