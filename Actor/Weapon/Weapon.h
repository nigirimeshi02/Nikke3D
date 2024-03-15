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

	VECTOR tmpBase;	//ベースの長さ、
	VECTOR tmpBase2;	//ベースの長さを保存、最初の長さがないとだめ

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

	//モデルハンドル
	void Initialize(int handle, int cHandle, VECTOR base);


	void SetWeaponLocation(std::string frameName1, std::string frameName2);
	void SetWeaponRotation();
};

