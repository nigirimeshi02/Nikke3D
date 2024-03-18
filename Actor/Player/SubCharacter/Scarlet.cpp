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
	MovementAnimation(SCARLET);
}
