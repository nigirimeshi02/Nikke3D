#pragma once
#include"DxLib.h"

#define BUTTON 16
#define QUARTER 32767*0.25

struct Stick
{
	short x;	//縦軸
	short y;	//横軸
};

class PadInput
{
private:
	static char now_key[BUTTON];	//今回のキー
	static char old_key[BUTTON];	//前回のキー
	static XINPUT_STATE input;		//パッド情報
	static Stick l_stick;			//左スティック
	static Stick r_stick;			//右スティック
private:
	PadInput() = default;
public:
	//更新処理
	static void Update()
	{
		//入力キー取得
		GetJoypadXInputState(DX_INPUT_KEY_PAD1, &input);

		for (int i = 0; i < BUTTON; i++)
		{
			old_key[i] = now_key[i];
			now_key[i] = input.Buttons[i];
		}

		//左スティック
		l_stick.x = input.ThumbLX;
		l_stick.y = input.ThumbLY;

		//右スティック
		r_stick.x = input.ThumbRX;
		r_stick.y = input.ThumbRY;
	}

	//ボタンを押したとき
	static bool OnButton(int button)
	{
		bool ret = (now_key[button] == TRUE && old_key[button] == FALSE);
		return ret;
	}

	//ボタンを押しているとき
	static bool OnPressed(int button)
	{
		bool ret = (now_key[button] == TRUE);
		return ret;
	}

	//ボタンを離したとき
	static bool OnRelease(int button)
	{
		bool ret = (now_key[button] == FALSE && old_key[button] == TRUE);
		return ret;
	}

	//右スティックの取得
	static Stick GetRStick()
	{
		return r_stick;
	}

	//左スティックの取得
	static Stick GetLStick()
	{
		return l_stick;
	}

	static char GetOldKey(const int i)
	{
		return old_key[i];
	}

	static char GetNowKey(const int i)
	{
		return now_key[i];
	}
};

