#pragma once
#include "../SceneBase.h"
#include"../../Actor/Player/Player.h"
#include"../../Actor/Camera/Camera.h"
#include"../../Actor/Enemy/Enemy.h"
#include"../../Actor/Player/SubCharacter/Scarlet.h"

#define LINE_AREA_SIZE 10000.0f         // ���C����`���͈�
#define LINE_NUM 50                     // ���C���̐�

class GameMainScene :
    public SceneBase
{
private:
    Player* player;         //�v���C���[�̃I�u�W�F�N�g
    Camera* camera;         //�J�����̃I�u�W�F�N�g
    Enemy* enemy;           //�G�̃I�u�W�F�N�g
    Scarlet* scarlet;       //�g�@�̃I�u�W�F�N�g
public:
    //�R���X�g���N�^
    GameMainScene();

    //�f�X�g���N�^
    ~GameMainScene();

    //�`��Ɋւ��邱�ƈȊO�̍X�V����������
    SceneBase* Update()override;

    //�`��Ɋւ��邱�Ƃ̍X�V����������
    void Draw()const override;

private:
    //�n�ʂ̕`��
    void Ground()const;

    //�L�����N�^�[�̐؂�ւ�
    void SwitchCharacter();

public:
    //�v���C���[�I�u�W�F�N�g�̎擾
    Player* GetPlayer()const { return player; }

    //�J�����I�u�W�F�N�g�̎擾
    Camera* GetCamera()const { return camera; }

    //�G�̃I�u�W�F�N�g�̎擾
    Enemy* GetEnemy()const { return enemy; }

    //�g�@�̃I�u�W�F�N�g�̎擾
    Scarlet* GetScarlet()const { return scarlet; }
};

