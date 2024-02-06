#pragma once
#include "DxLib.h"
#include "../Player/Player.h"

class GameMainScene;

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
	VECTOR directionVec;		//�L�����N�^�[�̕����ێ�

	float speed;				//�X�s�[�h


	//�Ԃ��i���j
	int weaponModelHandle;
	int weaponAttachFrameNum;
	MATRIX matrix;
	VECTOR weaponLocation;
	

public:
	//�R���X�g���N�^
	Enemy();

	//�f�X�g���N�^
	~Enemy();

	//�X�V
	void Update(GameMainScene* gm);

	//�`��
	void Draw()const;

	//�ړ�
	void Movement();

	//�A�j���[�V����
	void Animation();

	//���W�̎擾
	VECTOR GetLocation() { return location; }

	//�p�x��ݒ�
	void SetRotation(Player* p);

	//�x�N�g��
	void SetVector(Player* p);


};



