#include "ModelManager.h"
#include"../../common.h"

ModelManager* ModelManager::model = nullptr;

void ModelManager::CreateModelManager()
{
	//オブジェクト作成
	if (model == nullptr)
	{
		model = new ModelManager();
	}

	SetUseASyncLoadFlag(TRUE);

	//モデルの読み込み
	/**********キャラクター**********/
	SetModel(Rapi);
	SetModel(Anis);
	/**********武器**********/
	SetModel(DesertEagle);
	SetModel(Sword);

	for (auto iterator = model->handle.begin(); iterator != model->handle.end(); ++iterator)
	{
		if (model->handle[iterator->first] == FuncError)
		{
			throw("モデルが読み込めませんでした。\n");
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
	//ローカル変数にキーの検索結果をいれる
	auto iterator = model->handle.find(std::string(fileName));

	//キーを設定
	if (iterator == model->handle.end())
	{
		//ファイルのパス
		std::string path = "Resource/Model/" + std::string(fileName);

		//キーに読みこむ
		model->handle[fileName] = MV1LoadModel(path.c_str());
	}
}
