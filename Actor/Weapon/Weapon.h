#pragma once
#include "../../common.h"

class Weapon
{
private:
	int modelHandle;
	int CharModelHandle;
	int weaponAttachFrameNum;
	VECTOR weaponLocation[2];
	VECTOR weaponLocationTmp;
	//VECTOR weaponLocationTmp1;
	VECTOR weaponVector;
	//VECTOR weaponVectorTmp;
	VECTOR weaponRotation;

	VECTOR tmpBase;	//�x�[�X�̒����A
	VECTOR tmpBase2;	//�x�[�X�̒�����ۑ��A�ŏ��̒������Ȃ��Ƃ���

	VECTOR aaa;

	float o = 0;
	float o1 = 0;
	float o2 = 0;

	
public:
	Weapon();
	~Weapon();

	void Update(std::string frameName1, std::string frameName2);
	void Draw()const;

	//���f���n���h��
	void Initialize(int handle, int cHandle, VECTOR base);


	void SetWeaponLocation(std::string frameName1, std::string frameName2);
	void SetWeaponRotation();

	class DesertEagle
	{
	private:
		VECTOR location;		//���W
		VECTOR rotation;		//��]�l

	public:
		//�R���X�g���N�^
		DesertEagle() : location(VGet(0.f, 0.f, 0.f)), rotation(VGet(0.f, 0.f, 0.f)) {};

		//�f�X�g���N�^
		~DesertEagle() {};

		//�X�V
		void Update(class GameMainScene* object, const char* path);

		//�`��
		void Draw()const;

		//���W���擾����
		const VECTOR GetLocation() { return location; }

		//��]�l���擾����
		const VECTOR GetRotation() { return rotation; }

		//���W��ݒ肷��
		void SetLocation(const VECTOR location)
		{
			this->location = location;
		}

		void SetLocationX(const float x) { location.x = x; }			//���Wx��ݒ肷��
		void SetLocationY(const float y) { location.y = y; }			//���Wy��ݒ肷��
		void SetLocationZ(const float z) { location.z = z; }			//���Wz��ݒ肷��

		//��]�l��ݒ肷��
		void SetRotation(const VECTOR rotation)
		{
			this->rotation = rotation;
		}

		void SetRotationX(const float x) { rotation.x = x; }			//��]�lx��ݒ肷��
		void SetRotationY(const float y) { rotation.y = y; }			//��]�ly��ݒ肷��
		void SetRotationZ(const float z) { rotation.z = z; }			//��]�lz��ݒ肷��
	};
};
