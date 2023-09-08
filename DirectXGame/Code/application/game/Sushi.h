#pragma once
#include "DirectXCommon.h"
#include "Mouse.h"
#include "DebugText.h"
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
	Mouse* mouse = Mouse::GetInstance();

	// �摜
	Image2d* shari = nullptr;
	Image2d* sushi_geta = nullptr;

	//���i�ꗗ
	std::vector<Image2d*> sushiList;
	Image2d* maguro = nullptr;
	Image2d* samon = nullptr;
	Image2d* ebi = nullptr;
	Image2d* tamago = nullptr;
	Image2d* ika = nullptr;
	Image2d* maguro_neta = nullptr;
	Image2d* samon_neta = nullptr;
	Image2d* ebi_neta = nullptr;
	Image2d* tamago_neta = nullptr;
	Image2d* ika_neta = nullptr;

	bool isDrag = false; // �w��̎��i���h���b�O���Ă��邩
	bool isDragNow = false; // �����̎��i���h���b�O���Ă��邩
	int dragNum = 0; // �h���b�O���Ă�����i�̔ԍ�
	int imgNumber{}; // �摜�̓o�^�ԍ�
};

