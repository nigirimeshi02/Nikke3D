#pragma once
#include "../SceneBase.h"
#include"../../Actor/Player/Player.h"
#include"../../Actor/Camera/Camera.h"
#include"../../Actor/Enemy/Enemy.h"


// ラインを描く範囲
#define LINE_AREA_SIZE 10000.0f

// ラインの数
#define LINE_NUM 50


class GameMainScene :
    public SceneBase
{
private:
    Player* player;
    Camera* camera;
    Enemy* enemy;

public:
    //コンストラクタ
    GameMainScene();

    //デストラクタ
    ~GameMainScene();

    //描画に関すること以外の更新を実装する
    SceneBase* Update()override;

    //描画に関することの更新を実装する
    void Draw()const override;

    //地面の描画
    void Ground()const;


    Player* GetPlayer() { return player; }
};

