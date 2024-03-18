#include "Scarlet.h"
#include"../../common.h"
#include"../../ResourceManager/Model/ModelManager.h"

Scarlet::Scarlet()
{
	//3D���f���̃X�P�[����3�{�ɂ���
	MV1SetScale(ModelManager::GetModelHandle(SCARLET), VGet(3.0f, 3.0f, 3.0f));
}

Scarlet::~Scarlet()
{

}

void Scarlet::Update(GameMainScene* object)
{
	//���W���Z�b�g����
	MV1SetPosition(ModelManager::GetModelHandle(SCARLET), location);

	//��]�l���Z�b�g����
	MV1SetRotationXYZ(ModelManager::GetModelHandle(SCARLET), rotation);

	//�A�j���[�V����
	Animation();

	//�Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(ModelManager::GetModelHandle(SCARLET), animIndex, animPlayTime);

	if (activeState == Controller::Scarlet)
	{
		//�ړ�
		PlayerMovement(object);
	}

	//�X�V
	CharacterUpdate();

	//�s��
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
		MV1DetachAnim(ModelManager::GetModelHandle(SCARLET), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(SCARLET), scarletAnim::Idle, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(SCARLET), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = scarletAnim::Idle;
	}

	//�����A�j���[�V�����̓ǂݍ���
	if (isWalk && !isAir && animState != scarletAnim::Walk)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(SCARLET), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(SCARLET), scarletAnim::Walk, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(SCARLET), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = scarletAnim::Walk;
	}

	//����A�j���[�V�����̓ǂݍ���
	if (isDash && !isAir && animState != scarletAnim::Dash)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(SCARLET), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(SCARLET), scarletAnim::Dash, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(SCARLET), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = scarletAnim::Dash;
	}

	//�W�����v�A�j���[�V�����̓ǂݍ���
	if (isJump && !isDash && animState != scarletAnim::Jump && animState != scarletAnim::DashJump)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(SCARLET), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(SCARLET), scarletAnim::Jump, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(SCARLET), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = scarletAnim::Jump;
	}

	//�_�b�V���W�����v�̃A�j���[�V�����̓ǂݍ���
	if (isJump && isDash && animState != scarletAnim::DashJump && animState != scarletAnim::Jump)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(SCARLET), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(SCARLET), scarletAnim::DashJump, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(SCARLET), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 3.f;

		animState = scarletAnim::DashJump;
	}

	//�����̃A�j���[�V�����̓ǂݍ���
	if (isAir && !isJump && animState != scarletAnim::Fall)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(SCARLET), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(SCARLET), scarletAnim::Fall, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(SCARLET), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = scarletAnim::Fall;
	}
}
