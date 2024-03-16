#pragma once
#include"DxLib.h"
#include"../CharaBase.h"
#include"../Weapon/Weapon.h"

class GameMainScene;

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

class Player :public CharaBase
{
private:
	Weapon::DesertEagle* handGun;	//�f�U�[�g�C�[�O���̃I�u�W�F�N�g

public:
	//�R���X�g���N�^
	Player();

	//�f�X�g���N�^
	~Player();

	//�X�V
	void Update(GameMainScene* object);

	//�`��
	void Draw()const;

	//�A�N�V����
	void Action();

	//�A�j���[�V����
	void Animation();

	//�f�U�[�g�C�[�O���̃I�u�W�F�N�g���擾����
	Weapon::DesertEagle* GetDesertEagle() { return handGun; }
};

