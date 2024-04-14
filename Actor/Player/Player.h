﻿#pragma once
#include"DxLib.h"
#include"../CharaBase.h"
#include"../Weapon/Weapon.h"

namespace playerAnim
{
	enum Animation
	{
		Idle = 0,			//待機
		Walk,				//歩き
		Dash,				//走り
		Jump,				//ジャンプ
		GunHold,			//射撃体勢
		DashJump,			//ダッシュジャンプ
		Fall				//落下
	};
}

class Player :public CharaBase
{
private:
	Weapon::DesertEagle* handGun;	//デザートイーグルのオブジェクト

	bool isHit;
public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//更新
	void Update(GameMainScene* object)override;

	//描画
	void Draw()const override;

private:
	//アクション
	void Action()override;

	//アニメーション
	void Animation()override;

public:
	//デザートイーグルのオブジェクトを取得する
	Weapon::DesertEagle* GetDesertEagle()const { return handGun; }
};

