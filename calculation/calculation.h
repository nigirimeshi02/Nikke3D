#pragma once
#include "../common.h"
#include "DxLib.h"
#include <math.h>

//�x�N�g���̒���
float Get3DVectorLength(VECTOR v) {
	return sqrtf(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

//�x�N�g���̓���
float Get3DProduct(VECTOR v, VECTOR v1) {
	return v.x * v1.x + v.y * v1.y + v.z * v1.z;
}

//2�̃x�N�g���̊p�x
float GetAngle2Vector(VECTOR v, VECTOR v1) {

	//����
	float length_a = Get3DVectorLength(v);
	float length_b = Get3DVectorLength(v1);
	if (length_a == 0 || length_b == 0) {
		return -1; //�ǂ��炩�̒�����0�������ꍇ���s
	}

	//���ςƒ�������R�T�C�������߂�
	float cos = Get3DProduct(v, v1) / (length_a * length_b);

	//�R�T�C�����烉�W�A����
	float angle = acosf(cos);

	//���W�A������f�O���[
	angle = r_d(angle);

	//�f�O���[�ŕԂ�
	return angle;
}


