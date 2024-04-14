#pragma once
#include"../../common.h"

class ModelManager
{
private:
	static ModelManager* model;			//オブジェクト

	std::map<std::string, int>handle;	//ハンドル
public:
	//コンストラクタ
	ModelManager() {};

	//デストラクタ
	~ModelManager() {};

	//モデルマネージャーの作成
	static void CreateModelManager();

	//モデルマネージャーの削除
	static void DeleteModleManager();

	//ハンドルにモデルをセットする
	static void SetModel(const char* fileName);

	//ハンドルを取得する
	static int GetModelHandle(const char* fileName) { return model->handle[fileName]; }
};

