#include"../../common.h"
#include "Player.h"
#include"../Camera/Camera.h"

Player::Player()
{
	//３Ｄモデルの読み込み
	modelHandle = MV1LoadModel("Nikke-Rapi/nikke.pmx");

	angle = 0.f;
	radian = angle * DX_PI_F / 180.f;

	isIdle = false;
	isWalk = false;
	isDash = false;

	location = VGet(0.0f, 0.0f, 0.0f);
	rotation = VGet(0.0f, 0.0f, 0.0f);
	vec = VGet(0.0f, 0.0f, 0.0f);

	//３Ｄモデルのスケールを2.5倍にする
	MV1SetScale(modelHandle, VGet(3.0f, 3.0f, 3.0f));
}

Player::~Player()
{
	MV1DeleteModel(modelHandle);
}

void Player::Update(Camera* camera)
{
	//座標をセットする
	MV1SetPosition(modelHandle, location);

	//回転値をセットする
	MV1SetRotationXYZ(modelHandle, rotation);

	//アニメーション
	Animation();

	//再生時間をセットする
	MV1SetAttachAnimTime(modelHandle, animIndex, animPlayTime);

	//移動
	Movement(camera);
}

void Player::Draw() const
{
	MV1DrawModel(modelHandle);

	DrawFormatString(0, 0, 0xffffff, "x:%f", location.x);
	DrawFormatString(0, 16, 0xffffff, "y:%f", location.y);
	DrawFormatString(0, 32, 0xffffff, "z:%f", location.z);
}

void Player::Movement(Camera* camera)
{
	VECTOR cameraVec = camera->GetIdentity();

	if (KeyInput::GetKeyDown(KEY_INPUT_W))
	{
		if (KeyInput::GetKeyDown(KEY_INPUT_LSHIFT))
		{			
			isDash = true;
			isWalk = false;
			isIdle = false;			

			if (vec.z > -MAX_MOVE_SPEED)
			{
				vec.z -= MOVE_SPEED;
			}
		}
		else
		{
			isWalk = true;
			isIdle = false;
			isDash = false;

			if (vec.z > -MOVE_SPEED)
			{
				vec.z -= MOVE_SPEED;
			}
		}

		angle = 360.f - camera->GetHAngle();
	}
	else if (KeyInput::GetKeyDown(KEY_INPUT_S))
	{
		if (KeyInput::GetKeyDown(KEY_INPUT_LSHIFT))
		{
			isDash = true;
			isWalk = false;
			isIdle = false;

			if (vec.z < MAX_MOVE_SPEED)
			{
				vec.z += MOVE_SPEED;
			}
		}
		else
		{
			isWalk = true;
			isIdle = false;
			isDash = false;

			if (vec.z < MOVE_SPEED)
			{
				vec.z += MOVE_SPEED;
			}
		}

		angle = 180.f - camera->GetHAngle();
	}
	else
	{
		isIdle = true;
		isWalk = false;
		isDash = false;
		vec.z = 0.f;
	}

	if (KeyInput::GetKeyDown(KEY_INPUT_A))
	{
		if (KeyInput::GetKeyDown(KEY_INPUT_LSHIFT))
		{
			isDash = true;
			isWalk = false;
			isIdle = false;

			if (vec.x < MAX_MOVE_SPEED)
			{
				vec.x += MOVE_SPEED;
			}
		}
		else
		{
			isWalk = true;
			isIdle = false;
			isDash = false;

			if (vec.x < MOVE_SPEED)
			{
				vec.x += MOVE_SPEED;
			}
		}

		angle = 270.f - camera->GetHAngle();
	}
	else if (KeyInput::GetKeyDown(KEY_INPUT_D))
	{
		if (KeyInput::GetKeyDown(KEY_INPUT_LSHIFT))
		{
			isDash = true;
			isWalk = false;
			isIdle = false;

			if (vec.x > -MAX_MOVE_SPEED)
			{
				vec.x -= MOVE_SPEED;
			}
		}
		else
		{
			isWalk = true;
			isIdle = false;
			isDash = false;

			if (vec.x > -MOVE_SPEED)
			{
				vec.x -= MOVE_SPEED;
			}
		}

		angle = 90.f - camera->GetHAngle();
	}
	else
	{
		vec.x = 0.f;
	}

	radian = angle * DX_PI_F / 180.f;
	rotation = VGet(0, radian, 0);

	if (isWalk || isDash)
	{
		VECTOR moveVec;

		float sinPara = sinf(camera->GetHAngle() / 180.f * DX_PI_F);
		float cosPara = cosf(camera->GetHAngle() / 180.f * DX_PI_F);

		moveVec.x = vec.x * cosPara - vec.z * sinPara;
		moveVec.y = 0.f;
		moveVec.z = vec.x * sinPara + vec.z * cosPara;

		location = VAdd(location, moveVec);
	}
}

void Player::Animation()
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
