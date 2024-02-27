#pragma once
#include"DxLib.h"

#define MOVE_SPEED		1.5f	//移動の速度	
#define MAX_MOVE_SPEED	3.0f	//移動の最高速度
#define ROTATE_SPEED	45.f	//回転速度
#define GRAVITY			0.06f	//落下速度
#define JUMP_POWER		1.6f	//ジャンプ力

class Camera;

namespace playerAnim
{
	enum Animation
	{
		Dance = 0,			//くるくる
		Idle,				//待機
		Walk,				//歩き
		Dash,				//走り
		Jump,				//ジャンプ
		GunHold,			//射撃体勢
		DashJump,			//ダッシュジャンプ
		Fall				//落下
	};
}

class Player
{
private:
	int animIndex;				//アニメーションの要素数

	int animState;				//アニメーションの状態

	float animTotalTime;		//アニメーションの総再生時間
	float animPlayTime;			//アニメーションの再生時間

	float angle;				//角度
	float radian;				//ラジアン

	bool isIdle;				//待機中？
	bool isWalk;				//歩いている？
	bool isDash;				//走っている？
	bool isJump;				//飛んでいる？
	bool isGunHold;				//構えている？
	bool isAir;					//空中?

	VECTOR location;			//座標
	VECTOR weaponLocation;		//武器の座標
	VECTOR rotation;			//回転値
	VECTOR weaponRotation;		//武器の回転値
	VECTOR vec;					//移動量

public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//更新
	void Update(Camera* camera);

	//描画
	void Draw()const;

	//移動
	void Movement(Camera* camera);

	//アクション
	void Action();

	//武器の更新
	void WeaponUpdate(Camera* camera);

	//アニメーション
	void Animation();

	//座標を取得する
	VECTOR GetLocation() { return location; }

	//ベクトルを取得する
	VECTOR GetVec() { return vec; }
};

