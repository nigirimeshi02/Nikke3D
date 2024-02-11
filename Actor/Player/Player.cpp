#include"../../common.h"
#include "Player.h"
#include"../Camera/Camera.h"
#include"../../ResourceManager/Model/ModelManager.h"

Player::Player()
{
	animIndex = 0;

	animState = playerAnim::Dance;

	animPlayTime = 0.f;
	animTotalTime = 0.f;

	jumpPower = 0.f;

	angle = CAMERA_ANGLE_0 * 2;
	radian = angle * DX_PI_F / 180.f;

	isIdle = false;
	isWalk = false;
	isDash = false;
	isJump = false;
	isGunHold = false;

	location = VGet(0.0f, 0.0f, 0.0f);
	weaponLocation = VGet(0.0f, 0.0f, 0.0f);
	rotation = VGet(0.0f, 0.0f, 0.0f);
	weaponRotation = VGet(0.0f, 0.0f, 0.0f);
	vec = VGet(0.0f, 0.0f, 0.0f);

	//３Ｄモデルのスケールを2.5倍にする
	MV1SetScale(ModelManager::GetModelHandle(RAPI), VGet(3.0f, 3.0f, 3.0f));

	weaponAttachFrameNum = MV1SearchFrame(ModelManager::GetModelHandle(RAPI), "右手先");
	MV1SetScale(ModelManager::GetModelHandle(DESERT_EAGLE), VGet(5.0f, 5.0f, 5.0f));
}

Player::~Player()
{

}

void Player::Update(Camera* camera)
{
	//座標をセットする
	MV1SetPosition(ModelManager::GetModelHandle(RAPI), location);

	//回転値をセットする
	MV1SetRotationXYZ(ModelManager::GetModelHandle(RAPI), rotation);

	//アニメーション
	Animation();

	//再生時間をセットする
	MV1SetAttachAnimTime(ModelManager::GetModelHandle(RAPI), animIndex, animPlayTime);

	//移動
	Movement(camera);

	//行動
	Action();

	//武器
	weaponLocation = MV1GetFramePosition(ModelManager::GetModelHandle(RAPI), weaponAttachFrameNum);
	MV1SetPosition(ModelManager::GetModelHandle(DESERT_EAGLE), weaponLocation);
	MV1SetRotationXYZ(ModelManager::GetModelHandle(DESERT_EAGLE), weaponRotation);
}

void Player::Draw() const
{
	MV1DrawModel(ModelManager::GetModelHandle(RAPI));
	MV1DrawModel(ModelManager::GetModelHandle(DESERT_EAGLE));

	DrawFormatString(0, 0, 0xffffff, "x:%f", location.x);
	DrawFormatString(0, 10, 0xffffff, "y:%f", location.y);
	DrawFormatString(0, 20, 0xffffff, "z:%f", location.z);
}

