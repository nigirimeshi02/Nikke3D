#include "CharaBase.h"
#include"../../Scene/GameMain/GameMainScene.h"
#include"../../common.h"

int CharaBase::activeState = Controller::Rapi;

CharaBase::CharaBase()
{

	animIndex = 0;
	animState = -1;
	activeState = Controller::Rapi;

	angle = CAMERA_ANGLE_0 * 2;
	radian = angle * DX_PI_F / 180.f;
	animPlayTime = 0.f;
	animTotalTime = 0.f;

	isIdle = true;
	isWalk = false;
	isDash = false;
	isJump = false;
	isGunHold = false;
	isAir = false;

	location = VGet(0.0f, 0.0f, 0.0f);
	rotation = VGet(0.0f, 0.0f, 0.0f);
	vec = VGet(0.0f, 0.0f, 0.0f);
}

CharaBase::~CharaBase()
{

}

void CharaBase::CharacterUpdate()
{
	//重力
	vec.y -= GRAVITY;
	location.y += vec.y;

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

void CharaBase::PlayerMovement(GameMainScene* object)
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

		angle = CAMERA_ANGLE_0 - object->GetCamera()->GetHAngle();
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

		angle = CAMERA_ANGLE_180 - object->GetCamera()->GetHAngle();
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

		angle = CAMERA_ANGLE_270 - object->GetCamera()->GetHAngle();

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
			angle = CAMERA_ANGLE_270 + ROTATE_SPEED - object->GetCamera()->GetHAngle();
		}
		if (KeyInput::GetKeyDown(KEY_INPUT_S))
		{
			angle = CAMERA_ANGLE_270 - ROTATE_SPEED - object->GetCamera()->GetHAngle();
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

		angle = CAMERA_ANGLE_90 - object->GetCamera()->GetHAngle();

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
			angle = CAMERA_ANGLE_90 - ROTATE_SPEED - object->GetCamera()->GetHAngle();
		}
		if (KeyInput::GetKeyDown(KEY_INPUT_S))
		{
			angle = CAMERA_ANGLE_90 + ROTATE_SPEED - object->GetCamera()->GetHAngle();
		}
	}
	else
	{
		vec.x = 0.f;
	}

	radian = angle * DX_PI_F / 180.f;
	rotation = VGet(0.f, radian, 0.f);
	object->GetPlayer()->GetDesertEagle()->SetRotationY(radian);

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

	float sinPara = sinf(object->GetCamera()->GetHAngle() / 180.f * DX_PI_F);
	float cosPara = cosf(object->GetCamera()->GetHAngle() / 180.f * DX_PI_F);

	moveVec.x = vec.x * cosPara - vec.z * sinPara;
	moveVec.y = vec.y;
	moveVec.z = vec.x * sinPara + vec.z * cosPara;

	location = VAdd(location, moveVec);
}
