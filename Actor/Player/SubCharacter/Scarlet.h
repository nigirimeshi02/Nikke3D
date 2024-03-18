#pragma once
#include "../../CharaBase.h"

namespace scarletAnim
{
    enum Animation
    {
        Idle = 0,			//待機
        Walk,				//歩き
        Dash,				//走り
        Jump,				//ジャンプ
        DashJump,			//ダッシュジャンプ
        Fall				//落下
    };
}

class Scarlet :
    public CharaBase
{
private:

public:
    //コンストラクタ
    Scarlet();

    //デストラクト
    ~Scarlet();

    //更新
    void Update(GameMainScene* object)override;

    //描画
    void Draw()const override;

    //アクション
    void Action();

    //アニメーション
    void Animation();
};

