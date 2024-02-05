#pragma once
#include"DxLib.h"

class SceneBase 
{
public:
	//�f�X�g���N�^
	virtual ~SceneBase() {};

	//�`��ȊO�̍X�V����������
	virtual SceneBase* Update() = 0;

	//�`��Ɋւ��邱�Ƃ���������
	virtual void Draw()const = 0;
};