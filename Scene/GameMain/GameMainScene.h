#pragma once
#include "../SceneBase.h"
#include"../../Actor/Player/Player.h"
#include"../../Actor/Camera/Camera.h"

// ���C����`���͈�
#define LINE_AREA_SIZE 10000.0f

// ���C���̐�
#define LINE_NUM 50


class GameMainScene :
    public SceneBase
{
private:
    Player* player;
    Camera* camera;

public:
    //�R���X�g���N�^
    GameMainScene();

    //�f�X�g���N�^
    ~GameMainScene();

    //�`��Ɋւ��邱�ƈȊO�̍X�V����������
    SceneBase* Update()override;

    //�`��Ɋւ��邱�Ƃ̍X�V����������
    void Draw()const override;

    //�n�ʂ̕`��
    void Ground()const;
};

