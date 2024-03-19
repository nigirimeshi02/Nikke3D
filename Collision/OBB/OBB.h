#pragma once
#include "../CollisionBase.h"

class OBB :public CollisionBase
{
private:
    VECTOR centerPoint;             //中心点
    VECTOR directionVec[3];         //各軸の方向ベクトル
    VECTOR directionLength;         //各軸の方向の長さ

public:
    //コンストラクタ
    OBB();

    //デストラクタ
    ~OBB();

    //中心点を取得する
    VECTOR GetCenterPoint()const { return centerPoint; }

    //各軸の方向ベクトルを取得する
    VECTOR GetDirectionVec(int element)const { return directionVec[element]; }

    //各軸の方向の長さを取得する
    VECTOR GetDirectionLength()const { return directionLength; }

protected:
    //OBBの更新
    void UpdateOBB(const char* model);

private:
    //OBBとの当たり判定
    bool HitOBB(const OBB* obb)const override;
};

