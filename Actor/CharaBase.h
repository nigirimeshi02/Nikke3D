#pragma once
#include"DxLib.h"
#include"../Collision/OBB/OBB.h"

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
		Rapi = 0,
		Scarlet
	};
}

class CharaBase :public OBB
{
protected:
	int animIndex;				//アニメーションの要素
	int animState;				//アニメーションの状態
	static int activeState;		//操作状態

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

	//更新
	virtual void Update(GameMainScene* object) = 0;

	//描画
	virtual void Draw()const = 0;
	
private:
	//アクション
	virtual void Action() = 0;

	//アニメーション
	virtual void Animation() = 0;

public:
	//ラジアンを取得する
	float GetRadian()const { return radian; }

	//構えているかどうか取得する
	bool GetGunHold()const { return isGunHold; }

	//操作状態の取得
	int GetActiveState()const { return activeState; }

	//操作状態の設定
	void SetActiveState(const Controller::State character)
	{
		activeState = character;
	}

protected:
	//キャラクターの更新処理
	void CharacterUpdate();

	//プレイヤーの移動処理
	void PlayerMovement(GameMainScene* object);

	//移動のアニメーション
	void MovementAnimation(const char* character);
};

