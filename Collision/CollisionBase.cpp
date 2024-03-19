#include "CollisionBase.h"
#include"OBB/OBB.h"

CollisionBase::CollisionBase()
{
	location = VGet(0.0f, 0.0f, 0.0f);
	rotation = VGet(0.0f, 0.0f, 0.0f);
	vec = VGet(0.0f, 0.0f, 0.0f);

	type = Empty;
}

CollisionBase::~CollisionBase()
{

}

bool CollisionBase::HitCheck(const CollisionBase* collision) const
{
	bool ret = false;
	//�R���W�����̎�ނ̎擾
	CollisionType collisionType = collision->GetType();

	switch (collisionType)
	{
	//��
	case Empty:
		ret = false;
		break;

	//�L�����E�{�b�N�X
	case Obb:
		ret = HitOBB(static_cast<const OBB*>(collision));
		break;

	//�f�t�H���g
	default:
		ret = false;
		break;
	}

	return ret;
}
