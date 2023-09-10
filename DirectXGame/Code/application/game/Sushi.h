#pragma once
#include "DirectXCommon.h"
#include "Mouse.h"
#include "Keyboard.h"
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
	Keyboard* keyboard = Keyboard::GetInstance();
	Mouse* mouse = Mouse::GetInstance();

	// �摜
	Image2d* sushi_geta = nullptr;
	Image2d* wasabi = nullptr;

	//���i�ꗗ
	std::vector<Image2d*> sushi_list;
	Image2d* maguro = nullptr;
	Image2d* samon = nullptr;
	Image2d* ebi = nullptr;
	Image2d* tamago = nullptr;
	Image2d* ika = nullptr;
	bool isCombine = false;
	// �l�^�ꗗ
	Image2d* maguro_neta = nullptr;
	Image2d* samon_neta = nullptr;
	Image2d* ebi_neta = nullptr;
	Image2d* tamago_neta = nullptr;
	Image2d* ika_neta = nullptr;

	// �V����
	std::vector<Image2d*> shari_list;
	Image2d* shari = nullptr;

	// �h���b�O���Ă���摜�f�[�^�擾�p
	Image2d* dragData = nullptr;
	XMFLOAT2 drag_maxPos;
	XMFLOAT2 drag_minPos;


	bool isDrag = false; // �w��̎��i���h���b�O���Ă��邩
	bool isDragNow = false; // �����̎��i���h���b�O���Ă��邩
	int dragNum = 0; // �h���b�O���Ă�����i�̔ԍ�

	int imgNumber = 0; // �摜�Ǘ��̔ԍ�
	int shariNumber = 0; // �V�����̔ԍ�
	int netaNumber = 0; // �l�^�̔ԍ�
};

