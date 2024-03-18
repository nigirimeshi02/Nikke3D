#include "Scarlet.h"
#include"../../common.h"
#include"../../ResourceManager/Model/ModelManager.h"

Scarlet::Scarlet()
{
	//3Dモデルのスケールを3倍にする
	MV1SetScale(ModelManager::GetModelHandle(SCARLET), VGet(3.0f, 3.0f, 3.0f));
}

Scarlet::~Scarlet()
{

}

void Scarlet::Update(GameMainScene* object)
{
	//座標をセットする
	MV1SetPosition(ModelManager::GetModelHandle(SCARLET), location);

	//回転値をセットする
	MV1SetRotationXYZ(ModelManager::GetModelHandle(SCARLET), rotation);

	//アニメーション
	Animation();

	//再生時間をセットする
	MV1SetAttachAnimTime(ModelManager::GetModelHandle(SCARLET), animIndex, animPlayTime);

	if (activeState == Controller::Scarlet)
	{
		//移動
		PlayerMovement(object);
	}

	//更新
	CharacterUpdate();

	//行動
	Action();

}

void Scarlet::Draw() const
{
	MV1DrawModel(ModelManager::GetModelHandle(SCARLET));
}

void Scarlet::Action()
{

}

void Scarlet::Animation()
{
	animPlayTime += .5f;

	//アニメーションのループ
	if (animPlayTime >= animTotalTime)
	{
		//ジャンプしていないかつ空中にいないなら初期化
		if (!isJump && !isAir)
		{
			animPlayTime = 0.f;
		}
		else
		{
			isJump = false;
		}
	}

	//待機アニメーションの読み込み
	if (isIdle && !isAir && animState != scarletAnim::Idle)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(SCARLET), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(SCARLET), scarletAnim::Idle, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(SCARLET), animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = scarletAnim::Idle;
	}

	//歩くアニメーションの読み込み
	if (isWalk && !isAir && animState != scarletAnim::Walk)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(SCARLET), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(SCARLET), scarletAnim::Walk, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(SCARLET), animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = scarletAnim::Walk;
	}

	//走るアニメーションの読み込み
	if (isDash && !isAir && animState != scarletAnim::Dash)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(SCARLET), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(SCARLET), scarletAnim::Dash, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(SCARLET), animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = scarletAnim::Dash;
	}

	//ジャンプアニメーションの読み込み
	if (isJump && !isDash && animState != scarletAnim::Jump && animState != scarletAnim::DashJump)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(SCARLET), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(SCARLET), scarletAnim::Jump, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(SCARLET), animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = scarletAnim::Jump;
	}

	//ダッシュジャンプのアニメーションの読み込み
	if (isJump && isDash && animState != scarletAnim::DashJump && animState != scarletAnim::Jump)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(SCARLET), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(SCARLET), scarletAnim::DashJump, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(SCARLET), animIndex);

		//再生時間の初期化
		animPlayTime = 3.f;

		animState = scarletAnim::DashJump;
	}

	//落下のアニメーションの読み込み
	if (isAir && !isJump && animState != scarletAnim::Fall)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(ModelManager::GetModelHandle(SCARLET), animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(SCARLET), scarletAnim::Fall, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(SCARLET), animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = scarletAnim::Fall;
	}
}
