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
	//右肩
	int framNum1 = MV1SearchFrame(ModelManager::GetModelHandle(model), "右腕");
	//左肩
	int framNum2 = MV1SearchFrame(ModelManager::GetModelHandle(model), "左腕");
	//原点
	int framNum3 = MV1SearchFrame(ModelManager::GetModelHandle(model), "全ての親");
	//頭の上
	int framNum4 = MV1SearchFrame(ModelManager::GetModelHandle(model), "両目");
	//左足のつま先
	int framNum5 = MV1SearchFrame(ModelManager::GetModelHandle(model), "左つま先");
	//腰
	int framNum6 = MV1SearchFrame(ModelManager::GetModelHandle(model), "腰");

	//各軸の最小値
	VECTOR min = 
	{ 
		MV1GetFramePosition(ModelManager::GetModelHandle(model),framNum1).x,
		MV1GetFramePosition(ModelManager::GetModelHandle(model),framNum3).y,
		MV1GetFramePosition(ModelManager::GetModelHandle(model),framNum5).z
	};
	//各軸の最大値
	VECTOR max =
	{
		MV1GetFramePosition(ModelManager::GetModelHandle(model),framNum2).x,
		MV1GetFramePosition(ModelManager::GetModelHandle(model),framNum4).y,
		MV1GetFramePosition(ModelManager::GetModelHandle(model),framNum6).z
	};

	MATRIX matrixRotXYZ = MV1GetRotationMatrix(ModelManager::GetModelHandle(model));
	MATRIX matrixRotX = MGetRotX(d_r(rotation.x));
	MATRIX matrixRotY = MGetRotY(d_r(rotation.y));
	MATRIX matrixRotZ = MGetRotZ(d_r(rotation.z));

	directionVec[0] = VTransformSR(directionLength, matrixRotX);
	directionVec[1] = VTransformSR(directionLength, matrixRotY);
	directionVec[2] = VTransformSR(directionLength, matrixRotZ);

	//中心点
	centerPoint = VScale(VAdd(min, max), 0.5f);

	directionLength.x = (max.x - min.x) * 0.5f;
	directionLength.y = (max.y - min.y) * 0.5f;
	directionLength.z = (max.z - min.z) * 0.5f;
}

bool OBB::HitOBB(const OBB* obb) const
{
	//各方向ベクトルの確保
	VECTOR NAe1 = GetDirectionVec(0), Ae1 = VMult(NAe1, directionLength);
	VECTOR NAe2 = GetDirectionVec(1), Ae2 = VMult(NAe2, directionLength);
	VECTOR NAe3 = GetDirectionVec(2), Ae3 = VMult(NAe3, directionLength);
	VECTOR NBe1 = GetDirectionVec(0), Be1 = VMult(NBe1, obb->GetDirectionLength());
	VECTOR NBe2 = GetDirectionVec(1), Be2 = VMult(NBe2, obb->GetDirectionVec(1));
	VECTOR NBe3 = GetDirectionVec(2), Be3 = VMult(NBe3, obb->GetDirectionVec(2));
	//中心点間の距離
	VECTOR Interval = VSub(centerPoint, obb->GetCenterPoint());

	// 分離軸 : Ae1
	float rA = VSize(Ae1);
	float rB = VDotAdd3(NAe1, Be1, Be2, Be3);
	float L = fabs(VDot(Interval, NAe1));
	if (L > rA + rB)return false;	// 衝突していない

	// 分離軸 : Ae2
	rA = VSize(Ae2);
	rB = VDotAdd3(NAe2, Be1, Be2, Be3);
	L = fabs(VDot(Interval, NAe2));
	if (L > rA + rB)return false;

	// 分離軸 : Ae3
	rA = VSize(Ae3);
	rB = VDotAdd3(NAe3, Be1, Be2, Be3);
	L = fabs(VDot(Interval, NAe3));
	if (L > rA + rB)return false;

	// 分離軸 : Be1
	rA = VDotAdd3(NBe1, Ae1, Ae2, Ae3);
	rB = VSize(Be1);
	L = fabs(VDot(Interval, NBe1));
	if (L > rA + rB)return false;

	// 分離軸 : Be2
	rA = VDotAdd3(NBe2, Ae1, Ae2, Ae3);
	rB = VSize(Be2);
	L = fabs(VDot(Interval, NBe2));
	if (L > rA + rB)return false;

	// 分離軸 : Be3
	rA = VDotAdd3(NBe3, Ae1, Ae2, Ae3);
	rB = VSize(Be3);
	L = fabs(VDot(Interval, NBe3));
	if (L > rA + rB)return false;

	// 分離軸 : C11
	VECTOR Cross = VCross(NAe1, NBe1);
	rA = VDotAdd3(Cross, Ae2, Ae3);
	rB = VDotAdd3(Cross, Be2, Be3);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// 分離軸 : C12
	Cross = VCross(NAe1, NBe2);
	rA = VDotAdd3(Cross, Ae2, Ae3);
	rB = VDotAdd3(Cross, Be1, Be3);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// 分離軸 : C13
	Cross = VCross(NAe1, NBe3);
	rA = VDotAdd3(Cross, Ae2, Ae3);
	rB = VDotAdd3(Cross, Be1, Be2);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// 分離軸 : C21
	Cross = VCross(NAe2, NBe1);
	rA = VDotAdd3(Cross, Ae1, Ae3);
	rB = VDotAdd3(Cross, Be2, Be3);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// 分離軸 : C22
	Cross = VCross(NAe2, NBe2);
	rA = VDotAdd3(Cross, Ae1, Ae3);
	rB = VDotAdd3(Cross, Be1, Be3);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// 分離軸 : C23
	Cross = VCross(NAe2, NBe3);
	rA = VDotAdd3(Cross, Ae1, Ae3);
	rB = VDotAdd3(Cross, Be1, Be2);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// 分離軸 : C31
	Cross = VCross(NAe3, NBe1);
	rA = VDotAdd3(Cross, Ae1, Ae2);
	rB = VDotAdd3(Cross, Be2, Be3);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// 分離軸 : C32
	Cross = VCross(NAe3, NBe2);
	rA = VDotAdd3(Cross, Ae1, Ae2);
	rB = VDotAdd3(Cross, Be1, Be3);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// 分離軸 : C33
	Cross = VCross(NAe3, NBe3);
	rA = VDotAdd3(Cross, Ae1, Ae2);
	rB = VDotAdd3(Cross, Be1, Be2);
	L = fabs(VDot(Interval, Cross));
	if (L > rA + rB)return false;

	// 分離平面が存在しないので「衝突している」
	return true;
}
