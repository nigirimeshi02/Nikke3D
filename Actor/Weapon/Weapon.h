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
	void Draw()const;

	//モデルハンドル
	void Initialize(int handle, int cHandle, VECTOR base);


	void SetWeaponLocation(std::string frameName1, std::string frameName2);
	void SetWeaponRotation();

	class DesertEagle
	{
	private:
		VECTOR location;		//座標
		VECTOR rotation;		//回転値

	public:
		//コンストラクタ
		DesertEagle() : location(VGet(0.f, 0.f, 0.f)), rotation(VGet(0.f, 0.f, 0.f)) {};

		//デストラクタ
		~DesertEagle() {};

		//更新
		void Update(class GameMainScene* object, const char* path);

		//描画
		void Draw()const;

		//座標を取得する
		const VECTOR GetLocation() { return location; }

		//回転値を取得する
		const VECTOR GetRotation() { return rotation; }

		//座標を設定する
		void SetLocation(const VECTOR location)
		{
			this->location = location;
		}

		void SetLocationX(const float x) { location.x = x; }			//座標xを設定する
		void SetLocationY(const float y) { location.y = y; }			//座標yを設定する
		void SetLocationZ(const float z) { location.z = z; }			//座標zを設定する

		//回転値を設定する
		void SetRotation(const VECTOR rotation)
		{
			this->rotation = rotation;
		}

		void SetRotationX(const float x) { rotation.x = x; }			//回転値xを設定する
		void SetRotationY(const float y) { rotation.y = y; }			//回転値yを設定する
		void SetRotationZ(const float z) { rotation.z = z; }			//回転値zを設定する
	};
};
