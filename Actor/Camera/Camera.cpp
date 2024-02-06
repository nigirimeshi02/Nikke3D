#include"../../common.h"
#include "Camera.h"
#include"../Player/Player.h"
#include<algorithm>

Camera::Camera()
{		
	location = VGet(0.f, 0.f, 0.f);
	position1 = VGet(0.f, 0.f, 0.f);
	position2 = VGet(0.f, 0.f, 0.f);
	lookAtPosition = VGet(0.f, 0.f, 0.f);

	lookAtDistance = 100;

	vAngle = 0.f;
	hAngle = 0.f;

	sinPara = 0.f;
	cosPara = 0.f;

	//�}�E�X�̈ʒu��ݒ肷��
	SetMousePoint(720, 200);

	baseX = KeyInput::GetMouseLocationX();
	baseY = KeyInput::GetMouseLocationY();

	//�}�E�X�J�[�\����\�����Ȃ�
	SetMouseDispFlag(FALSE);
}

Camera::~Camera()
{

}

void Camera::Update(Player* player)
{
	//�����_�̓L�����N�^�[�̍��W����CAMERA_LOOK_AT_HEIGHT�̕�������������
	lookAtPosition = player->GetLocation();
	lookAtPosition.y += CAMERA_LOOK_AT_HEIGHT;

	//�J�����̈ʒu�̓J�����̐����p�x�Ɛ����p�x����Z�o

	vAngle = (float)baseY - KeyInput::GetMouseLocationY();
	hAngle = (float)baseX - KeyInput::GetMouseLocationX();

	if (hAngle < -1080)
	{
		SetMousePoint(720, KeyInput::GetMouseLocationY());
	}
	if (hAngle > -360)
	{
		SetMousePoint(720, KeyInput::GetMouseLocationY());
	}


	if (vAngle == 0)
	{
		vAngle = -205.f;
	}
	//�ォ��̊p�x����
	if (vAngle > -90.5f)
	{
		vAngle = -90.5f;
		SetMousePoint(KeyInput::GetMouseLocationX(), 90);
	}
	//������̊p�x����
	if (vAngle < -269.5f)
	{
		vAngle = -269.5f;
	}
	
	lookAtDistance += -GetMouseWheelRotVolF();

	//�ŏ��ɐ����p�x�𔽉f�����ʒu���Z�o
	sinPara = sinf(vAngle / 180.0f * DX_PI_F);
	cosPara = cosf(vAngle / 180.0f * DX_PI_F);
	position1.x = 0.0f;
	position1.y = sinPara * lookAtDistance;
	position1.z = -cosPara * lookAtDistance;

	// ���ɐ����p�x�𔽉f�����ʒu���Z�o
	sinPara = sinf(hAngle / 180.0f * DX_PI_F);
	cosPara = cosf(hAngle / 180.0f * DX_PI_F);
	position2.x = cosPara * position1.x - sinPara * position1.z;
	position2.y = position1.y;
	position2.z = sinPara * position1.x + cosPara * position1.z;

	// �Z�o�������W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
	location = VAdd(position2, lookAtPosition);

	// �J�����̐ݒ�ɔ��f����
	SetCameraPositionAndTarget_UpVecY(location, lookAtPosition);
}

void Camera::Draw() const
{
	DrawFormatString(300, 0, 0xff0000, "v:%f", vAngle);
}
