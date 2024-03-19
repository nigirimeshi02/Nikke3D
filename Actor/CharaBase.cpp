#include "CharaBase.h"
#include"../../Scene/GameMain/GameMainScene.h"
#include"../../common.h"
#include"../../ResourceManager/Model/ModelManager.h"

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
}

CharaBase::~CharaBase()
{

}

void CharaBase::CharacterUpdate()
{
	//�d��
	vec.y -= GRAVITY;
	location.y += vec.y;

	//0��艺�ɂ͍s���Ȃ�
	if (location.y < 0)
	{
		isJump = false;
		isAir = false;
		vec.y = 0.f;
		location.y = 0.f;

		//�ړ��ʂ����ɖ߂�
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
	//0���傫���Ȃ��
	if (location.y > 0)
	{
		isAir = true;
	}
}

void CharaBase::PlayerMovement(GameMainScene* object)
{
	//�J�������猩�ĉ��ɐi��
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
	//�J�������猩�Ď�O�ɐi��
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

	//�J�������猩�č��ɐi��
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
	//�J�������猩�ĉE�ɐi��
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

		//�W�����v�͂��ړ��ʂɏ�Z
		vec.x *= JUMP_POWER;
		vec.z *= JUMP_POWER;

		vec.y = JUMP_POWER;
	}

	//�J�����̊p�x�ɍ��킹�Ĉړ��ʂ��Z�o����
	VECTOR moveVec;

	float sinPara = sinf(object->GetCamera()->GetHAngle() / 180.f * DX_PI_F);
	float cosPara = cosf(object->GetCamera()->GetHAngle() / 180.f * DX_PI_F);

	moveVec.x = vec.x * cosPara - vec.z * sinPara;
	moveVec.y = vec.y;
	moveVec.z = vec.x * sinPara + vec.z * cosPara;

	location = VAdd(location, moveVec);
}

void CharaBase::MovementAnimation(const char* character)
{
	animPlayTime += .5f;

	//�A�j���[�V�����̃��[�v
	if (animPlayTime >= animTotalTime)
	{
		//�W�����v���Ă��Ȃ����󒆂ɂ��Ȃ��Ȃ珉����
		if (!isJump && !isAir)
		{
			animPlayTime = 0.f;
		}
		else
		{
			isJump = false;
		}
	}

	//�ҋ@�A�j���[�V�����̓ǂݍ���
	if (isIdle && !isAir && animState != scarletAnim::Idle)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(character), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(character), scarletAnim::Idle, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(character), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = scarletAnim::Idle;
	}

	//�����A�j���[�V�����̓ǂݍ���
	if (isWalk && !isAir && animState != scarletAnim::Walk)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(character), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(character), scarletAnim::Walk, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(character), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = scarletAnim::Walk;
	}

	//����A�j���[�V�����̓ǂݍ���
	if (isDash && !isAir && animState != scarletAnim::Dash)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(character), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(character), scarletAnim::Dash, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(character), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = scarletAnim::Dash;
	}

	//�W�����v�A�j���[�V�����̓ǂݍ���
	if (isJump && !isDash && animState != scarletAnim::Jump && animState != scarletAnim::DashJump)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(character), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(character), scarletAnim::Jump, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(character), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = scarletAnim::Jump;
	}

	//�_�b�V���W�����v�̃A�j���[�V�����̓ǂݍ���
	if (isJump && isDash && animState != scarletAnim::DashJump && animState != scarletAnim::Jump)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(character), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(character), scarletAnim::DashJump, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(character), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 3.f;

		animState = scarletAnim::DashJump;
	}

	//�����̃A�j���[�V�����̓ǂݍ���
	if (isAir && !isJump && animState != scarletAnim::Fall)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(character), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(character), scarletAnim::Fall, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(character), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = scarletAnim::Fall;
	}
}
