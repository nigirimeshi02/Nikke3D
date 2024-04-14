#pragma once
#include"DxLib.h"

enum CollisionType
{
	Empty = 0,		//空
	Obb				//有向境界ボックス
};

class OBB;

class CollisionBase
{
protected:
	VECTOR location;			//座標
	VECTOR rotation;			//回転値
	VECTOR vec;					//移動量
	VECTOR scale;				//大きさ

	CollisionType type;			//コリジョンの種類
public:
	//コンストラクタ
	CollisionBase();

	//デストラクタ
	~CollisionBase();

	//当たり判定
	bool HitCheck(const CollisionBase* collision)const;

	//座標を取得する
	VECTOR GetLocation()const { return location; }

	//回転値を取得する
	VECTOR GetRotation()const { return rotation; }

	//ベクトルを取得する
	VECTOR GetVec()const { return vec; }

	//コリジョンの種類を取得する
	CollisionType GetType()const { return type; }
	
protected:
	//OBBとの当たり判定
	virtual bool HitOBB(const OBB* obb)const = 0;

};

