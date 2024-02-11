#pragma once
#include"../../common.h"

class ModelManager
{
private:
	static ModelManager* model;			//�I�u�W�F�N�g

	std::map<std::string, int>handle;	//�n���h��
public:
	//�R���X�g���N�^
	ModelManager() {};

	//�f�X�g���N�^
	~ModelManager() {};

	//���f���}�l�[�W���[�̍쐬
	static void CreateModelManager();

	//���f���}�l�[�W���[�̍폜
	static void DeleteModleManager();

	//�n���h���Ƀ��f�����Z�b�g����
	static void SetModel(const char* fileName);

	//�n���h�����擾����
	static int GetModelHandle(const char* fileName) { return model->handle[fileName]; }
};

