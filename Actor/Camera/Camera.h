#include"../../common.h"

class GameMainScene;

#define CAMERA_LOOK_AT_HEIGHT 30.0f	// �J�����̒����_�̍���

class Camera
{
private:
	VECTOR location;				//�J�����̈ʒu
	VECTOR position1;				//�����p�x�Z�o�p
	VECTOR position2;				//�����p�x�Z�o�p
	VECTOR lookAtPosition;			//�J�����̒����_

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
	void Update(GameMainScene* object);

	//�`��
	void Draw()const;

	//�����p�x���擾����
	float GetHAngle() { return hAngle; }
};