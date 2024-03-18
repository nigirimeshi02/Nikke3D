#pragma once
#include "../SceneBase.h"
#include"../../Actor/Player/Player.h"
#include"../../Actor/Camera/Camera.h"
#include"../../Actor/Enemy/Enemy.h"
#include"../../Actor/Player/SubCharacter/Scarlet.h"

#define LINE_AREA_SIZE 10000.0f         // ラインを描く範囲
#define LINE_NUM 50                     // ラインの数

class GameMainScene :
    public SceneBase
{
private:
    Player* player;         //プレイヤーのオブジェクト
    Camera* camera;         //カメラのオブジェクト
    Enemy* enemy;           //敵のオブジェクト
    Scarlet* scarlet;       //紅蓮のオブジェクト
public:
    //コンストラクタ
    GameMainScene();

    //デストラクタ
    ~GameMainScene();

    //描画に関すること以外の更新を実装する
    SceneBase* Update()override;

    //描画に関することの更新を実装する
    void Draw()const override;

private:
    //地面の描画
    void Ground()const;

    //キャラクターの切り替え
    void SwitchCharacter();

public:
    //プレイヤーオブジェクトの取得
    Player* GetPlayer()const { return player; }

    //カメラオブジェクトの取得
    Camera* GetCamera()const { return camera; }

    //敵のオブジェクトの取得
    Enemy* GetEnemy()const { return enemy; }

    //紅蓮のオブジェクトの取得
    Scarlet* GetScarlet()const { return scarlet; }
};

