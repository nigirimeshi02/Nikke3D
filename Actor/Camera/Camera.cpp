#include"../../common.h"
#include"../../Scene/GameMain/GameMainScene.h"
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
}

Camera::~Camera()
{

}

void Camera::Update(GameMainScene* object)
{
	//�����_�̓L�����N�^�[�̍��W����CAMERA_LOOK_AT_HEIGHT�̕�������������
	if (object->GetPlayer()->GetActiveState() == Controller::Rapi)lookAtPosition = object->GetPlayer()->GetLocation();
	if (object->GetPlayer()->GetActiveState() == Controller::Scarlet)lookAtPosition = object->GetScarlet()->GetLocation();
	lookAtPosition.y += CAMERA_LOOK_AT_HEIGHT;

	//�J�����̈ʒu�̓J�����̐����p�x�Ɛ����p�x����Z�o

	vAngle += (float) - KeyInput::GetMouseVecY();
	hAngle += (float) - KeyInput::GetMouseVecX();

	//�N�����̒����p
	if (vAngle >= 0)
	{
		vAngle = -200.f;
	}

	//�ォ��̊p�x����
	if (vAngle > -90.5f)
	{
		vAngle = -90.5f;
	}
	//������̊p�x����
	if (vAngle < -269.5f)
	{
		vAngle = -269.5f;
	}
	
	lookAtDistance += -GetMouseWheelRotVolF() * 2;

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