void Player::Movement(Camera* camera)
{
	if (KeyInput::GetKeyDown(KEY_INPUT_W))
	{
		if (KeyInput::GetKeyDown(KEY_INPUT_LSHIFT))
		{			
			if (!isJump)
			{
				isDash = true;
				isWalk = false;
				isIdle = false;			
			}
			else
			{
				isDash = false;
				isWalk = false;
				isIdle = false;
			}

			if (vec.z > -MAX_MOVE_SPEED)
			{
				vec.z -= MOVE_SPEED;
			}
		}
		else
		{
			if (!isJump)
			{
				isWalk = true;
				isIdle = false;
				isDash = false;
			}
			else
			{
				isWalk = false;
				isIdle = false;
				isDash = false;
			}

			vec.z = -MOVE_SPEED;
		}

		angle = CAMERA_ANGLE_0 - camera->GetHAngle();
	}
	else if (KeyInput::GetKeyDown(KEY_INPUT_S))
	{
		if (KeyInput::GetKeyDown(KEY_INPUT_LSHIFT))
		{
			if (!isJump)
			{
				isDash = true;
				isWalk = false;
				isIdle = false;
			}
			else
			{
				isDash = false;
				isWalk = false;
				isIdle = false;
			}

			if (vec.z < MAX_MOVE_SPEED)
			{
				vec.z += MOVE_SPEED;
			}
		}
		else
		{
			if (!isJump)
			{
				isWalk = true;
				isIdle = false;
				isDash = false;
			}
			else
			{
				isWalk = false;
				isIdle = false;
				isDash = false;
			}

			vec.z = MOVE_SPEED;
		}

		angle = CAMERA_ANGLE_180 - camera->GetHAngle();
	}
	else
	{
		if (!isJump)
		{
			isIdle = true;
		}
		else
		{
			isIdle = false;
		}
		isWalk = false;
		isDash = false;
		vec.z = 0.f;
	}

	if (KeyInput::GetKeyDown(KEY_INPUT_A))
	{
		if (KeyInput::GetKeyDown(KEY_INPUT_LSHIFT))
		{
			if (!isJump)
			{
				isDash = true;
				isWalk = false;
				isIdle = false;
			}
			else
			{
				isDash = false;
				isWalk = false;
				isIdle = false;
			}

			if (vec.x < MAX_MOVE_SPEED)
			{
				vec.x += MOVE_SPEED;
			}
		}
		else
		{
			if (!isJump)
			{
				isWalk = true;
				isIdle = false;
				isDash = false;
			}
			else
			{
				isWalk = false;
				isIdle = false;
				isDash = false;
			}

			vec.x = MOVE_SPEED;
		}

		if (angle <= CAMERA_ANGLE_0 - camera->GetHAngle())
		{
			angle = CAMERA_ANGLE_270 - camera->GetHAngle();
		}

		if (angle < CAMERA_ANGLE_270 - camera->GetHAngle())
		{
			angle += ROTATE_SPEED;
		}
		if (angle > CAMERA_ANGLE_270 - camera->GetHAngle())
		{
			angle -= ROTATE_SPEED;
		}

		if (KeyInput::GetKeyDown(KEY_INPUT_W))
		{
			angle = CAMERA_ANGLE_270 + ROTATE_SPEED - camera->GetHAngle();
		}
	}
	else if (KeyInput::GetKeyDown(KEY_INPUT_D))
	{
		if (KeyInput::GetKeyDown(KEY_INPUT_LSHIFT))
		{
			if (!isJump)
			{
				isDash = true;
				isWalk = false;
				isIdle = false;
			}
			else
			{
				isDash = false;
				isWalk = false;
				isIdle = false;
			}

			if (vec.x > -MAX_MOVE_SPEED)
			{
				vec.x -= MOVE_SPEED;
			}
		}
		else
		{
			if (!isJump)
			{
				isWalk = true;
				isIdle = false;
				isDash = false;
			}
			else
			{
				isWalk = false;
				isIdle = false;
				isDash = false;
			}

			vec.x = -MOVE_SPEED;
		}

		if (angle < CAMERA_ANGLE_90 - camera->GetHAngle())
		{
			angle += ROTATE_SPEED;
		}
		if (angle > CAMERA_ANGLE_90 - camera->GetHAngle())
		{
			angle -= ROTATE_SPEED;
		}
	}
	else
	{
		vec.x = 0.f;
	}

	radian = angle * DX_PI_F / 180.f;
	rotation = VGet(0.f, radian, 0.f);
	weaponRotation = VGet(0.f, radian, 0.f);

	if (KeyInput::GetKey(KEY_INPUT_SPACE))
	{
		isJump = true;
		isIdle = false;
		isWalk = false;
		isDash = false;

		jumpPower = 1.6f;

		vec.y = jumpPower;
	}

	//カメラの角度に合わせて移動量を算出する
	if (isWalk || isDash || isJump)
	{
		VECTOR moveVec;

		float sinPara = sinf(camera->GetHAngle() / 180.f * DX_PI_F);
		float cosPara = cosf(camera->GetHAngle() / 180.f * DX_PI_F);

		moveVec.x = vec.x * cosPara - vec.z * sinPara;
		moveVec.y = vec.y;
		moveVec.z = vec.x * sinPara + vec.z * cosPara;

		location = VAdd(location, moveVec);
	}	
	vec.y -= GRAVITY;
	if (location.y < 0)
	{
		isJump = false;
		jumpPower = 0.f;
		vec.y = 0.f;
		location.y = 0.f;
	}

}

void Player::Action()
{
	if (KeyInput::GetButtonDown(MOUSE_INPUT_RIGHT))
	{
		isGunHold = true;
	}
	else
	{
		isGunHold = false;
	}
}

void Player::Animation()
{
	animPlayTime += .5f;

	if (animPlayTime >= animTotalTime)
	{
		if (!isJump)
		{
			animPlayTime = 0.f;
		}
		else
		{
			isIdle = true;
		}
	}

	//待機アニメーションの読み込み
	if (isIdle && animState != playerAnim::Idle)
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
	if (isWalk && animState != playerAnim::Walk)
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
	if (isDash && animState != playerAnim::Dash)
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
	if (isJump && animState != playerAnim::Jump)
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
}
