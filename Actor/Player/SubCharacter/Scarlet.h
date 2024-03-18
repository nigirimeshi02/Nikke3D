#pragma once
#include "../../CharaBase.h"

namespace scarletAnim
{
    enum Animation
    {
        Idle = 0,			//�ҋ@
        Walk,				//����
        Dash,				//����
        Jump,				//�W�����v
        DashJump,			//�_�b�V���W�����v
        Fall				//����
    };
}

class Scarlet :
    public CharaBase
{
private:

public:
    //�R���X�g���N�^
    Scarlet();

    //�f�X�g���N�g
    ~Scarlet();

    //�X�V
    void Update(GameMainScene* object)override;

    //�`��
    void Draw()const override;

    //�A�N�V����
    void Action();

    //�A�j���[�V����
    void Animation();
};
