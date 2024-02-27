#include "LoadScene.h"
#include"../../common.h"
#include"../GameMain/GameMainScene.h"

LoadScene::LoadScene()
{
	SetBackgroundColor(230, 230, 230);

	maxNum = (float)GetASyncLoadNum();
	num = 0;

	bar = { 50,SCREEN_HEIGHT - 50 };
}

LoadScene::~LoadScene()
{
	SetBackgroundColor(128, 128, 128);
}

SceneBase* LoadScene::Update()
{
	num = (float)GetASyncLoadNum();

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
		DrawFormatString(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2, 0x888888, "Now Loading");

		DrawBox(bar.x, bar.y, bar.x + BARWIDTH, bar.y + BARHEIGHT, 0x000000, FALSE);

		DrawBox(bar.x, bar.y, bar.x + (bar.x + BARWIDTH - ((int)num * BARWIDTH / (int)maxNum)), bar.y + BARHEIGHT, 0x888888, TRUE);
		
		DrawFormatString(bar.x + BARWIDTH - 25, bar.y + BARHEIGHT + 8, 0x888888, "%.0f%%", ((maxNum - num) / maxNum) * 100);
	}
}
