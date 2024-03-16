#pragma once
#include"DxLib.h"

#define MOVE_SPEED		1.5f	//移動の速度	
#define MAX_MOVE_SPEED	3.0f	//移動の最高速度
#define ROTATE_SPEED	45.f	//回転速度
#define GRAVITY			0.06f	//落下速度
#define JUMP_POWER		1.6f	//ジャンプ力

class GameMainScene;

namespace Controller
{
	enum State
	{
		Player = 0
	};
}

class CharaBase
{
private:

protected:
	VECTOR location;			//座標
	VECTOR rotation;			//回転値
	VECTOR vec;					//移動量

	int animIndex;				//アニメーションの要素
	int animState;				//アニメーションの状態
	int activeState;			//操作状態

	float angle;				//角度
	float radian;				//ラジアン
	float animTotalTime;		//アニメーションの総再生時間
	float animPlayTime;			//アニメーションの再生時間

	bool isIdle;				//待機中？
	bool isWalk;				//歩いている？
	bool isDash;				//走っている？
	bool isJump;				//飛んでいる？
	bool isGunHold;				//構えている？
	bool isAir;					//空中?

public:
	//コンストラクタ
	CharaBase();

	//デストラクタ
	~CharaBase();

	//座標を取得する
	const VECTOR GetLocation() { return location; }

	//回転値を取得する
	const VECTOR GetRotation() { return rotation; }

	//ベクトルを取得する
	const VECTOR GetVec() { return vec; }

	//ラジアンを取得する
	const float GetRadian() { return radian; }

	//構えているかどうか取得する
	const bool GetGunHold() { return isGunHold; }

protected:
	//プレイヤーの移動処理
	void	PlayerMovement(GameMainScene* object);

};

