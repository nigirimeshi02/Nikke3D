#include "Weapon.h"
#include "ResourceManager/Model/ModelManager.h"
#include "calculation/calculation.h"

Weapon::Weapon()
{
	
}

Weapon::~Weapon()
{
}

void Weapon::Update(std::string frameName1, std::string frameName2)
{
	SetWeaponLocation(frameName1, frameName2);
	SetWeaponRotation();
	MV1SetPosition(/*ModelManager::GetModelHandle(SWORD)*/modelHandle, weaponLocation[1]);
}

void Weapon::Draw() const
{
	int a = MV1DrawModel(/*ModelManager::GetModelHandle(SWORD)*/modelHandle);
	DrawSphere3D(weaponLocation[0], 2, 5, 0xff0000, 0xff0000, TRUE);
	DrawSphere3D(weaponLocation[1], 2, 5, 0xff0000, 0xff0000, TRUE);
	DrawSphere3D(weaponLocationTmp, 2, 5, 0x00ff00, 0xff0000, TRUE);
}

void Weapon::Initialize(int handle, int cHandle, VECTOR base)
{
	modelHandle = handle;
	CharModelHandle = cHandle;
	//weaponAttachFrameNum = MV1SearchFrame(/*ModelManager::GetModelHandle(ANIS)*/CharModelHandle, "�E�l�w�P");
	weaponAttachFrameNum = MV1SearchFrame(/*ModelManager::GetModelHandle(ANIS)*/CharModelHandle, "�E���w�P");
	//MV1SetScale(/*ModelManager::GetModelHandle(SWORD)*/modelHandle, VGet(0.05f, 0.05f, 0.05f));
	MV1SetScale(/*ModelManager::GetModelHandle(SWORD)*/modelHandle, VGet(5.0f, 5.0f, 5.0f));

	tmpBase2 = base;
}

void Weapon::SetWeaponLocation(std::string frameName1, std::string frameName2)
{
	int frameNum = MV1SearchFrame(/*ModelManager::GetModelHandle(ANIS)*/CharModelHandle, /*"�E�l�w�P"*/frameName1.c_str());
	int frameNum1 = MV1SearchFrame(/*ModelManager::GetModelHandle(ANIS)*/CharModelHandle, /*"�E���w�P"*/frameName2.c_str());

	VECTOR loc = MV1GetFramePosition(/*ModelManager::GetModelHandle(ANIS)*/CharModelHandle, frameNum);		//�l�w
	VECTOR loc1 = MV1GetFramePosition(/*ModelManager::GetModelHandle(ANIS)*/CharModelHandle, frameNum1);		//���w

	VECTOR v;
	v = { loc.x - loc1.x,loc.y - loc1.y ,loc.z - loc1.z };		//�����l
	
	//����
	float dis;
	dis = Get3DVectorLength(v);

	//�P�ʃx�N�g��
	VECTOR tmp;
	//������0�������ꍇ�P�ʃx�N�g�������ׂ�0�ɂ���
	if (dis != 0) {
		tmp = { v.x / dis,v.y / dis, v.z / dis };
	}
	else {
		tmp = { 0,0,0 };
	}

	dis = Get3DVectorLength(tmpBase2);

	weaponLocation[0] = MV1GetFramePosition(/*ModelManager::GetModelHandle(ANIS)*/CharModelHandle, weaponAttachFrameNum);
	weaponLocation[1] = MV1GetFramePosition(/*ModelManager::GetModelHandle(ANIS)*/CharModelHandle, weaponAttachFrameNum);

	weaponLocation[0] = { weaponLocation[0].x,weaponLocation[0].y,weaponLocation[0].z };
	weaponLocation[1] = { weaponLocation[1].x + tmp.x * dis,weaponLocation[1].y + tmp.y * dis,weaponLocation[1].z + tmp.z * dis };

	weaponVector = { (weaponLocation[0].x - weaponLocation[1].x), (weaponLocation[0].y - weaponLocation[1].y) ,(weaponLocation[0].z - weaponLocation[1].z) };

}

