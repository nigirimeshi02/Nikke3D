#include "KeyInput.h"
#include<DxLib.h>

//�ÓI�����o�ϐ��̒�`
char KeyInput::now_key[MAX_KEY];
char KeyInput::old_key[MAX_KEY];
MOUSE_INPUT KeyInput::now_mouse;
MOUSE_INPUT KeyInput::old_mouse;

void KeyInput::Update()
{
	for (int i = 0; i < MAX_KEY; i++) 
	{
		old_key[i] = now_key[i];
	}

	old_mouse = now_mouse;
	//���݂̃}�E�X
	now_mouse.button = GetMouseInput();
	GetMousePoint(&now_mouse.x, &now_mouse.y);

	//���݂̃L�[
	GetHitKeyStateAll(now_key);

}

bool KeyInput::GetKey(int key)
{
	bool ret = (now_key[key] == TRUE) && (old_key[key] != TRUE);

	return ret;
}

bool KeyInput::GetKeyDown(int key)
{
	bool ret = (now_key[key] == TRUE) && (old_key[key] == TRUE);

	return ret;
}

bool KeyInput::GetKeyUp(int key)
{
	bool ret = (now_key[key] != TRUE) && (old_key[key] == TRUE);

	return ret;
}

int KeyInput::GetMouseLocationX()
{
	int ret = now_mouse.x;

	return ret;
}

int KeyInput::GetMouseLocationY()
{
	int ret = now_mouse.y;

	return ret;
}

bool KeyInput::GetButton(int key)
{
	bool ret = ~(old_mouse.button & key) & (now_mouse.button & key);

	return ret;
}

bool KeyInput::GetButtonDown(int key)
{
	bool ret = (old_mouse.button & key) & (now_mouse.button & key);

	return ret;
}

bool KeyInput::GetButtonUp(int key)
{
	bool ret = (old_mouse.button & key) & ~(now_mouse.button & key);

	return ret;
}