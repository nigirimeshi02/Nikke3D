#pragma once
#include "../CollisionBase.h"

class OBB :public CollisionBase
{
private:
    VECTOR centerPoint;             //���S�_
    VECTOR directionVec[3];         //�e���̕����x�N�g��
    VECTOR directionLength;         //�e���̕����̒���

public:
    //�R���X�g���N�^
    OBB();

    //�f�X�g���N�^
    ~OBB();

    //���S�_���擾����
    VECTOR GetCenterPoint()const { return centerPoint; }

    //�e���̕����x�N�g�����擾����
    VECTOR GetDirectionVec(int element)const { return directionVec[element]; }

    //�e���̕����̒������擾����
    VECTOR GetDirectionLength()const { return directionLength; }

protected:
    //OBB�̍X�V
    void UpdateOBB(const char* model);

private:
    //OBB�Ƃ̓����蔻��
    bool HitOBB(const OBB* obb)const override;
};

