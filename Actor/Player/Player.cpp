#include"../../common.h"
#include "Player.h"
#include"../../ResourceManager/Model/ModelManager.h"
#include"../Weapon/Weapon.h"
#include"../../Scene/GameMain/GameMainScene.h"

Player::Player()
{
	handGun = new Weapon::DesertEagle();

	isHit = false;

	scale = VGet(3.f, 3.f, 3.f);

	//3Dモデルのスケールを3倍にする
	MV1SetScale(ModelManager::GetModelHandle(RAPI), scale);
	MV1SetScale(ModelManager::GetModelHandle(DESERT_EAGLE), VGet(3.0f, 3.0f, 3.0f));

}

Player::~Player()
{
	delete handGun;
}

void Player::Update(GameMainScene* object)
{
	//座標をセットする
	MV1SetPosition(ModelManager::GetModelHandle(RAPI), location);

	//回転値をセットする
	MV1SetRotationXYZ(ModelManager::GetModelHandle(RAPI), rotation);

	//アニメーション
	Animation();

	//再生時間をセットする
	MV1SetAttachAnimTime(ModelManager::GetModelHandle(RAPI), animIndex, animPlayTime);

 	if (activeState == Controller::Rapi)
	{
		//移動
		PlayerMovement(object);
	}

	//更新
	CharacterUpdate();

	//行動
	Action();

	//武器
	handGun->Update(object,RAPI);

	OBBUpdate(RAPI);

	if (HitCheck(object->GetScarlet()))
	{
		isHit = true;
	}
	else
	{
		isHit = false;
	}
}

void Player::Draw() const
{
	MV1DrawModel(ModelManager::GetModelHandle(RAPI));
	handGun->Draw();

	DrawFormatString(0, 0, 0xffffff, "x:%f", location.x);
	DrawFormatString(0, 10, 0xffffff, "y:%f", location.y);
	DrawFormatString(0, 20, 0xffffff, "z:%f", location.z);
	DrawFormatString(100, 0, 0xffffff, "isHit:%s", isHit ? "true" : "false");
}

void Player::Action()
{
	if (KeyInput::GetButtonDown(MOUSE_INPUT_RIGHT))
	{
		isGunHold = true;
		//isIdle = false;
		//isDash = false;
		//isWalk = false;
	}
	else
	{
		isGunHold = false;
	}
}

void Player::Animation()
{
	animPlayTime += .5f;

	//アニメーションのループ
	if (animPlayTime >= animTotalTime)
	{
		//ジャンプしていないかつ空中にいないなら初期化
		if (!isJump&&!isAir)
		{
			animPlayTime = 0.f;
		}
		else
		{
			isJump = false;
		}
	}

	//待機アニメーションの読み込み
	if (isIdle && !isAir && animState != playerAnim::Idle)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Idle, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = playerAnim::Idle;
	}

	//歩くアニメーションの読み込み
	if (isWalk && !isAir && animState != playerAnim::Walk)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Walk, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = playerAnim::Walk;
	}

	//走るアニメーションの読み込み
	if (isDash && !isAir && animState != playerAnim::Dash)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Dash, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = playerAnim::Dash;
	}

	//ジャンプアニメーションの読み込み
	if (isJump && !isDash && animState != playerAnim::Jump && animState != playerAnim::DashJump)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Jump, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = playerAnim::Jump;
	}

	//銃を構えるアニメーションの読み込み
	if (isGunHold && animState != playerAnim::GunHold)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::GunHold, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = playerAnim::GunHold;
	}

	//ダッシュジャンプのアニメーションの読み込み
	if (isJump && isDash && animState != playerAnim::DashJump && animState != playerAnim::Jump)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::DashJump, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//再生時間の初期化
		animPlayTime = 3.f;

		animState = playerAnim::DashJump;
	}

	//落下のアニメーションの読み込み
	if (isAir && !isJump && animState != playerAnim::Fall)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Fall, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = playerAnim::Fall;
	}
}