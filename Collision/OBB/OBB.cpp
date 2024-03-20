#include "OBB.h"
#include"../../ResourceManager/Model/ModelManager.h"
#include"../../common.h"

OBB::OBB()
{
	centerPoint = VGet(0.f, 0.f, 0.f);
	for (int i = 0; i < 3; i++)
	{
		directionVec[i] = VGet(0.f, 0.f, 0.f);
	}
	directionLength = VGet(0.f, 0.f, 0.f);

	type = Obb;
}

OBB::~OBB()
{

}

void OBB::UpdateOBB(const char* model)
{
	//�E��
	int framNum1 = MV1SearchFrame(ModelManager::GetModelHandle(model), "�E�r");
	//����
	int framNum2 = MV1SearchFrame(ModelManager::GetModelHandle(model), "���r");
	//���_
	int framNum3 = MV1SearchFrame(ModelManager::GetModelHandle(model), "�S�Ă̐e");
	//���̏�
	int framNum4 = MV1SearchFrame(ModelManager::GetModelHandle(model), "����");
	//�����̂ܐ�
	int framNum5 = MV1SearchFrame(ModelManager::GetModelHandle(model), "���ܐ�");
	//��
	int framNum6 = MV1SearchFrame(ModelManager::GetModelHandle(model), "��");

	//�e���̍ŏ��l
	VECTOR min = 
	{ 
		MV1GetFramePosition(ModelManager::GetModelHandle(model),framNum1).x,
		MV1GetFramePosition(ModelManager::GetModelHandle(model),framNum3).y,
		MV1GetFramePosition(ModelManager::GetModelHandle(model),framNum5).z
	};
	//min = VMult(min, scale);
	//�e���̍ő�l
	VECTOR max =
	{
		MV1GetFramePosition(ModelManager::GetModelHandle(model),framNum2).x,
		MV1GetFramePosition(ModelManager::GetModelHandle(model),framNum4).y,
		MV1GetFramePosition(ModelManager::GetModelHandle(model),framNum6).z
	};
	//max = VMult(max, scale);

	//MATRIX matrixRotX = MGetRotX(d_r(rotation.x));
	//MATRIX matrixRotY = MGetRotY(d_r(rotation.y));
	//MATRIX matrixRotZ = MGetRotZ(d_r(rotation.z));

	MATRIX matrixRot = MV1GetMatrix(ModelManager::GetModelHandle(RAPI));
	//CreateIdentityMatrix(&matrixRot);
	//CreateRotationYXZMatrix(&matrixRot, d_r(rotation.y), d_r(rotation.x), d_r(rotation.z));
	
	directionVec[0] = { matrixRot.m[0][0],matrixRot.m[0][1],matrixRot.m[0][2] };
	directionVec[1] = { matrixRot.m[1][0],matrixRot.m[1][1],matrixRot.m[1][2] };
	directionVec[2] = { matrixRot.m[2][0],matrixRot.m[2][1],matrixRot.m[2][2] };

	//���S�_
	centerPoint = VScale(VAdd(min, max), 0.5f);

	directionLength.x = fabsf(max.x - min.x) * 0.5f;
	directionLength.y = fabsf(max.y - min.y) * 0.5f;
	directionLength.z = fabsf(max.z - min.z) * 0.5f;
}

bool OBB::HitOBB(const OBB* obb) const
{
	//�e�����x�N�g���̊m��
	VECTOR NAe1 = GetDirectionVec(0), Ae1 = VScale(NAe1, directionLength.x);
	VECTOR NAe2 = GetDirectionVec(1), Ae2 = VScale(NAe2, directionLength.y);
	VECTOR NAe3 = GetDirectionVec(2), Ae3 = VScale(NAe3, directionLength.z);
	VECTOR NBe1 = GetDirectionVec(0), Be1 = VScale(NBe1, obb->GetDirectionLength().x);
	VECTOR NBe2 = GetDirectionVec(1), Be2 = VScale(NBe2, obb->GetDirectionLength().y);
	VECTOR NBe3 = GetDirectionVec(2), Be3 = VScale(NBe3, obb->GetDirectionLength().z);
	//���S�_�Ԃ̋���
	VECTOR Interval = VSub(centerPoint, obb->GetCenterPoint());

	// ������ : Ae1
	float rA = VSize(Ae1);
	float rB = VDotAdd3(NAe1, Be1, Be2, Be3);
	float L = fabs(VDot(Interval, NAe1));
	if (L > rA + rB)return false;	// �Փ˂��Ă��Ȃ�

	// ������ : Ae2
	rA = VSize(Ae2);
	rB = VDotAdd3(NAe2, Be1, Be2, Be3);
	L = fabs(VDot(Interval, NAe2));
	if (L > rA + rB)return false;

	// ������ : Ae3
	rA = VSize(Ae3);
	rB = VDotAdd3(NAe3, Be1, Be2, Be3);
	L = fabs(VDot(Interval, NAe3));
	if (L > rA + rB)return false;

	// ������ : Be1
	rA = VDotAdd3(NBe1, Ae1, Ae2, Ae3);
	rB = VSize(Be1);
	L = fabs(VDot(Interval, NBe1));
	if (L > rA + rB)return false;

	// ������ : Be2
	rA = VDotAdd3(NBe2, Ae1, Ae2, Ae3);
	rB = VSize(Be2);
	L = fabs(VDot(Interval, NBe2));
	if (L > rA + rB)return false;

	// ������ : Be3
	rA = VDotAdd3(NBe3, Ae1, Ae2, Ae3);
	rB = VSize(Be3);
	L = fabs(VDot(Interval, NBe3));
	if (L > rA + rB)return false;

	// ������ : C11
	VECTOR Cross = VCross(NAe1, NBe1);
	rA = VDotAdd3(Cross, Ae2, Ae3);
	rB = VDotAdd3(Cross, Be2, Be3);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// ������ : C12
	Cross = VCross(NAe1, NBe2);
	rA = VDotAdd3(Cross, Ae2, Ae3);
	rB = VDotAdd3(Cross, Be1, Be3);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// ������ : C13
	Cross = VCross(NAe1, NBe3);
	rA = VDotAdd3(Cross, Ae2, Ae3);
	rB = VDotAdd3(Cross, Be1, Be2);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// ������ : C21
	Cross = VCross(NAe2, NBe1);
	rA = VDotAdd3(Cross, Ae1, Ae3);
	rB = VDotAdd3(Cross, Be2, Be3);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// ������ : C22
	Cross = VCross(NAe2, NBe2);
	rA = VDotAdd3(Cross, Ae1, Ae3);
	rB = VDotAdd3(Cross, Be1, Be3);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// ������ : C23
	Cross = VCross(NAe2, NBe3);
	rA = VDotAdd3(Cross, Ae1, Ae3);
	rB = VDotAdd3(Cross, Be1, Be2);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// ������ : C31
	Cross = VCross(NAe3, NBe1);
	rA = VDotAdd3(Cross, Ae1, Ae2);
	rB = VDotAdd3(Cross, Be2, Be3);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// ������ : C32
	Cross = VCross(NAe3, NBe2);
	rA = VDotAdd3(Cross, Ae1, Ae2);
	rB = VDotAdd3(Cross, Be1, Be3);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// ������ : C33
	Cross = VCross(NAe3, NBe3);
	rA = VDotAdd3(Cross, Ae1, Ae2);
	rB = VDotAdd3(Cross, Be1, Be2);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	return true;
}
