#pragma once
#include "../Scene/SceneBase.h"

class SceenManager :
    public SceneBase
{
private:
    //���݂̃V�[��
    SceneBase* now_sceen;
public:
    //�R���X�g���N�^
    SceenManager(SceneBase* scene) :now_sceen(scene) {};

    //�f�X�g���N�^
    ~SceenManager() { delete now_sceen; }

    //�`��Ɋւ��邱�ƈȊO�̍X�V����������
    SceneBase* Update()override;

    //�`��Ɋւ��邱�Ƃ�
    void Draw()const override;
};

