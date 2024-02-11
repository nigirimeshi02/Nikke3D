#pragma once
#include "../SceneBase.h"
#include"DxLib.h"

//�o�[�̕�
#define BARWIDTH    1170

//�o�[�̍���
#define BARHEIGHT   10

struct Box
{
    int x, y;
};

class LoadScene :
    public SceneBase
{
private:
    float maxNum;             //�ǂݍ��݃t�@�C���̍ő吔
    float num;                //�ǂݍ��݃t�@�C���̐�
    
    Box bar;

public:
    //�R���X�g���N�^
    LoadScene();

    //�f�X�g���N�^
    ~LoadScene();

    //�`��Ɋւ��邱�ƈȊO�̍X�V����������
    SceneBase* Update()override;

    //�`��Ɋւ��邱�Ƃ̍X�V����������
    void Draw()const override;
};

