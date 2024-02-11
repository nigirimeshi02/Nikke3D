#include "LoadScene.h"
#include"../../common.h"
#include"../GameMain/GameMainScene.h"

LoadScene::LoadScene()
{

}

LoadScene::~LoadScene()
{

}

SceneBase* LoadScene::Update()
{
	if (GetASyncLoadNum())
	{
		return this;
	}

	return new GameMainScene();
}

void LoadScene::Draw() const
{
	if (GetASyncLoadNum())
	{
		DrawFormatString(0, SCREEN_HEIGHT - 16, 0xffffff, "Now Loading");
	}
}
