#pragma once
#include "../SceneBase.h"

class LoadScene :
    public SceneBase
{
private:

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

