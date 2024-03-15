#pragma once
#include "../../common.h"

class Weapon
{
private:
	int modelHandle;
	int CharModelHandle;
	int weaponAttachFrameNum;
	VECTOR weaponLocation[2];
	VECTOR weaponLocationTmp;
	//VECTOR weaponLocationTmp1;
	VECTOR weaponVector;
	//VECTOR weaponVectorTmp;
	VECTOR weaponRotation;

	VECTOR tmpBase;	//�x�[�X�̒����A
	VECTOR tmpBase2;	//�x�[�X�̒�����ۑ��A�ŏ��̒������Ȃ��Ƃ���

	VECTOR aaa;

	float o = 0;
	float o1 = 0;
	float o2 = 0;
	
public:
	Weapon();
	~Weapon();

	void Update(std::string frameName1, std::string frameName2);
	void Update();
	void Draw()const;

	//���f���n���h��
	void Initialize(int handle, int cHandle, VECTOR base);


	void SetWeaponLocation(std::string frameName1, std::string frameName2);
	void SetWeaponRotation();
};

