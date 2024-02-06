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

	//マウスの位置を設定する
	SetMousePoint(720, 200);

	baseX = KeyInput::GetMouseLocationX();
	baseY = KeyInput::GetMouseLocationY();

	//マウスカーソルを表示しない
	SetMouseDispFlag(FALSE);
}

Camera::~Camera()
{

}

void Camera::Update(Player* player)
{
	//注視点はキャラクターの座標からCAMERA_LOOK_AT_HEIGHTの分だけ高くする
	lookAtPosition = player->GetLocation();
	lookAtPosition.y += CAMERA_LOOK_AT_HEIGHT;

	//カメラの位置はカメラの水平角度と垂直角度から算出

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
	//上からの角度制限
	if (vAngle > -90.5f)
	{
		vAngle = -90.5f;
		SetMousePoint(KeyInput::GetMouseLocationX(), 90);
	}
	//下からの角度制限
	if (vAngle < -269.5f)
	{
		vAngle = -269.5f;
	}
	
	lookAtDistance += -GetMouseWheelRotVolF();

	//最初に垂直角度を反映した位置を算出
	sinPara = sinf(vAngle / 180.0f * DX_PI_F);
	cosPara = cosf(vAngle / 180.0f * DX_PI_F);
	position1.x = 0.0f;
	position1.y = sinPara * lookAtDistance;
	position1.z = -cosPara * lookAtDistance;

	// 次に水平角度を反映した位置を算出
	sinPara = sinf(hAngle / 180.0f * DX_PI_F);
	cosPara = cosf(hAngle / 180.0f * DX_PI_F);
	position2.x = cosPara * position1.x - sinPara * position1.z;
	position2.y = position1.y;
	position2.z = sinPara * position1.x + cosPara * position1.z;

	// 算出した座標に注視点の位置を加算したものがカメラの位置
	location = VAdd(position2, lookAtPosition);

	// カメラの設定に反映する
	SetCameraPositionAndTarget_UpVecY(location, lookAtPosition);
}

void Camera::Draw() const
{
	DrawFormatString(300, 0, 0xff0000, "v:%f", vAngle);
}
