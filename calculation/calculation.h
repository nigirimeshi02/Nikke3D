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


//マトリクスお試し
//マトリクス構造体
static struct Matrix4x4
{
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;
};

static struct Vector4
{
	float x, y, z, w;
};


//単位マトリクス獲得
static Matrix4x4 Matrix4x4_Identity()
{
	Matrix4x4 m;

	m.m00 = 1.0f; m.m01 = 0.0f; m.m02 = 0.0f; m.m03 = 0.0f;
	m.m10 = 0.0f; m.m11 = 1.0f; m.m12 = 0.0f; m.m13 = 0.0f;
	m.m20 = 0.0f; m.m21 = 0.0f; m.m22 = 1.0f; m.m23 = 0.0f;
	m.m30 = 0.0f; m.m31 = 0.0f; m.m32 = 0.0f; m.m33 = 1.0f;

	return m;
}

//拡大縮小マトリクス獲得
static Matrix4x4 Matrix4x4_Scale(float sx, float sy, float sz)
{
	Matrix4x4 m;

	m.m00 = sx;   m.m01 = 0.0f; m.m02 = 0.0f; m.m03 = 0.0f;
	m.m10 = 0.0f; m.m11 = sy;   m.m12 = 0.0f; m.m13 = 0.0f;
	m.m20 = 0.0f; m.m21 = 0.0f; m.m22 = sz;   m.m23 = 0.0f;
	m.m30 = 0.0f; m.m31 = 0.0f; m.m32 = 0.0f; m.m33 = 1.0f;

	return m;
}

//回転（X軸）マトリクス獲得
static Matrix4x4 Matrix4x4_RotateX(float rx)
{
	Matrix4x4 m;

	m.m00 = 1.0f; m.m01 = 0.0f;     m.m02 =  0.0f;      m.m03 = 0.0f;
	m.m10 = 0.0f; m.m11 = cosf(rx); m.m12 = -sinf(rx);  m.m13 = 0.0f;
	m.m20 = 0.0f; m.m21 = sinf(rx); m.m22 =  cosf(rx);  m.m23 = 0.0f;
	m.m30 = 0.0f; m.m31 = 0.0f;     m.m32 =  0.0f;      m.m33 = 1.0f;

	return m;
}

//回転（Y軸）マトリクス獲得
static Matrix4x4 Matrix4x4_RotateY(float ry)
{
	Matrix4x4 m;

	m.m00 =  cosf(ry); m.m01 = 0.0f; m.m02 = sinf(ry); m.m03 = 0.0f;
	m.m10 =  0.0f;     m.m11 = 1.0f; m.m12 = 0.0f;     m.m13 = 0.0f;
	m.m20 = -sinf(ry); m.m21 = 0.0f; m.m22 = cosf(ry); m.m23 = 0.0f;
	m.m30 =  0.0f;     m.m31 = 0.0f; m.m32 = 0.0f;     m.m33 = 1.0f;

	return m;
}

//回転（Z軸）マトリクス獲得
static Matrix4x4 Matrix4x4_RotateZ(float rz)
{
	Matrix4x4 m;

	m.m00 = cosf(rz); m.m01 = -sinf(rz); m.m02 = 0.0f; m.m03 = 0.0f;
	m.m10 = sinf(rz); m.m11 =  cosf(rz); m.m12 = 0.0f; m.m13 = 0.0f;
	m.m20 = 0.0f;     m.m21 =  0.0f;     m.m22 = 1.0f; m.m23 = 0.0f;
	m.m30 = 0.0f;     m.m31 =  0.0f;     m.m32 = 0.0f; m.m33 = 1.0f;

	return m;
}

//平行移動マトリクス獲得
static Matrix4x4 Matrix4x4_Translate(float tx, float ty, float tz)
{
	Matrix4x4 m;

	m.m00 = 1.0f; m.m01 = 0.0f; m.m02 = 0.0f; m.m03 = tx;
	m.m10 = 0.0f; m.m11 = 1.0f; m.m12 = 0.0f; m.m13 = ty;
	m.m20 = 0.0f; m.m21 = 0.0f; m.m22 = 1.0f; m.m23 = tz;
	m.m30 = 0.0f; m.m31 = 0.0f; m.m32 = 0.0f; m.m33 = 1.0f;

	return m;
}

//マトリクス*ベクトル
static Vector4 Matrix4x4_Mul_Vector4(Matrix4x4 m, Vector4 v)
{
	Vector4 r;

	r.x = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03 * v.w;
	r.y = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13 * v.w;
	r.z = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23 * v.w;
	r.w = m.m30 * v.x + m.m31 * v.y + m.m32 * v.z + m.m33 * v.w;

	return r;
}