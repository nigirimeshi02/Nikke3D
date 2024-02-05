#include"../../common.h"
#include "Enemy.h"
#include "../Player/Player.h"


Enemy::Enemy()
{
	//�R�c���f���̓ǂݍ���
	modelHandle = MV1LoadModel("Anis.fbm/Anis-Apose.pmx");

	angle = 0.f;
	radian = angle * DX_PI_F / 180.f;

	isIdle = true;
	isWalk = false;
	isDash = false;

	location = VGet(0.0f, 0.0f, 0.0f);
	rotation = VGet(0.0f, 0.0f, 0.0f);
	vec = VGet(0.0f, 0.0f, 0.0f);

	//�R�c���f���̃X�P�[����2.5�{�ɂ���
	MV1SetScale(modelHandle, VGet(3.0f, 3.0f, 3.0f));
}

Enemy::~Enemy()
{
	MV1DeleteModel(modelHandle);
}

void Enemy::Update()
{
	//���W���Z�b�g����
	MV1SetPosition(modelHandle, location);

	//��]�l���Z�b�g����
	MV1SetRotationXYZ(modelHandle, rotation);

	//�A�j���[�V����
	Animation();

	//�Đ����Ԃ��Z�b�g����
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

