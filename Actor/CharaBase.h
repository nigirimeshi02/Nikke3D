#pragma once
#include"DxLib.h"
#include"../Collision/OBB/OBB.h"

#define MOVE_SPEED		1.5f	//�ړ��̑��x	
#define MAX_MOVE_SPEED	3.0f	//�ړ��̍ō����x
#define ROTATE_SPEED	45.f	//��]���x
#define GRAVITY			0.06f	//�������x
#define JUMP_POWER		1.6f	//�W�����v��

class GameMainScene;

namespace Controller
{
	enum State
	{
		Rapi = 0,
		Scarlet
	};
}

class CharaBase :public OBB
{
protected:
	int animIndex;				//�A�j���[�V�����̗v�f
	int animState;				//�A�j���[�V�����̏��
	static int activeState;		//������

	float angle;				//�p�x
	float radian;				//���W�A��
	float animTotalTime;		//�A�j���[�V�����̑��Đ�����
	float animPlayTime;			//�A�j���[�V�����̍Đ�����

	bool isIdle;				//�ҋ@���H
	bool isWalk;				//�����Ă���H
	bool isDash;				//�����Ă���H
	bool isJump;				//���ł���H
	bool isGunHold;				//�\���Ă���H
	bool isAir;					//��?

public:
	//�R���X�g���N�^
	CharaBase();

	//�f�X�g���N�^
	~CharaBase();

	//�X�V
	virtual void Update(GameMainScene* object) = 0;

	//�`��
	virtual void Draw()const = 0;
	
private:
	//�A�N�V����
	virtual void Action() = 0;

	//�A�j���[�V����
	virtual void Animation() = 0;

public:
	//���W�A�����擾����
	float GetRadian()const { return radian; }

	//�\���Ă��邩�ǂ����擾����
	bool GetGunHold()const { return isGunHold; }

	//�����Ԃ̎擾
	int GetActiveState()const { return activeState; }

	//�����Ԃ̐ݒ�
	void SetActiveState(const Controller::State character)
	{
		activeState = character;
	}

protected:
	//�L�����N�^�[�̍X�V����
	void CharacterUpdate();

	//�v���C���[�̈ړ�����
	void PlayerMovement(GameMainScene* object);

	//�ړ��̃A�j���[�V����
	void MovementAnimation(const char* character);
};

