#pragma once

#include "DirectXCommon.h"
#include "Mouse.h"
#include "Image2d.h"
#include "DebugText.h"
#include "Operator.h"
#include "Particle.h"
#include "SafeDelete.h"

#include <stdlib.h>
#include <time.h>
#include <list>
class Sushi
{
private:
	Sushi();

	~Sushi();
public:
	// �R�s�[�R���X�g���N�^�𖳌���
	Sushi(const Sushi& obj) = delete;
	// ������Z�q�𖳌���
	Sushi& operator=(const Sushi& obj) = delete;

public: // �ÓI�����o�ϐ�
	static Sushi* GetInstance();

public: // �����o�֐�
	// ���t���[������
	void Update();
	// �`��
	void Draw();

private: // �����o�ϐ�
	Controller* controller = Controller::GetInstance();
	Mouse* mouse = Mouse::GetInstance();
	Camera* camera = Camera::GetInstance();

	// �摜
	Image2d* shari = nullptr;
	Image2d* sushi_geta = nullptr;

	std::list<Image2d*> sushiList;
	Image2d* maguro = nullptr;
	Image2d* maguro_neta = nullptr;

	bool isDrag = false;
};

