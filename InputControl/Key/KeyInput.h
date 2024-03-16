#pragma once
#include"../../common.h"

#define MAX_KEY 256
#define MOUSE_OFFSET_X SCREEN_WIDTH	/ 2
#define MOUSE_OFFSET_Y SCREEN_HEIGHT / 2

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
	static MOUSE_INPUT mouse_vec;
	static float mouse_sensitivity;
public:
	//�X�V����
	static void Update();

	//�L�[���������Ƃ����擾����
	static bool GetKey(int key);

	//�L�[�������Ă���Ƃ��擾����
	static bool GetKeyDown(int key);

	//�L�[�𗣂����Ƃ����擾����
	static bool GetKeyUp(int key);

	//�}�E�X��x���W���擾����
	static int GetMouseLocationX();

	//�}�E�X��y���W���擾����
	static int GetMouseLocationY();

	//�}�E�X�̈ړ���x���擾����
	static int GetMouseVecX();

	//�}�E�X�̈ړ���y���擾����
	static int GetMouseVecY();
	
	//�{�^�����������Ƃ����擾����
	static bool GetButton(int key);

	//�{�^���������Ă���Ƃ����擾����
	static bool GetButtonDown(int key);

	//�{�^���𗣂����Ƃ����擾����
	static bool GetButtonUp(int key);
};



