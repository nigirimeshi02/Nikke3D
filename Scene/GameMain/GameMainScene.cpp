#include"../../common.h"
#include "GameMainScene.h"

#define DEBUG

GameMainScene::GameMainScene()
{
	player = new Player();
	camera = new Camera();
	enemy = new Enemy();
	scarlet = new Scarlet();
}

GameMainScene::~GameMainScene()
{
	delete player;
	delete camera;
	delete enemy;
	delete scarlet;
}

SceneBase* GameMainScene::Update()
{
	SwitchCharacter();

	camera->Update(this);

	player->Update(this);

	enemy->Update(this);

	scarlet->Update(this);

	return this;
}

void GameMainScene::Draw() const
{
#ifdef DEBUG
	Ground();

	//x�͐ԐF
	DrawLine3D({ 0.f,0.f,0.f }, { 50.f,0.f,0.f }, X_AXIS_COLOR);
	//y�͗ΐF
	DrawLine3D({ 0.f,0.f,0.f }, { 0.f,50.f,0.f }, Y_AXIS_COLOR);
	//z�͐F
	DrawLine3D({ 0.f,0.f,0.f }, { 0.f,0.f,50.f }, Z_AXIS_COLOR);

#endif // DEBUG

	camera->Draw();

	player->Draw();

	enemy->Draw();

	scarlet->Draw();
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

void GameMainScene::SwitchCharacter()
{
	if(KeyInput::GetKey(KEY_INPUT_1))	
	{
		player->SetActiveState(Controller::Rapi);
	}
	if (KeyInput::GetKey(KEY_INPUT_2))
	{
		player->SetActiveState(Controller::Scarlet);
	}
}
