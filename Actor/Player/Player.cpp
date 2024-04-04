#include"../../common.h"
#include "Player.h"
#include"../../ResourceManager/Model/ModelManager.h"
#include"../Weapon/Weapon.h"
#include"../../Scene/GameMain/GameMainScene.h"

Player::Player()
{
	handGun = new Weapon::DesertEagle();

	isHit = false;

	scale = VGet(3.f, 3.f, 3.f);

	//3D���f���̃X�P�[����3�{�ɂ���
	MV1SetScale(ModelManager::GetModelHandle(RAPI), scale);
	MV1SetScale(ModelManager::GetModelHandle(DESERT_EAGLE), VGet(3.0f, 3.0f, 3.0f));

}

Player::~Player()
{
	delete handGun;
}

void Player::Update(GameMainScene* object)
{
	//���W���Z�b�g����
	MV1SetPosition(ModelManager::GetModelHandle(RAPI), location);

	//��]�l���Z�b�g����
	MV1SetRotationXYZ(ModelManager::GetModelHandle(RAPI), rotation);

	//�A�j���[�V����
	Animation();

	//�Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(ModelManager::GetModelHandle(RAPI), animIndex, animPlayTime);

 	if (activeState == Controller::Rapi)
	{
		//�ړ�
		PlayerMovement(object);
	}

	//�X�V
	CharacterUpdate();

	//�s��
	Action();

	//����
	handGun->Update(object,RAPI);

	OBBUpdate(RAPI);

	if (HitCheck(object->GetScarlet()))
	{
		isHit = true;
	}
	else
	{
		isHit = false;
	}
}

void Player::Draw() const
{
	MV1DrawModel(ModelManager::GetModelHandle(RAPI));
	handGun->Draw();

	DrawFormatString(0, 0, 0xffffff, "x:%f", location.x);
	DrawFormatString(0, 10, 0xffffff, "y:%f", location.y);
	DrawFormatString(0, 20, 0xffffff, "z:%f", location.z);
	DrawFormatString(100, 0, 0xffffff, "isHit:%s", isHit ? "true" : "false");
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

void Player::Animation()
{
	animPlayTime += .5f;

	//�A�j���[�V�����̃��[�v
	if (animPlayTime >= animTotalTime)
	{
		//�W�����v���Ă��Ȃ����󒆂ɂ��Ȃ��Ȃ珉����
		if (!isJump&&!isAir)
		{
			animPlayTime = 0.f;
		}
		else
		{
			isJump = false;
		}
	}

	//�ҋ@�A�j���[�V�����̓ǂݍ���
	if (isIdle && !isAir && animState != playerAnim::Idle)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Idle, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Idle;
	}

	//�����A�j���[�V�����̓ǂݍ���
	if (isWalk && !isAir && animState != playerAnim::Walk)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Walk, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Walk;
	}

	//����A�j���[�V�����̓ǂݍ���
	if (isDash && !isAir && animState != playerAnim::Dash)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Dash, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Dash;
	}

	//�W�����v�A�j���[�V�����̓ǂݍ���
	if (isJump && !isDash && animState != playerAnim::Jump && animState != playerAnim::DashJump)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Jump, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Jump;
	}

	//�e���\����A�j���[�V�����̓ǂݍ���
	if (isGunHold && animState != playerAnim::GunHold)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::GunHold, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::GunHold;
	}

	//�_�b�V���W�����v�̃A�j���[�V�����̓ǂݍ���
	if (isJump && isDash && animState != playerAnim::DashJump && animState != playerAnim::Jump)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::DashJump, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 3.f;

		animState = playerAnim::DashJump;
	}

	//�����̃A�j���[�V�����̓ǂݍ���
	if (isAir && !isJump && animState != playerAnim::Fall)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Fall, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Fall;
	}
}