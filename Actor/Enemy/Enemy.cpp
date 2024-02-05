#include"../../common.h"
#include "Enemy.h"
#include "../Player/Player.h"


Enemy::Enemy()
{
	//３Ｄモデルの読み込み
	modelHandle = MV1LoadModel("Anis.fbm/Anis-Apose.pmx");

	angle = 0.f;
	radian = angle * DX_PI_F / 180.f;

	isIdle = true;
	isWalk = false;
	isDash = false;

	location = VGet(0.0f, 0.0f, 0.0f);
	rotation = VGet(0.0f, 0.0f, 0.0f);
	vec = VGet(0.0f, 0.0f, 0.0f);

	//３Ｄモデルのスケールを2.5倍にする
	MV1SetScale(modelHandle, VGet(3.0f, 3.0f, 3.0f));
}

Enemy::~Enemy()
{
	MV1DeleteModel(modelHandle);
}

void Enemy::Update()
{
	//座標をセットする
	MV1SetPosition(modelHandle, location);

	//回転値をセットする
	MV1SetRotationXYZ(modelHandle, rotation);

	//アニメーション
	Animation();

	//再生時間をセットする
	MV1SetAttachAnimTime(modelHandle, animIndex, animPlayTime);

	rotation.z++;

}

void Enemy::Draw() const
{
	MV1DrawModel(modelHandle);
}

void Enemy::Movement()
{
}

void Enemy::Animation()
{
	animPlayTime += .5f;

	if (animPlayTime >= animTotalTime)
	{
		animPlayTime = MOVE_SPEED;
	}

	//待機アニメーションの読み込み
	if (isIdle && animState != playerAnim::Idle)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(modelHandle, animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(modelHandle, playerAnim::Idle, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = playerAnim::Idle;
	}

	//歩くアニメーションの読み込み
	if (isWalk && animState != playerAnim::Walk)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(modelHandle, animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(modelHandle, playerAnim::Walk, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = playerAnim::Walk;
	}

	//走るアニメーションの読み込み
	if (isDash && animState != playerAnim::Dash)
	{
		//アニメーションのデタッチ
		MV1DetachAnim(modelHandle, animIndex);

		//アニメーションのアタッチ
		animIndex = MV1AttachAnim(modelHandle, playerAnim::Dash, -1, FALSE);

		//アタッチしたモーションの総再生時間を取得する
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);

		//再生時間の初期化
		animPlayTime = 0.f;

		animState = playerAnim::Dash;
	}
}

