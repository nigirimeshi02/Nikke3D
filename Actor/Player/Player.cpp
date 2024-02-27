#include"../../common.h"
#include "Player.h"
#include"../Camera/Camera.h"
#include"../../ResourceManager/Model/ModelManager.h"

Player::Player()
{
	animIndex = 0;

	animState = playerAnim::Dance;

	animPlayTime = 0.f;
	animTotalTime = 0.f;

	angle = CAMERA_ANGLE_0 * 2;
	radian = angle * DX_PI_F / 180.f;

	isIdle = false;
	isWalk = false;
	isDash = false;
	isJump = false;
	isGunHold = false;
	isAir = false;

	location = VGet(0.0f, 0.0f, 0.0f);
	weaponLocation = VGet(0.0f, 0.0f, 0.0f);
	rotation = VGet(0.0f, 0.0f, 0.0f);
	weaponRotation = VGet(0.0f, 0.0f, 0.0f);
	vec = VGet(0.0f, 0.0f, 0.0f);

	//�R�c���f���̃X�P�[����3�{�ɂ���
	MV1SetScale(ModelManager::GetModelHandle(RAPI), VGet(3.0f, 3.0f, 3.0f));
	MV1SetScale(ModelManager::GetModelHandle(DESERT_EAGLE), VGet(3.0f, 3.0f, 3.0f));

}

Player::~Player()
{

}

void Player::Update(Camera* camera)
{
	//���W���Z�b�g����
	MV1SetPosition(ModelManager::GetModelHandle(RAPI), location);

	//��]�l���Z�b�g����
	MV1SetRotationXYZ(ModelManager::GetModelHandle(RAPI), rotation);

	//�A�j���[�V����
	Animation();

	//�Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(ModelManager::GetModelHandle(RAPI), animIndex, animPlayTime);

	//�ړ�
	Movement(camera);

	//�s��
	Action();

	//����
	WeaponUpdate(camera);
}

void Player::Draw() const
{
	MV1DrawModel(ModelManager::GetModelHandle(RAPI));
	MV1DrawModel(ModelManager::GetModelHandle(DESERT_EAGLE));

	DrawFormatString(0, 0, 0xffffff, "x:%f", location.x);
	DrawFormatString(0, 10, 0xffffff, "y:%f", location.y);
	DrawFormatString(0, 20, 0xffffff, "z:%f", location.z);
}

