#include "Weapon.h"
#include "../../ResourceManager/Model/ModelManager.h"
#include "../../calculation/calculation.h"

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
	//DrawSphere3D(weaponLocation[0], 2, 5, 0xff0000, 0xff0000, TRUE);
	DrawSphere3D(weaponLocation[1], 2, 5, 0xff0000, 0xff0000, TRUE);
	DrawSphere3D(weaponLocationTmp, 2, 5, 0x00ff00, 0xff0000, TRUE);

	float dis = Get3DVectorLength(tmpBase2);
	VECTOR v = { tmpBase2.x / dis,tmpBase2.y / dis,tmpBase2.z / dis };
	VECTOR l = { weaponLocation[0].x + v.x * 30,weaponLocation[0].y + v.y * 30,weaponLocation[0].z + v.z * 30 };
	//DrawSphere3D(l, 3, 5, 0x00ffff, 0x00ffff, TRUE);


	DrawFormatString(200, 0 + 48, 0xffffff, "x:%f", weaponVector.x);
	DrawFormatString(200, 16 + 48, 0xffffff, "y:%f", weaponVector.y);
	DrawFormatString(200, 32 + 48, 0xffffff, "z:%f", weaponVector.z);

	DrawFormatString(400, 0 + 48, 0xffffff, "wrx:%f", r_d(weaponRotation.x));
	DrawFormatString(400, 16 + 48, 0xffffff, "wry:%f", r_d(weaponRotation.y));
	DrawFormatString(400, 32 + 48, 0xffffff, "wrz:%f", r_d(weaponRotation.z));

	DrawFormatString(800, 0 + 48, 0xffffff, "x:%f", weaponLocation[0].x);
	DrawFormatString(800, 16 + 48, 0xffffff, "y:%f", weaponLocation[0].y);
	DrawFormatString(800, 32 + 48, 0xffffff, "z:%f", weaponLocation[0].z);
}

void Weapon::Initialize(int handle, int cHandle, VECTOR base)
{
	modelHandle = handle;
	CharModelHandle = cHandle;
	//weaponAttachFrameNum = MV1SearchFrame(/*ModelManager::GetModelHandle(ANIS)*/CharModelHandle, "右人指１");
	weaponAttachFrameNum = MV1SearchFrame(/*ModelManager::GetModelHandle(ANIS)*/CharModelHandle, "右中指１");
	//MV1SetScale(/*ModelManager::GetModelHandle(SWORD)*/modelHandle, VGet(0.05f, 0.05f, 0.05f));
	MV1SetScale(/*ModelManager::GetModelHandle(SWORD)*/modelHandle, VGet(5.0f, 5.0f, 5.0f));

	tmpBase2 = base;
}

void Weapon::SetWeaponLocation(std::string frameName1, std::string frameName2)
{
	int frameNum = MV1SearchFrame(/*ModelManager::GetModelHandle(ANIS)*/CharModelHandle, /*"右人指１"*/frameName1.c_str());
	int frameNum1 = MV1SearchFrame(/*ModelManager::GetModelHandle(ANIS)*/CharModelHandle, /*"右小指１"*/frameName2.c_str());

	VECTOR loc = MV1GetFramePosition(/*ModelManager::GetModelHandle(ANIS)*/CharModelHandle, frameNum);		//人指
	VECTOR loc1 = MV1GetFramePosition(/*ModelManager::GetModelHandle(ANIS)*/CharModelHandle, frameNum1);		//小指

	VECTOR v;
	v = { loc.x - loc1.x,loc.y - loc1.y ,loc.z - loc1.z };		//小→人
	
	//長さ
	float dis;
	dis = Get3DVectorLength(v);

	//単位ベクトル
	VECTOR tmp;
	//距離が0だった場合単位ベクトルをすべて0にする
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

	//weaponVector = { (weaponLocation[0].x - weaponLocation[1].x), (weaponLocation[0].y - weaponLocation[1].y) ,(weaponLocation[0].z - weaponLocation[1].z) };
	weaponVector = { (weaponLocation[1].x - weaponLocation[0].x), (weaponLocation[1].y - weaponLocation[0].y) ,(weaponLocation[1].z - weaponLocation[0].z) };

}

