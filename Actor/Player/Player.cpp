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

	angle = CAMERA_ANGLE_0 * 2;
	radian = angle * DX_PI_F / 180.f;

	isIdle = false;
	isWalk = false;
	isDash = false;
	isJump = false;
	isGunHold = false;
	isAir = false;

	location = VGet(0.0f, 0.0f, 0.0f);
	weaponLocation = VGet(0.0f, 0.0f, 0.0f);
	rotation = VGet(0.0f, 0.0f, 0.0f);
	weaponRotation = VGet(0.0f, 0.0f, 0.0f);
	vec = VGet(0.0f, 0.0f, 0.0f);

	//３Ｄモデルのスケールを3倍にする
	MV1SetScale(ModelManager::GetModelHandle(RAPI), VGet(3.0f, 3.0f, 3.0f));
	MV1SetScale(ModelManager::GetModelHandle(DESERT_EAGLE), VGet(3.0f, 3.0f, 3.0f));

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
	WeaponUpdate(camera);
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
	//カメラから見て奥に進む
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

			vec.z = -MOVE_SPEED;
		}

		angle = CAMERA_ANGLE_0 - camera->GetHAngle();
	}
	//カメラから見て手前に進む
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

			vec.z = MOVE_SPEED;
		}

		angle = CAMERA_ANGLE_180 - camera->GetHAngle();
	}
	else
	{
		isIdle = true;
		isWalk = false;
		isDash = false;
		vec.z = 0.f;
	}

	//カメラから見て左に進む
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

			vec.x = MOVE_SPEED;
		}

		angle = CAMERA_ANGLE_270 - camera->GetHAngle();

		//if (angle <= CAMERA_ANGLE_0 - camera->GetHAngle())
		//{
		//	angle = CAMERA_ANGLE_270 - camera->GetHAngle();
		//}

		//if (angle < CAMERA_ANGLE_270 - camera->GetHAngle())
		//{
		//	angle += ROTATE_SPEED;
		//}
		//if (angle > CAMERA_ANGLE_270 - camera->GetHAngle())
		//{
		//	angle -= ROTATE_SPEED;
		//}

		if (KeyInput::GetKeyDown(KEY_INPUT_W))
		{
			angle = CAMERA_ANGLE_270 + ROTATE_SPEED - camera->GetHAngle();
		}
		if (KeyInput::GetKeyDown(KEY_INPUT_S))
		{
			angle = CAMERA_ANGLE_270 - ROTATE_SPEED - camera->GetHAngle();
		}
	}
	//カメラから見て右に進む
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

			vec.x = -MOVE_SPEED;
		}

		angle = CAMERA_ANGLE_90 - camera->GetHAngle();

		//if (angle < CAMERA_ANGLE_90 - camera->GetHAngle())
		//{
		//	angle += ROTATE_SPEED;
		//}
		//if (angle > CAMERA_ANGLE_90 - camera->GetHAngle())
		//{
		//	angle -= ROTATE_SPEED;
		//}
		if (KeyInput::GetKeyDown(KEY_INPUT_W))
		{
			angle = CAMERA_ANGLE_90 - ROTATE_SPEED - camera->GetHAngle();
		}
		if (KeyInput::GetKeyDown(KEY_INPUT_S))
		{
			angle = CAMERA_ANGLE_90 + ROTATE_SPEED - camera->GetHAngle();
		}
	}
	else
	{
		vec.x = 0.f;
	}

	radian = angle * DX_PI_F / 180.f;
	rotation = VGet(0.f, radian, 0.f);
	weaponRotation.y = radian;

	if (KeyInput::GetKeyDown(KEY_INPUT_SPACE) && !isAir)
	{
		isJump = true;
		isAir = true;

		//ジャンプ力を移動量に乗算
		vec.x *= JUMP_POWER;
		vec.z *= JUMP_POWER;

		vec.y = JUMP_POWER;
	}

	//カメラの角度に合わせて移動量を算出する
	VECTOR moveVec;

	float sinPara = sinf(camera->GetHAngle() / 180.f * DX_PI_F);
	float cosPara = cosf(camera->GetHAngle() / 180.f * DX_PI_F);

	moveVec.x = vec.x * cosPara - vec.z * sinPara;
	moveVec.y = vec.y;
	moveVec.z = vec.x * sinPara + vec.z * cosPara;

	location = VAdd(location, moveVec);

	//重力
	vec.y -= GRAVITY;

	//0より下には行けない
	if (location.y < 0)
	{
		isJump = false;
		isAir = false;
		vec.y = 0.f;
		location.y = 0.f;

		//移動量を元に戻す
		if (vec.x > MAX_MOVE_SPEED)
		{
			vec.x = MAX_MOVE_SPEED;
		}
		else if (vec.x < -MAX_MOVE_SPEED)
		{
			vec.x = -MAX_MOVE_SPEED;
		}
		if (vec.z > MAX_MOVE_SPEED)
		{
			vec.z = MAX_MOVE_SPEED;
		}
		else if (vec.z < -MAX_MOVE_SPEED)
		{
			vec.z = -MAX_MOVE_SPEED;
		}
	}
	//0より大きいなら空中
	if (location.y > 0)
	{
		isAir = true;
	}
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

