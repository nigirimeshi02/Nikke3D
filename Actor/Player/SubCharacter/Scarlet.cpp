#include "Scarlet.h"
#include"../../common.h"
#include"../../ResourceManager/Model/ModelManager.h"

Scarlet::Scarlet()
{
	//3Dモデルのスケールを3倍にする
	MV1SetScale(ModelManager::GetModelHandle(SCARLET), VGet(3.0f, 3.0f, 3.0f));
}

Scarlet::~Scarlet()
{

}

void Scarlet::Update(GameMainScene* object)
{
	//座標をセットする
	MV1SetPosition(ModelManager::GetModelHandle(SCARLET), location);

	//回転値をセットする
	MV1SetRotationXYZ(ModelManager::GetModelHandle(SCARLET), rotation);

	//アニメーション
	Animation();

	//再生時間をセットする
	MV1SetAttachAnimTime(ModelManager::GetModelHandle(SCARLET), animIndex, animPlayTime);

	if (activeState == Controller::Scarlet)
	{
		//移動
		PlayerMovement(object);
	}

	//更新
	CharacterUpdate();

	//行動
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
