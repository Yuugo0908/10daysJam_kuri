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
	Mouse* mouse = Mouse::GetInstance();

	// �摜
	Image2d* rice = nullptr;
	Image2d* watar = nullptr;

	Image2d* kama = nullptr;
	Image2d* kama_watar = nullptr;
	Image2d* kama_rice_watar = nullptr;
	Image2d* kama_rice = nullptr;

	Image2d* suihan_open = nullptr;
	Image2d* suihan_close = nullptr;
};

