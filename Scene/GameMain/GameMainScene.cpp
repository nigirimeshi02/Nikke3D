#include"../../common.h"
#include "GameMainScene.h"

GameMainScene::GameMainScene()
{
	player = new Player();
	camera = new Camera();
	enemy = new Enemy();
}

GameMainScene::~GameMainScene()
{
	delete player;
	delete camera;
	delete enemy;
}

SceneBase* GameMainScene::Update()
{
	camera->Update(player);

	player->Update(camera);

	enemy->Update();

	return this;
}

void GameMainScene::Draw() const
{
	Ground();

	camera->Draw();

	//player->Draw();

	enemy->Draw();
}

void GameMainScene::Ground() const
{
	int i;
	VECTOR pos1;
	VECTOR pos2;

	SetUseZBufferFlag(TRUE);

	pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
	pos2 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, LINE_AREA_SIZE / 2.0f);
	for (i = 0; i <= LINE_NUM; i++)
	{
		DrawLine3D(pos1, pos2, GetColor(255, 255, 255));
		pos1.x += LINE_AREA_SIZE / LINE_NUM;
		pos2.x += LINE_AREA_SIZE / LINE_NUM;
	}

	pos1 = VGet(-LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
	pos2 = VGet(LINE_AREA_SIZE / 2.0f, 0.0f, -LINE_AREA_SIZE / 2.0f);
	for (i = 0; i < LINE_NUM; i++)
	{
		DrawLine3D(pos1, pos2, GetColor(255, 255, 255));
		pos1.z += LINE_AREA_SIZE / LINE_NUM;
		pos2.z += LINE_AREA_SIZE / LINE_NUM;
	}

	SetUseZBufferFlag(FALSE);
}
