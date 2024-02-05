#pragma once
#include "DxLib.h"

class Enemy
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
	Enemy();

	//デストラクタ
	~Enemy();

	//更新
	void Update();

	//描画
	void Draw()const;

	//移動
	void Movement();

	//アニメーション
	void Animation();

	//座標の取得
	VECTOR GetLocation() { return location; }

};



