#pragma once
#include "DxLib.h"

class Enemy
{
private:
	int modelHandle;			//���f���̃n���h��

	int animIndex;				//�A�j���[�V�����̗v�f��

	int animState;				//�A�j���[�V�����̏��

	float animTotalTime;		//�A�j���[�V�����̑��Đ�����
	float animPlayTime;			//�A�j���[�V�����̍Đ�����

	float angle;				//�p�x
	float radian;				//���W�A��

	bool isIdle;				//�ҋ@���H
	bool isWalk;				//�����Ă���H
	bool isDash;				//�����Ă���H

	VECTOR location;			//���W
	VECTOR rotation;			//��]�l
	VECTOR vec;					//�ړ���

public:
	//�R���X�g���N�^
	Enemy();

	//�f�X�g���N�^
	~Enemy();

	//�X�V
	void Update();

	//�`��
	void Draw()const;

	//�ړ�
	void Movement();

	//�A�j���[�V����
	void Animation();

	//���W�̎擾
	VECTOR GetLocation() { return location; }

};



