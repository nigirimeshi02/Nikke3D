#pragma once
#include"DxLib.h"

#define BUTTON 16
#define QUARTER 32767*0.25

struct Stick
{
	short x;	//�c��
	short y;	//����
};

class PadInput
{
private:
	static char now_key[BUTTON];	//����̃L�[
	static char old_key[BUTTON];	//�O��̃L�[
	static XINPUT_STATE input;		//�p�b�h���
	static Stick l_stick;			//���X�e�B�b�N
	static Stick r_stick;			//�E�X�e�B�b�N
private:
	PadInput() = default;
public:
	//�X�V����
	static void Update()
	{
		//���̓L�[�擾
		GetJoypadXInputState(DX_INPUT_KEY_PAD1, &input);

		for (int i = 0; i < BUTTON; i++)
		{
			old_key[i] = now_key[i];
			now_key[i] = input.Buttons[i];
		}

		//���X�e�B�b�N
		l_stick.x = input.ThumbLX;
		l_stick.y = input.ThumbLY;

		//�E�X�e�B�b�N
		r_stick.x = input.ThumbRX;
		r_stick.y = input.ThumbRY;
	}

	//�{�^�����������Ƃ�
	static bool OnButton(int button)
	{
		bool ret = (now_key[button] == TRUE && old_key[button] == FALSE);
		return ret;
	}

	//�{�^���������Ă���Ƃ�
	static bool OnPressed(int button)
	{
		bool ret = (now_key[button] == TRUE);
		return ret;
	}

	//�{�^���𗣂����Ƃ�
	static bool OnRelease(int button)
	{
		bool ret = (now_key[button] == FALSE && old_key[button] == TRUE);
		return ret;
	}

	//�E�X�e�B�b�N�̎擾
	static Stick GetRStick()
	{
		return r_stick;
	}

	//���X�e�B�b�N�̎擾
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