void Player::Movement(Camera* camera)
{
	//�J�������猩�ĉ��ɐi��
	if (KeyInput::GetKeyDown(KEY_INPUT_W))
	{
		if (KeyInput::GetKeyDown(KEY_INPUT_LSHIFT))
		{			
			isDash = true;
			isWalk = false;
			isIdle = false;	

			if (vec.z > -MAX_MOVE_SPEED)
			{
				vec.z -= MOVE_SPEED;
			}
		}
		else
		{
			isWalk = true;
			isIdle = false;
			isDash = false;

			vec.z = -MOVE_SPEED;
		}

		angle = CAMERA_ANGLE_0 - camera->GetHAngle();
	}
	//�J�������猩�Ď�O�ɐi��
	else if (KeyInput::GetKeyDown(KEY_INPUT_S))
	{
		if (KeyInput::GetKeyDown(KEY_INPUT_LSHIFT))
		{
			isDash = true;
			isWalk = false;
			isIdle = false;

			if (vec.z < MAX_MOVE_SPEED)
			{
				vec.z += MOVE_SPEED;
			}
		}
		else
		{
			isWalk = true;
			isIdle = false;
			isDash = false;

			vec.z = MOVE_SPEED;
		}

		angle = CAMERA_ANGLE_180 - camera->GetHAngle();
	}
	else
	{
		isIdle = true;
		isWalk = false;
		isDash = false;
		vec.z = 0.f;
	}

	//�J�������猩�č��ɐi��
	if (KeyInput::GetKeyDown(KEY_INPUT_A))
	{
		if (KeyInput::GetKeyDown(KEY_INPUT_LSHIFT))
		{
			isDash = true;
			isWalk = false;
			isIdle = false;

			if (vec.x < MAX_MOVE_SPEED)
			{
				vec.x += MOVE_SPEED;
			}
		}
		else
		{
			isWalk = true;
			isIdle = false;
			isDash = false;

			vec.x = MOVE_SPEED;
		}

		angle = CAMERA_ANGLE_270 - camera->GetHAngle();

		//if (angle <= CAMERA_ANGLE_0 - camera->GetHAngle())
		//{
		//	angle = CAMERA_ANGLE_270 - camera->GetHAngle();
		//}

		//if (angle < CAMERA_ANGLE_270 - camera->GetHAngle())
		//{
		//	angle += ROTATE_SPEED;
		//}
		//if (angle > CAMERA_ANGLE_270 - camera->GetHAngle())
		//{
		//	angle -= ROTATE_SPEED;
		//}

		if (KeyInput::GetKeyDown(KEY_INPUT_W))
		{
			angle = CAMERA_ANGLE_270 + ROTATE_SPEED - camera->GetHAngle();
		}
		if (KeyInput::GetKeyDown(KEY_INPUT_S))
		{
			angle = CAMERA_ANGLE_270 - ROTATE_SPEED - camera->GetHAngle();
		}
	}
	//�J�������猩�ĉE�ɐi��
	else if (KeyInput::GetKeyDown(KEY_INPUT_D))
	{
		if (KeyInput::GetKeyDown(KEY_INPUT_LSHIFT))
		{
			isDash = true;
			isWalk = false;
			isIdle = false;

			if (vec.x > -MAX_MOVE_SPEED)
			{
				vec.x -= MOVE_SPEED;
			}
		}
		else
		{
			isWalk = true;
			isIdle = false;
			isDash = false;

			vec.x = -MOVE_SPEED;
		}

		angle = CAMERA_ANGLE_90 - camera->GetHAngle();

		//if (angle < CAMERA_ANGLE_90 - camera->GetHAngle())
		//{
		//	angle += ROTATE_SPEED;
		//}
		//if (angle > CAMERA_ANGLE_90 - camera->GetHAngle())
		//{
		//	angle -= ROTATE_SPEED;
		//}
		if (KeyInput::GetKeyDown(KEY_INPUT_W))
		{
			angle = CAMERA_ANGLE_90 - ROTATE_SPEED - camera->GetHAngle();
		}
		if (KeyInput::GetKeyDown(KEY_INPUT_S))
		{
			angle = CAMERA_ANGLE_90 + ROTATE_SPEED - camera->GetHAngle();
		}
	}
	else
	{
		vec.x = 0.f;
	}

	radian = angle * DX_PI_F / 180.f;
	rotation = VGet(0.f, radian, 0.f);
	weaponRotation.y = radian;

	if (KeyInput::GetKeyDown(KEY_INPUT_SPACE) && !isAir)
	{
		isJump = true;
		isAir = true;

		//�W�����v�͂��ړ��ʂɏ�Z
		vec.x *= JUMP_POWER;
		vec.z *= JUMP_POWER;

		vec.y = JUMP_POWER;
	}

	//�J�����̊p�x�ɍ��킹�Ĉړ��ʂ��Z�o����
	VECTOR moveVec;

	float sinPara = sinf(camera->GetHAngle() / 180.f * DX_PI_F);
	float cosPara = cosf(camera->GetHAngle() / 180.f * DX_PI_F);

	moveVec.x = vec.x * cosPara - vec.z * sinPara;
	moveVec.y = vec.y;
	moveVec.z = vec.x * sinPara + vec.z * cosPara;

	location = VAdd(location, moveVec);

	//�d��
	vec.y -= GRAVITY;

	//0��艺�ɂ͍s���Ȃ�
	if (location.y < 0)
	{
		isJump = false;
		isAir = false;
		vec.y = 0.f;
		location.y = 0.f;

		//�ړ��ʂ����ɖ߂�
		if (vec.x > MAX_MOVE_SPEED)
		{
			vec.x = MAX_MOVE_SPEED;
		}
		else if (vec.x < -MAX_MOVE_SPEED)
		{
			vec.x = -MAX_MOVE_SPEED;
		}
		if (vec.z > MAX_MOVE_SPEED)
		{
			vec.z = MAX_MOVE_SPEED;
		}
		else if (vec.z < -MAX_MOVE_SPEED)
		{
			vec.z = -MAX_MOVE_SPEED;
		}
	}
	//0���傫���Ȃ��
	if (location.y > 0)
	{
		isAir = true;
	}
}

void Player::Action()
{
	if (KeyInput::GetButtonDown(MOUSE_INPUT_RIGHT))
	{
		isGunHold = true;
		//isIdle = false;
		//isDash = false;
		//isWalk = false;
	}
	else
	{
		isGunHold = false;
	}
}

