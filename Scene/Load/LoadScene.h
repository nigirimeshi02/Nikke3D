#pragma once
#include "../SceneBase.h"

class LoadScene :
    public SceneBase
{
private:

public:
    //コンストラクタ
    LoadScene();

    //デストラクタ
    ~LoadScene();

    //描画に関すること以外の更新を実装する
    SceneBase* Update()override;

    //描画に関することの更新を実装する
    void Draw()const override;
};

