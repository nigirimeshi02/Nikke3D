#include"../../common.h"
#include "Player.h"
#include"../Camera/Camera.h"

Player::Player()
{
	//�R�c���f���̓ǂݍ���
	modelHandle = MV1LoadModel("Nikke-Rapi/nikke.pmx");

	angle = 0.f;
	radian = angle * DX_PI_F / 180.f;

	isIdle = false;
	isWalk = false;
	isDash = false;

	location = VGet(0.0f, 0.0f, 0.0f);
	rotation = VGet(0.0f, 0.0f, 0.0f);
	vec = VGet(0.0f, 0.0f, 0.0f);

	//�R�c���f���̃X�P�[����2.5�{�ɂ���
	MV1SetScale(modelHandle, VGet(3.0f, 3.0f, 3.0f));
}

Player::~Player()
{
	MV1DeleteModel(modelHandle);
}

void Player::Update(Camera* camera)
{
	//���W���Z�b�g����
	MV1SetPosition(modelHandle, location);

	//��]�l���Z�b�g����
	MV1SetRotationXYZ(modelHandle, rotation);

	//�A�j���[�V����
	Animation();

	//�Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(modelHandle, animIndex, animPlayTime);

	//�ړ�
	Movement(camera);
}

void Player::Draw() const
{
	MV1DrawModel(modelHandle);
}

void Player::Movement(Camera* camera)
{
	angle = camera->GetHAngle() / 360;

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

		angle += 360.f;
		radian = angle * DX_PI_F / 180.f;
		rotation = VGet(0, radian, 0);
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

		angle += 180.f;
		radian = angle * DX_PI_F / 180.f;
		rotation = VGet(0, radian, 0);
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

		angle += 270.f;
		radian = angle * DX_PI_F / 180.f;
		rotation = VGet(0, radian, 0);
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

		angle += 90.f;
		radian = angle * DX_PI_F / 180.f;
		rotation = VGet(0, radian, 0);
	}
	else
	{
		vec.x = 0.f;
	}

	location.x += vec.x;
	location.y += vec.y;
	location.z += vec.z;
}

void Player::Animation()
{
	animPlayTime += .5f;

	if (animPlayTime >= animTotalTime)
	{
		animPlayTime = MOVE_SPEED;
	}

	//�ҋ@�A�j���[�V�����̓ǂݍ���
	if (isIdle && animState != playerAnim::Idle)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(modelHandle, animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(modelHandle, playerAnim::Idle, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Idle;
	}

	//�����A�j���[�V�����̓ǂݍ���
	if (isWalk && animState != playerAnim::Walk)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(modelHandle, animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(modelHandle, playerAnim::Walk, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Walk;
	}

	//����A�j���[�V�����̓ǂݍ���
	if (isDash && animState != playerAnim::Dash)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(modelHandle, animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(modelHandle, playerAnim::Dash, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Dash;
	}
}
