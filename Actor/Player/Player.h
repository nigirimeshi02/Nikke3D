#pragma once
#include"DxLib.h"

#define MOVE_SPEED		1.5f	//�ړ��̑��x	
#define MAX_MOVE_SPEED	3.0f	//�ړ��̍ō����x
#define ROTATE_SPEED	45.f	//��]���x
#define GRAVITY			0.06f	//�������x
#define JUMP_POWER		1.6f	//�W�����v��

class Camera;

namespace playerAnim
{
	enum Animation
	{
		Dance = 0,			//���邭��
		Idle,				//�ҋ@
		Walk,				//����
		Dash,				//����
		Jump,				//�W�����v
		GunHold,			//�ˌ��̐�
		DashJump,			//�_�b�V���W�����v
		Fall				//����
	};
}

class Player
{
private:
	int animIndex;				//�A�j���[�V�����̗v�f��

	int animState;				//�A�j���[�V�����̏��

	float animTotalTime;		//�A�j���[�V�����̑��Đ�����
	float animPlayTime;			//�A�j���[�V�����̍Đ�����

	float angle;				//�p�x
	float radian;				//���W�A��

	bool isIdle;				//�ҋ@���H
	bool isWalk;				//�����Ă���H
	bool isDash;				//�����Ă���H
	bool isJump;				//���ł���H
	bool isGunHold;				//�\���Ă���H
	bool isAir;					//��?

	VECTOR location;			//���W
	VECTOR weaponLocation;		//����̍��W
	VECTOR rotation;			//��]�l
	VECTOR weaponRotation;		//����̉�]�l
	VECTOR vec;					//�ړ���

public:
	//�R���X�g���N�^
	Player();

	//�f�X�g���N�^
	~Player();

	//�X�V
	void Update(Camera* camera);

	//�`��
	void Draw()const;

	//�ړ�
	void Movement(Camera* camera);

	//�A�N�V����
	void Action();

	//����̍X�V
	void WeaponUpdate(Camera* camera);

	//�A�j���[�V����
	void Animation();

	//���W���擾����
	VECTOR GetLocation() { return location; }

	//�x�N�g�����擾����
	VECTOR GetVec() { return vec; }
};

