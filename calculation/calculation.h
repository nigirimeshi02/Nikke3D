#pragma once
#include "../common.h"
#include "DxLib.h"
#include <math.h>

//ベクトルの長さ
static float Get3DVectorLength(VECTOR v) {
	return sqrtf(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

//ベクトルの内積
static float Get3DProduct(VECTOR v, VECTOR v1) {
	return v.x * v1.x + v.y * v1.y + v.z * v1.z;
}

//2つのベクトルの角度
static float Get3DAngle2Vector(VECTOR v, VECTOR v1) {

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

//ベクトルの長さ
static float Get2DVectorLength(float x,float y) {
	return sqrtf(pow(x, 2) + pow(y, 2));
}

//ベクトルの内積
static float Get2DProduct(float x, float y, float x1, float y1) {
	return x * x1 + y * y1;
}

//2つのベクトルの角度
static float Get2DAngle2Vector(float x, float y, float x1, float y1) {

	//長さ
	float length_a = Get2DVectorLength(x, y);
	float length_b = Get2DVectorLength(x1, y1);
	if (length_a == 0 || length_b == 0) {
		return -1; //どちらかの長さが0だった場合失敗
	}

	//内積と長さからコサインを求める
	float cos = Get2DProduct(x, y, x1, y1) / (length_a * length_b);

	//コサインからラジアンへ
	float angle = acosf(cos);

	//ラジアンからデグリー
	angle = r_d(angle);

	//デグリーで返す
	return angle;
}

//回転2d
static VECTOR Get2DRotation(float x, float y, float r) {
	VECTOR v;

	v.x = x * cos(r) - y * sin(r);
	v.y = x * sin(r) + y * cos(r);
	
	return v;
}