void Player::WeaponUpdate(Camera* camera)
{
	//��̂Ђ�
	int framNum1 = MV1SearchFrame(ModelManager::GetModelHandle(RAPI), "�E���");
	//���w
	int framNum2 = MV1SearchFrame(ModelManager::GetModelHandle(RAPI), "�E���w�P");
	//�n���}�[�s��
	int framNum3 = MV1SearchFrame(ModelManager::GetModelHandle(DESERT_EAGLE), "�n���}�[�s��");
	//�e��
	int framNum4 = MV1SearchFrame(ModelManager::GetModelHandle(DESERT_EAGLE), "�e��");	

	//��̂Ђ�̍��W
	VECTOR framPoint1 = MV1GetFramePosition(ModelManager::GetModelHandle(RAPI), framNum1);
	//���w�̍��W
	VECTOR framPoint2 = MV1GetFramePosition(ModelManager::GetModelHandle(RAPI), framNum2);
	//�n���}�[�s���̍��W
	VECTOR framPoint3 = MV1GetFramePosition(ModelManager::GetModelHandle(DESERT_EAGLE), framNum3);
	//�e���̍��W
	VECTOR framPoint4 = MV1GetFramePosition(ModelManager::GetModelHandle(DESERT_EAGLE), framNum4);

	//��̂Ђ�ƒ��w�̃x�N�g��
	VECTOR framPointVec1 = VSub(framPoint1, framPoint2);
	//�n���}�[�s���Əe���̃x�N�g��
	VECTOR framPointVec2 = VSub(framPoint3, framPoint4);
	//��̂Ђ�Əe���̃x�N�g��
	VECTOR framPointVec3 = VSub(framPoint1, framPoint4);

	//��̂Ђ�ƒ��w�̒P�ʃx�N�g��
	VECTOR Identity1 = VNorm(framPointVec1);
	//�n���}�[�s���Əe���̒P�ʃx�N�g��
	VECTOR Identity2 = VNorm(framPointVec2);
	//��̂Ђ�Əe���̒P�ʃx�N�g��
	VECTOR Identity3 = VNorm(framPointVec3);

	//2�̃x�N�g���̊p�x
	float handGunRadX = asin(VDot(Identity1, Identity2));
	float handGunRadZ = acos(VDot(Identity2, Identity3));

	weaponLocation = framPoint1;

	if (isGunHold)
	{
		float radianY = 16.f * DX_PI_F / 180.f;

		weaponLocation = VGet(weaponLocation.x, weaponLocation.y + 1.f, weaponLocation.z);
		weaponRotation = VGet(0.f, radian - radianY, 0.f);
	}
	else
	{
		weaponLocation = VGet(weaponLocation.x, weaponLocation.y, weaponLocation.z);
		weaponRotation = VGet(-handGunRadX, this->radian, -handGunRadZ);
	}

	//X����Z����Y���̏��Ԃɉ�]������
	MV1SetMatrix(ModelManager::GetModelHandle(DESERT_EAGLE),
		MMult(MMult(MGetScale(VGet(3.f, 3.f, 3.f))
			, MMult(MMult(MGetRotX(weaponRotation.x), MGetRotZ(weaponRotation.z))
				, MGetRotY(weaponRotation.y)))
			, MGetTranslate(weaponLocation)));
}

void Player::Animation()
{
	animPlayTime += .5f;

	//�A�j���[�V�����̃��[�v
	if (animPlayTime >= animTotalTime)
	{
		//�W�����v���Ă��Ȃ����󒆂ɂ��Ȃ��Ȃ珉����
		if (!isJump&&!isAir)
		{
			animPlayTime = 0.f;
		}
		else
		{
			isJump = false;
		}
	}

	//�ҋ@�A�j���[�V�����̓ǂݍ���
	if (isIdle && !isAir && animState != playerAnim::Idle)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Idle, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Idle;
	}

	//�����A�j���[�V�����̓ǂݍ���
	if (isWalk && !isAir && animState != playerAnim::Walk)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Walk, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Walk;
	}

	//����A�j���[�V�����̓ǂݍ���
	if (isDash && !isAir && animState != playerAnim::Dash)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Dash, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Dash;
	}

	//�W�����v�A�j���[�V�����̓ǂݍ���
	if (isJump && !isDash && animState != playerAnim::Jump && animState != playerAnim::DashJump)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Jump, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Jump;
	}

	//�e���\����A�j���[�V�����̓ǂݍ���
	if (isGunHold && animState != playerAnim::GunHold)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::GunHold, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::GunHold;
	}

	//�_�b�V���W�����v�̃A�j���[�V�����̓ǂݍ���
	if (isJump && isDash && animState != playerAnim::DashJump && animState != playerAnim::Jump)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::DashJump, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 3.f;

		animState = playerAnim::DashJump;
	}

	//�����̃A�j���[�V�����̓ǂݍ���
	if (isAir && !isJump && animState != playerAnim::Fall)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(ModelManager::GetModelHandle(RAPI), animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(ModelManager::GetModelHandle(RAPI), playerAnim::Fall, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(ModelManager::GetModelHandle(RAPI), animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Fall;
	}
}