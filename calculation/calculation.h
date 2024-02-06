#pragma once
#include "../common.h"
#include "DxLib.h"
#include <math.h>

//ベクトルの長さ
float Get3DVectorLength(VECTOR v) {
	return sqrtf(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

//ベクトルの内積
float Get3DProduct(VECTOR v, VECTOR v1) {
	return v.x * v1.x + v.y * v1.y + v.z * v1.z;
}

//2つのベクトルの角度
float GetAngle2Vector(VECTOR v, VECTOR v1) {

	//長さ
	float length_a = Get3DVectorLength(v);
	float length_b = Get3DVectorLength(v1);
	if (length_a == 0 || length_b == 0) {
		return -1; //どちらかの長さが0だった場合失敗
	}

	//内積と長さからコサインを求める
	float cos = Get3DProduct(v, v1) / (length_a * length_b);

	//コサインからラジアンへ
	float angle = acosf(cos);

	//ラジアンからデグリー
	angle = r_d(angle);

	//デグリーで返す
	return angle;
}


