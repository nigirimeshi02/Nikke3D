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
	//min = VMult(min, scale);
	//各軸の最大値
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

	//中心点
	centerPoint = VScale(VAdd(min, max), 0.5f);

	directionLength.x = fabsf(max.x - min.x) * 0.5f;
	directionLength.y = fabsf(max.y - min.y) * 0.5f;
	directionLength.z = fabsf(max.z - min.z) * 0.5f;
}

bool OBB::HitOBB(const OBB* obb) const
{
	//各方向ベクトルの確保
	VECTOR NAe1 = GetDirectionVec(0), Ae1 = VScale(NAe1, directionLength.x);
	VECTOR NAe2 = GetDirectionVec(1), Ae2 = VScale(NAe2, directionLength.y);
	VECTOR NAe3 = GetDirectionVec(2), Ae3 = VScale(NAe3, directionLength.z);
	VECTOR NBe1 = GetDirectionVec(0), Be1 = VScale(NBe1, obb->GetDirectionLength().x);
	VECTOR NBe2 = GetDirectionVec(1), Be2 = VScale(NBe2, obb->GetDirectionLength().y);
	VECTOR NBe3 = GetDirectionVec(2), Be3 = VScale(NBe3, obb->GetDirectionLength().z);
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
