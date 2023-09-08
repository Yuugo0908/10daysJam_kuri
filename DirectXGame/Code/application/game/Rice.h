#pragma once
#include "DirectXCommon.h"
#include "Mouse.h"
#include "DebugText.h"
#include "SafeDelete.h"

#include <stdlib.h>
#include <time.h>
#include <list>

class Rice
{
private:
	Rice();

	~Rice();
public:
	// �R�s�[�R���X�g���N�^�𖳌���
	Rice(const Rice& obj) = delete;
	// ������Z�q�𖳌���
	Rice& operator=(const Rice& obj) = delete;
public: // �ÓI�����o�ϐ�
	static Rice* GetInstance();
public: // �����o�֐�
	// ���t���[������
	void Update();
	// �`��
	void Draw();

private: // �����o�ϐ�

};