void Weapon::SetWeaponRotation()
{

	if (KeyInput::GetKeyDown(KEY_INPUT_Z)) o2--;
	if (KeyInput::GetKeyDown(KEY_INPUT_X)) o2++;
	if (KeyInput::GetKeyDown(KEY_INPUT_C)) o2 = 0;



	weaponRotation = { 0,0,0 };
	Vector4 v4;
	Matrix4x4 m;
	Vector4 tmpv;

	//x軸の角度
	float tmp;
	
	tmpBase = tmpBase2;

	float baseAngle = Get2DAngle2Vector(tmpBase.z, tmpBase.y, 10, 0);

	/*VECTOR v90 = Get2DRotation(weaponVector.z, weaponVector.y, d_r(90));
	VECTOR v270 = Get2DRotation(weaponVector.z, weaponVector.y, d_r(270));*/

	VECTOR v90 = Get2DRotation(tmpBase.z, tmpBase.y, d_r(90));
	VECTOR v270 = Get2DRotation(tmpBase.z, tmpBase.y, d_r(270));

	/*float baseAngle90 = Get2DAngle2Vector(tmpBase.z, tmpBase.y, v90.x, v90.y);
	float baseAngle270 = Get2DAngle2Vector(tmpBase.z, tmpBase.y, v270.x, v270.y);*/


	tmp = Get2DAngle2Vector(weaponVector.z, weaponVector.y, tmpBase.z, tmpBase.y);
	//tmp = Get3DAngle2Vector(weaponVector, tmpBase);

	//テスト１
	/*if (weaponVector.z > 0.f) {
		weaponRotation.x = d_r(tmp);

		
	}
	else {
		float d = 180 + (180 - tmp);
		weaponRotation.x = d_r(d);
	}*/
	//テスト２
	//ここで回転の角度を出している
	/*if (weaponVector.y > 0.f) {
		weaponRotation.x = d_r(tmp);
	}
	else {
		float d = 180 + (180 - tmp);
		weaponRotation.x = d_r(d);
	}*/

	//テスト３
	if (weaponVector.z > 0) {
		if (Get2DAngle2Vector(weaponVector.z, weaponVector.y, v90.x, v90.y) > Get2DAngle2Vector(weaponVector.z, weaponVector.y, v270.x, v270.y)) {
			tmp += o1 + 90;
			weaponRotation.x = d_r(tmp);
		}
		else {
			float d = 180 + (180 - tmp) + o1 + 90;
			weaponRotation.x = d_r(d);
		}
	}
	else {
		if (Get2DAngle2Vector(weaponVector.z, weaponVector.y, v90.x, v90.y) > Get2DAngle2Vector(weaponVector.z, weaponVector.y, v270.x, v270.y)) {
			tmp += o1;
			weaponRotation.x = d_r(tmp);
		}
		else {
			float d = 180 + (180 - tmp) + o1;
			weaponRotation.x = d_r(d);
		}
	}
	if (Get2DAngle2Vector(weaponVector.z, weaponVector.y, v90.x, v90.y) > Get2DAngle2Vector(weaponVector.z, weaponVector.y, v270.x, v270.y)) {
		tmp += o1;
		weaponRotation.x = d_r(tmp);
	}
	else {
		float d = 180 + (180 - tmp) + o1;
		weaponRotation.x = d_r(d);
	}
	//if (weaponVector.z > 0.f) {
	//	weaponRotation.x = d_r(tmp);

	//	//kakudo[0] = d;
	//}
	//else {
	//	float d = 180 + (180 - tmp);
	//	weaponRotation.x = d_r(d);
	//	//kakudo[0] = tmp;
	//}


	v4 = { tmpBase.x,tmpBase.y,tmpBase.z,0 };
	//回転マトリクス
	m = Matrix4x4_RotateX(weaponRotation.x);

	tmpv = Matrix4x4_Mul_Vector4(m, v4);

	/*tmpBase = { tmpBase.x,
		Get2DRotation(tmpBase.z,tmpBase.y,weaponRotation.x).y,
		-1 * Get2DRotation(tmpBase.z,tmpBase.y,weaponRotation.x).x };*/

	tmpBase = { tmpv.x,tmpv.y,tmpv.z };

	weaponLocationTmp.x = tmpBase.x + weaponLocation[0].x;
	weaponLocationTmp.y = tmpBase.y + weaponLocation[0].y;
	weaponLocationTmp.z = tmpBase.z + weaponLocation[0].z;

	//weaponLocationTmp1.x = tmpBase.x;
	//weaponLocationTmp1.y = tmpBase.y;
	//weaponLocationTmp1.z = tmpBase.z;

	/*tmpBase = { (weaponLocationTmp.x - weaponLocation[1].x),
		(weaponLocationTmp.y - weaponLocation[1].y),
		(weaponLocationTmp.z - weaponLocation[1].z)
	};*/

	//tmpBase = { (weaponLocationTmp.x - weaponLocation[1].x),
	//	(weaponLocationTmp.y - weaponLocation[1].y),
	//	(weaponLocationTmp.z - weaponLocation[1].z)
	//};




	//ここまでワンセット





	//baseAngle = Get2DAngle2Vector(tmpBase.x, tmpBase.z, 10, 0);
	v90 = Get2DRotation(tmpBase.x, tmpBase.z, d_r(90));
	v270 = Get2DRotation(tmpBase.x, tmpBase.z, d_r(270));

	tmp = Get2DAngle2Vector(weaponVector.x, weaponVector.z, tmpBase.x, tmpBase.z);
	//tmp = Get3DAngle2Vector(weaponVector, tmpBase);

	//if (weaponVector.x > 0.f && weaponVector.z > 0.f) {
	//	weaponRotation.y = d_r(tmp);
	//}
	//else if (weaponVector.x < 0.f && weaponVector.z < 0.f) {
	//	float d = tmp;
	//	weaponRotation.y = d_r(d);
	//}
	//else {
	//	float d = 180 + (180 - tmp); //z+

	//	weaponRotation.y = d_r(d);
	//}

	/*if (weaponVector.z > 0.f) {
		weaponRotation.y = d_r(tmp);
	}
	else {
		float d = 180 + (180 - tmp);
		weaponRotation.y = d_r(d);
	}

	weaponRotation.y = d_r(tmp);*/

	if (weaponVector.z < 0) {
		if (Get2DAngle2Vector(weaponVector.x, weaponVector.z, v90.x, v90.y) > Get2DAngle2Vector(weaponVector.x, weaponVector.z, v270.x, v270.y)) {
			weaponRotation.y = d_r(tmp);
		}
		else {
			float d = 180 + (180 - tmp);
			weaponRotation.y = d_r(d);
		}
	}
	else {
		//if (Get2DAngle2Vector(weaponVector.x, weaponVector.z, v90.x, v90.y) < Get2DAngle2Vector(weaponVector.x, weaponVector.z, v270.x, v270.y)) {
		//	/*weaponRotation.y = d_r(tmp);*/
		//	float d = (tmp);
		//	weaponRotation.y = d_r(d);
		//}
		//else {
		//	float d = 180 + (180 - tmp);
		//	weaponRotation.y = d_r(-d);
		//}
		weaponRotation.y = d_r(0);
	}

	if (Get2DAngle2Vector(weaponVector.x, weaponVector.z, v90.x, v90.y) > Get2DAngle2Vector(weaponVector.x, weaponVector.z, v270.x, v270.y)) {
		tmp += o;
		weaponRotation.y = d_r(tmp);
	}
	else {
		float d = 180 + (180 - tmp) + o;
		weaponRotation.y = d_r(d);
	}



	//weaponRotation.y = d_r(tmp);
	/*float d = 180 + (180 - tmp);
	weaponRotation.y = d_r(d);*/
	/*tmpBase = { -1 * Get2DRotation(tmpBase.x,tmpBase.z,weaponRotation.y).x,
		tmpBase.y,
		Get2DRotation(tmpBase.x,tmpBase.z,weaponRotation.y).y };*/

	v4 = { tmpBase.x,tmpBase.y,tmpBase.z,0 };
	//回転マトリクス
	m = Matrix4x4_RotateY(weaponRotation.y);

	tmpv = Matrix4x4_Mul_Vector4(m, v4);

	/*tmpBase = { tmpBase.x,
		Get2DRotation(tmpBase.z,tmpBase.y,weaponRotation.x).y,
		-1 * Get2DRotation(tmpBase.z,tmpBase.y,weaponRotation.x).x };*/

	//weaponLocationTmp1.x = tmpBase.x;
	tmpBase = { tmpv.x,tmpv.y,tmpv.z };

	weaponLocationTmp.x = tmpBase.x + weaponLocation[0].x;
	weaponLocationTmp.y = tmpBase.y + weaponLocation[0].y;
	weaponLocationTmp.z = tmpBase.z + weaponLocation[0].z;

	//weaponLocationTmp1.y = tmpBase.y;
	//weaponLocationTmp1.z = tmpBase.z;

	/*tmpBase = { (weaponLocationTmp.x - weaponLocation[1].x),
		(weaponLocationTmp.y - weaponLocation[1].y),
		(weaponLocationTmp.z - weaponLocation[1].z)
	};*/


	//weaponRotation.y = d_r(o);




	////koko

	v90 = Get2DRotation(tmpBase.x, tmpBase.y, d_r(90));
	v270 = Get2DRotation(tmpBase.x, tmpBase.y, d_r(270));

	tmp = Get2DAngle2Vector(weaponVector.x, weaponVector.y, tmpBase.x, tmpBase.y);
	//tmp = Get3DAngle2Vector(weaponVector, tmp2dBase);
	/*if (weaponVector.y > 0) {
		weaponRotation.z = d_r(tmp);
	}
	else {
		float d = 180 + (180 - tmp);
		weaponRotation.z = d_r(d);
	}*/

	if (Get2DAngle2Vector(weaponVector.x, weaponVector.y, v90.x, v90.y) < Get2DAngle2Vector(weaponVector.x, weaponVector.y, v270.x, v270.y)) {
		tmp += o2;
		weaponRotation.z = d_r(tmp);
	}
	else {
		float d = 180 + (180 - tmp) + o2;
		weaponRotation.z = d_r(d);
	}


	/*tmpBase = { Get2DRotation(tmpBase.x,tmpBase.y,weaponRotation.z).x,
		Get2DRotation(tmpBase.x,tmpBase.y,weaponRotation.z).y,
		tmpBase.z, };*/

	v4 = { tmpBase.x,tmpBase.y,tmpBase.z,0 };
	//回転マトリクス
	m = Matrix4x4_RotateZ(weaponRotation.z);

	tmpv = Matrix4x4_Mul_Vector4(m, v4);

	tmpBase = { tmpv.x,tmpv.y,tmpv.z };

	weaponLocationTmp.x = tmpBase.x + weaponLocation[0].x;
	weaponLocationTmp.y = tmpBase.y + weaponLocation[0].y;
	weaponLocationTmp.z = tmpBase.z + weaponLocation[0].z;

	//weaponLocationTmp1.x = tmpBase.x;
	//weaponLocationTmp1.y = tmpBase.y;
	//weaponLocationTmp1.z = tmpBase.z;

	/*tmpBase = { (weaponLocationTmp.x - weaponLocation[1].x),
		(weaponLocationTmp.y - weaponLocation[1].y),
		(weaponLocationTmp.z - weaponLocation[1].z)
	};*/

	//weaponVectorTmp = { tmpBase.x,tmpBase.y ,tmpBase.z };
	//weaponRotation.y = 0;
	//weaponRotation.z = 0;
	MV1SetRotationXYZ(/*ModelManager::GetModelHandle(SWORD)*/modelHandle, weaponRotation);
}
