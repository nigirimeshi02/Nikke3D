#pragma once
#include"DxLib.h"

#define ANIMATION_INDEX 4		//�A�j���[�V�����̐�
#define MOVE_SPEED		0.5f	//�ړ��̑��x	
#define MAX_MOVE_SPEED	2.0f	//�ړ��̍ō����x
#define ROTATE_SPEED	45.f	//��]���x
#define GRAVITY			9.8f	//�d��

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
		GunHold				//�ˌ��̐�
	};
}

class Player
{
private:
	int weaponAttachFrameNum;	//������A�^�b�`����t���[���̔ԍ�

	int animIndex;				//�A�j���[�V�����̗v�f��

	int animState;				//�A�j���[�V�����̏��

	float animTotalTime;		//�A�j���[�V�����̑��Đ�����
	float animPlayTime;			//�A�j���[�V�����̍Đ�����

	float jumpPower;

	float angle;				//�p�x
	float radian;				//���W�A��

	bool isIdle;				//�ҋ@���H
	bool isWalk;				//�����Ă���H
	bool isDash;				//�����Ă���H
	bool isJump;				//���ł���H
	bool isGunHold;				//�\���Ă���H

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

	void Action();

	//�A�j���[�V����
	void Animation();

	//���W���擾����
	VECTOR GetLocation() { return location; }

	//�x�N�g�����擾����
	VECTOR GetVec() { return vec; }
};

