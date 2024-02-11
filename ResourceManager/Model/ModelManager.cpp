#include "ModelManager.h"
#include"../../common.h"

ModelManager* ModelManager::model = nullptr;

void ModelManager::CreateModelManager()
{
	//�I�u�W�F�N�g�쐬
	if (model == nullptr)
	{
		model = new ModelManager();
	}

	SetUseASyncLoadFlag(TRUE);

	//���f���̓ǂݍ���
	/**********�L�����N�^�[**********/
	SetModel(Rapi);
	SetModel(Anis);
	/**********����**********/
	SetModel(DesertEagle);
	SetModel(Sword);

	for (auto iterator = model->handle.begin(); iterator != model->handle.end(); ++iterator)
	{
		if (model->handle[iterator->first] == FuncError)
		{
			throw("���f�����ǂݍ��߂܂���ł����B\n");
		}
	}

	SetUseASyncLoadFlag(FALSE);
}

void ModelManager::DeleteModleManager()
{
	MV1InitModel();
	delete model;
	model = nullptr;
}

void ModelManager::SetModel(const char* fileName)
{
	//���[�J���ϐ��ɃL�[�̌������ʂ������
	auto iterator = model->handle.find(std::string(fileName));

	//�L�[��ݒ�
	if (iterator == model->handle.end())
	{
		//�t�@�C���̃p�X
		std::string path = "Resource/Model/" + std::string(fileName);

		//�L�[�ɓǂ݂���
		model->handle[fileName] = MV1LoadModel(path.c_str());
	}
}
