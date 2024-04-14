#pragma once
#include "../SceneBase.h"
#include"DxLib.h"

//バーの幅
#define BARWIDTH    1170

//バーの高さ
#define BARHEIGHT   10

struct Box
{
    int x, y;
};

class LoadScene :
    public SceneBase
{
private:
    float maxNum;             //読み込みファイルの最大数
    float num;                //読み込みファイルの数
    
    Box bar;

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

