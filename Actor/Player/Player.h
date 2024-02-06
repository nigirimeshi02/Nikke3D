#pragma once
#include"DxLib.h"

#define ANIMATION_INDEX 4		//アニメーションの数
#define MOVE_SPEED		0.5f	//移動の速度	
#define MAX_MOVE_SPEED	2.0f	//移動の最高速度

class Camera;

namespace playerAnim
{
	enum Animation
	{
		Dance = 0,			//くるくる
		Idle,				//待機
		Walk,				//歩き
		Dash				//走り
	};
}

class Player
{
private:
	int modelHandle;			//モデルのハンドル

	int animIndex;				//アニメーションの要素数

	int animState;				//アニメーションの状態

	float animTotalTime;		//アニメーションの総再生時間
	float animPlayTime;			//アニメーションの再生時間

	float angle;				//角度
	float radian;				//ラジアン

	bool isIdle;				//待機中？
	bool isWalk;				//歩いている？
	bool isDash;				//走っている？

	VECTOR location;			//座標
	VECTOR rotation;			//回転値
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

	//アニメーション
	void Animation();

	//座標を取得する
	VECTOR GetLocation() { return location; }

	//ベクトルを取得する
	VECTOR GetVec() { return vec; }
};