void Player::WeaponUpdate(Camera* camera)
{
	//手のひら
	int framNum1 = MV1SearchFrame(ModelManager::GetModelHandle(RAPI), "右手先");
	//中指
	int framNum2 = MV1SearchFrame(ModelManager::GetModelHandle(RAPI), "右中指１");
	//ハンマーピン
	int framNum3 = MV1SearchFrame(ModelManager::GetModelHandle(DESERT_EAGLE), "ハンマーピン");
	//銃口
	int framNum4 = MV1SearchFrame(ModelManager::GetModelHandle(DESERT_EAGLE), "銃口");	

	//手のひらの座標
	VECTOR framPoint1 = MV1GetFramePosition(ModelManager::GetModelHandle(RAPI), framNum1);
	//中指の座標
	VECTOR framPoint2 = MV1GetFramePosition(ModelManager::GetModelHandle(RAPI), framNum2);
	//ハンマーピンの座標
	VECTOR framPoint3 = MV1GetFramePosition(ModelManager::GetModelHandle(DESERT_EAGLE), framNum3);
	//銃口の座標
	VECTOR framPoint4 = MV1GetFramePosition(ModelManager::GetModelHandle(DESERT_EAGLE), framNum4);

	//手のひらと中指のベクトル
	VECTOR framPointVec1 = VSub(framPoint1, framPoint2);
	//ハンマーピンと銃口のベクトル
	VECTOR framPointVec2 = VSub(framPoint3, framPoint4);
	//手のひらと銃口のベクトル
	VECTOR framPointVec3 = VSub(framPoint1, framPoint4);

	//手のひらと中指の単位ベクトル
	VECTOR Identity1 = VNorm(framPointVec1);
	//ハンマーピンと銃口の単位ベクトル
	VECTOR Identity2 = VNorm(framPointVec2);
	//手のひらと銃口の単位ベクトル
	VECTOR Identity3 = VNorm(framPointVec3);

	//2つのベクトルの角度
	float handGunRadX = asin(VDot(Identity1, Identity2));
	float handGunRadZ = acos(VDot(Identity2, Identity3));

	weaponLocation = framPoint1;

	if (isGunHold)
	{
		float radianY = 16.f * DX_PI_F / 180.f;

		weaponLocation = VGet(weaponLocation.x, weaponLocation.y + 1.f, weaponLocation.z);
		weaponRotation = VGet(0.f, radian - radianY, 0.f);
	}
	else
	{
		weaponLocation = VGet(weaponLocation.x, weaponLocation.y, weaponLocation.z);
		weaponRotation = VGet(-handGunRadX, this->radian, -handGunRadZ);
	}

	//X軸→Z軸→Y軸の順番に回転させる
	MV1SetMatrix(ModelManager::GetModelHandle(DESERT_EAGLE),
		MMult(MMult(MGetScale(VGet(3.f, 3.f, 3.f))
			, MMult(MMult(MGetRotX(weaponRotation.x), MGetRotZ(weaponRotation.z))
				, MGetRotY(weaponRotation.y)))
			, MGetTranslate(weaponLocation)));
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