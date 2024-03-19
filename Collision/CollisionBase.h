#pragma once
#include"DxLib.h"

enum CollisionType
{
	Empty = 0,		//��
	Obb				//�L�����E�{�b�N�X
};

class OBB;

class CollisionBase
{
protected:
	VECTOR location;			//���W
	VECTOR rotation;			//��]�l
	VECTOR vec;					//�ړ���

	CollisionType type;			//�R���W�����̎��
public:
	//�R���X�g���N�^
	CollisionBase();

	//�f�X�g���N�^
	~CollisionBase();

	//�����蔻��
	bool HitCheck(const CollisionBase* collision)const;

	//���W���擾����
	VECTOR GetLocation()const { return location; }

	//��]�l���擾����
	VECTOR GetRotation()const { return rotation; }

	//�x�N�g�����擾����
	VECTOR GetVec()const { return vec; }

	//�R���W�����̎�ނ��擾����
	CollisionType GetType()const { return type; }
	
protected:
	//OBB�Ƃ̓����蔻��
	virtual bool HitOBB(const OBB* obb)const = 0;

};

