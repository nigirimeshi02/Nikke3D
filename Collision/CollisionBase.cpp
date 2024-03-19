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
	//コリジョンの種類の取得
	CollisionType collisionType = collision->GetType();

	switch (collisionType)
	{
	//空
	case Empty:
		ret = false;
		break;

	//有向境界ボックス
	case Obb:
		ret = HitOBB(static_cast<const OBB*>(collision));
		break;

	//デフォルト
	default:
		ret = false;
		break;
	}

	return ret;
}