void Weapon::SetWeaponRotation()
{
	

	//x���̊p�x
	float tmp;
	




	
	tmpBase = tmpBase2;

	tmp = Get2DAngle2Vector(weaponVector.z, weaponVector.y, tmpBase.z, tmpBase.y);
	tmp = Get3DAngle2Vector(weaponVector, tmpBase);

	if (weaponVector.z > 0.f) {
		weaponRotation.x = d_r(tmp);

		
	}
	else {
		float d = 180 + (180 - tmp);
		weaponRotation.x = d_r(d);
	
	}
	tmpBase = { tmpBase.x,
		Get2DRotation(tmpBase.z,tmpBase.y,weaponRotation.x).y,
		-1 * Get2DRotation(tmpBase.z,tmpBase.y,weaponRotation.x).x };

	weaponLocationTmp.x = tmpBase.x + weaponLocation[1].x;
	weaponLocationTmp.y = tmpBase.y + weaponLocation[1].y;
	weaponLocationTmp.z = tmpBase.z + weaponLocation[1].z;

	//weaponLocationTmp1.x = tmpBase.x;
	//weaponLocationTmp1.y = tmpBase.y;
	//weaponLocationTmp1.z = tmpBase.z;

	tmpBase = { (weaponLocationTmp.x - weaponLocation[1].x),
		(weaponLocationTmp.y - weaponLocation[1].y),
		(weaponLocationTmp.z - weaponLocation[1].z)
	};

	//�����܂Ń����Z�b�g






	tmp = Get2DAngle2Vector(weaponVector.x, weaponVector.z, tmpBase.x, tmpBase.z);

	if (weaponVector.x > 0.f && weaponVector.z > 0.f) {
		weaponRotation.y = d_r(tmp);
	}
	else if (weaponVector.x < 0.f && weaponVector.z < 0.f) {
		float d = tmp;
		weaponRotation.y = d_r(d);
	}
	else {
		float d = 180 + (180 - tmp); //z+

		weaponRotation.y = d_r(d);
	}

	//weaponRotation.y = d_r(tmp);
	tmpBase = { -1 * Get2DRotation(tmpBase.x,tmpBase.z,weaponRotation.y).x,
		tmpBase.y,
		Get2DRotation(tmpBase.x,tmpBase.z,weaponRotation.y).y };

	weaponLocationTmp.x = tmpBase.x + weaponLocation[1].x;
	weaponLocationTmp.y = tmpBase.y + weaponLocation[1].y;
	weaponLocationTmp.z = tmpBase.z + weaponLocation[1].z;

	//weaponLocationTmp1.x = tmpBase.x;
	//weaponLocationTmp1.y = tmpBase.y;
	//weaponLocationTmp1.z = tmpBase.z;

	tmpBase = { (weaponLocationTmp.x - weaponLocation[1].x),
		(weaponLocationTmp.y - weaponLocation[1].y),
		(weaponLocationTmp.z - weaponLocation[1].z)
	};






	//koko

	tmp = Get2DAngle2Vector(weaponVector.x, weaponVector.y, tmpBase.x, tmpBase.y);
	//tmp = Get3DAngle2Vector(weaponVector, tmp2dBase);
	if (weaponVector.y > 0) {
		weaponRotation.z = d_r(tmp);
	}
	else {
		float d = 180 + (180 - tmp);
		weaponRotation.z = d_r(d);
	}

	tmpBase = { Get2DRotation(tmpBase.x,tmpBase.y,weaponRotation.z).x,
		Get2DRotation(tmpBase.x,tmpBase.y,weaponRotation.z).y,
		tmpBase.z, };

	weaponLocationTmp.x = tmpBase.x + weaponLocation[1].x;
	weaponLocationTmp.y = tmpBase.y + weaponLocation[1].y;
	weaponLocationTmp.z = tmpBase.z + weaponLocation[1].z;

	//weaponLocationTmp1.x = tmpBase.x;
	//weaponLocationTmp1.y = tmpBase.y;
	//weaponLocationTmp1.z = tmpBase.z;

	tmpBase = { (weaponLocationTmp.x - weaponLocation[1].x),
		(weaponLocationTmp.y - weaponLocation[1].y),
		(weaponLocationTmp.z - weaponLocation[1].z)
	};

	//weaponVectorTmp = { tmpBase.x,tmpBase.y ,tmpBase.z };
	MV1SetRotationXYZ(/*ModelManager::GetModelHandle(SWORD)*/modelHandle, weaponRotation);
}
