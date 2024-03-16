#pragma once
#include"DxLib.h"
#include"../CharaBase.h"
#include"../Weapon/Weapon.h"

class GameMainScene;

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

class Player :public CharaBase
{
private:
	Weapon::DesertEagle* handGun;	//デザートイーグルのオブジェクト

public:
	//コンストラクタ
	Player();

	//デストラクタ
	~Player();

	//更新
	void Update(GameMainScene* object);

	//描画
	void Draw()const;

	//アクション
	void Action();

	//アニメーション
	void Animation();

	//デザートイーグルのオブジェクトを取得する
	Weapon::DesertEagle* GetDesertEagle() { return handGun; }
};

