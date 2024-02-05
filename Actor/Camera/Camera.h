#include"../../common.h"

class Player;

// �J�����̒����_�̍���
#define CAMERA_LOOK_AT_HEIGHT 30.0f

class Camera
{
private:
	VECTOR location;				//�J�����̈ʒu
	VECTOR position1;				//�����p�x�Z�o�p
	VECTOR position2;				//�����p�x�Z�o�p
	VECTOR lookAtPosition;			//�J�����̒����_
	VECTOR dVec;					//�����x�N�g��
	VECTOR identity;				//���K����̃x�N�g��

	float magnitude;				//�x�N�g���̑傫��

	float lookAtDistance;			//�J�����ƒ����_�̋���

	float vAngle;					//�����p�x
	float hAngle;					//�����p�x

	float sinPara;					//sin�̒l
	float cosPara;					//cos�̒l

public:
	//�R���X�g���N�^
	Camera();

	//�f�X�g���N�^
	~Camera();

	//�X�V
	void Update(Player* player);

	//�`��
	void Draw()const;

	//���W���擾����
	VECTOR GetIdentity() { return identity; }

	//�����p�x���擾����
	float GetHAngle() { return hAngle; }

	VECTOR operator -(const VECTOR& location)
	{
		VECTOR vec;

		vec. x = location.x - this->location.x;
		vec. y = location.y - this->location.y;
		vec. z = location.z - this->location.z;

		return vec;
	}
};