#include"../../common.h"
#include "Enemy.h"
#include "../../calculation/calculation.h"
#include "../../Scene/GameMain/GameMainScene.h"


Enemy::Enemy()
{
	//�R�c���f���̓ǂݍ���
	modelHandle = MV1LoadModel("Anis.fbm/Anis-Apose.pmx");

	angle = 0.f;
	radian = angle * DX_PI_F / 180.f;

	isIdle = false;
	isWalk = false;
	isDash = false;

	location = VGet(0.0f, 0.0f, 50.0f);
	rotation = VGet(0.0f, 0.0f, 0.0f);
	vec = VGet(0.0f, 0.0f, 0.0f);
	directionVec = VGet(0.0f, 0.0f, 0.0f);

	speed = 0.5;

	//�R�c���f���̃X�P�[����2.5�{�ɂ���
	MV1SetScale(modelHandle, VGet(3.0f, 3.0f, 3.0f));

	//����
	weaponModelHandle = MV1LoadModel("Anis.fbm/Sword.mv1");
	weaponAttachFrameNum = MV1SearchFrame(modelHandle, "�E�l�w�P");
	matrix = MV1GetFrameLocalWorldMatrix(modelHandle, weaponAttachFrameNum);
	MV1SetScale(weaponModelHandle, VGet(0.05f, 0.05f, 0.05f));
}

Enemy::~Enemy()
{
	MV1DeleteModel(modelHandle);
}

void Enemy::Update(GameMainScene* gm)
{
	//�x�N�g���̐ݒ�
	SetVector(gm->GetPlayer());

	//�p�x��ݒ�
	SetRotation(gm->GetPlayer());



	//���W���Z�b�g����
	MV1SetPosition(modelHandle, location);

	//��]�l���Z�b�g����
	MV1SetRotationXYZ(modelHandle, rotation);

	//�A�j���[�V����
	Animation();

	//�Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(modelHandle, animIndex, animPlayTime);

	Movement();


	weaponLocation = MV1GetFramePosition(modelHandle, weaponAttachFrameNum);
	MV1SetPosition(weaponModelHandle, weaponLocation);
}

void Enemy::Draw() const
{
	MV1DrawModel(modelHandle);
	MV1DrawModel(weaponModelHandle);

	DrawFormatString(0, 0 + 48, 0xffffff, "x:%f", location.x);
	DrawFormatString(0, 16 + 48, 0xffffff, "y:%f", location.y);
	DrawFormatString(0, 32 + 48, 0xffffff, "z:%f", location.z);

	DrawFormatString(200, 0 + 48, 0xffffff, "x:%f", vec.x);
	DrawFormatString(200, 16 + 48, 0xffffff, "y:%f", vec.y);
	DrawFormatString(200, 32 + 48, 0xffffff, "z:%f", vec.z);
	DrawFormatString(200, 48 + 48, 0xffffff, "angle:%f", angle);
	DrawFormatString(200, 64 + 48, 0xffffff, "rot.y:%f", rotation.y);
}

void Enemy::Movement()
{
	location.x += vec.x;
	//location.y += vec.y;
	location.z += vec.z;
}

void Enemy::Animation()
{
	//�ҋ@
	if (Get3DVectorLength(vec) == 0) {
		isIdle = true;
		isWalk = false;
		isDash = false;
	}
	//����
	else if (Get3DVectorLength(vec) > 0) {
		isIdle = false;
		isWalk = true;
		isDash = false;
	}

	animPlayTime += .5f;

	if (animPlayTime >= animTotalTime)
	{
		animPlayTime = MOVE_SPEED;
	}

	//�ҋ@�A�j���[�V�����̓ǂݍ���
	if (isIdle && animState != playerAnim::Idle)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(modelHandle, animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(modelHandle, playerAnim::Idle, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Idle;
	}

	//�����A�j���[�V�����̓ǂݍ���
	if (isWalk && animState != playerAnim::Walk)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(modelHandle, animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(modelHandle, playerAnim::Walk, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Walk;
	}

	//����A�j���[�V�����̓ǂݍ���
	if (isDash && animState != playerAnim::Dash)
	{
		//�A�j���[�V�����̃f�^�b�`
		MV1DetachAnim(modelHandle, animIndex);

		//�A�j���[�V�����̃A�^�b�`
		animIndex = MV1AttachAnim(modelHandle, playerAnim::Dash, -1, FALSE);

		//�A�^�b�`�������[�V�����̑��Đ����Ԃ��擾����
		animTotalTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);

		//�Đ����Ԃ̏�����
		animPlayTime = 0.f;

		animState = playerAnim::Dash;
	}
}

void Enemy::SetRotation(Player* p)
{
	//��x�N�g���̐ݒ�
	VECTOR baseVec;
	baseVec = { 0,0,-10 };

	//�x�N�g���̒���
	float dis;
	dis = Get3DVectorLength(directionVec);

	//�p�x�̎擾
	angle = GetAngle2Vector(directionVec, baseVec);

	//cos�ł�0~180�܂ł������Ȃ��̂�180~359�܂ł̐��K��
	if (directionVec.x > 0) {
		float tmp = 180 + (180 - angle);
		rotation.y = d_r(tmp);
	}
	else {
		rotation.y = d_r(angle);
	}
}

void Enemy::SetVector(Player* p)
{
	//�v���C���[�̈ʒu�ƃG�l�~�[�̈ʒu����x�N�g�����o��
	VECTOR tmp;
	tmp = { p->GetLocation().x - location.x, p->GetLocation().y - location.y, p->GetLocation().z - location.z };

	//�v���C���[�ƃG�l�~�[�̋���
	float dis;
	dis = sqrtf(pow(tmp.x, 2) + pow(tmp.y, 2) + pow(tmp.z, 2));

	//�P�ʃx�N�g��
	VECTOR tmp1;
	//������0�������ꍇ�P�ʃx�N�g�������ׂ�0�ɂ���
	if (dis != 0) {
		tmp1 = { tmp.x / dis,tmp.y / dis, tmp.z / dis };
	}
	else {
		tmp1 = { 0,0,0 };
	}

	//�v���C���[�Ƌ������߂Â�����X�g�b�v
	if (dis < 30.) {
		vec = { 0,0,0 };
	}
	//�v���C���[�Ƌ���������������x�N�g������
	else{
		//�x�N�g���ɑ��
		vec = { tmp1.x * speed,tmp1.y * speed ,tmp1.z * speed };
	}
	
	//�L�����N�^�[�̕����ێ�
	directionVec = { tmp1.x * speed,tmp1.y * speed ,tmp1.z * speed };
}

