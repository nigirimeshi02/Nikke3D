#pragma once

#define MAX_KEY 256

struct MOUSE_INPUT
{
	int button;
	int x;
	int y;
};

class KeyInput
{
private:
	static char now_key[MAX_KEY];
	static char old_key[MAX_KEY];
	static MOUSE_INPUT now_mouse;
	static MOUSE_INPUT old_mouse;
public:
	//更新処理
	static void Update();

	//キーを押したときを取得する
	static bool GetKey(int key);

	//キーを押しているとき取得する
	static bool GetKeyDown(int key);

	//キーを離したときを取得する
	static bool GetKeyUp(int key);

	//マウスのx座標を取得する
	static int GetMouseLocationX();

	//マウスのy座標を取得する
	static int GetMouseLocationY();
	
	//ボタンを押したときを取得する
	static bool GetButton(int key);

	//ボタンを押しているときを取得する
	static bool GetButtonDown(int key);

	//ボタンを離したときを取得する
	static bool GetButtonUp(int key);
};



