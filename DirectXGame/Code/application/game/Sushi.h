#pragma once
#include "DirectXCommon.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "DebugText.h"
#include "SafeDelete.h"
#include "Random.h"
#include "Audio.h"

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

public: // �ÓI�����o�֐�
	static Sushi* GetInstance();

public: // �ÓI�����o�ϐ�
	static int score;

public: // �����o�֐�
	// ������
	void Initialize();
	// ���t���[������
	void Update();
	// �`��
	void Draw();
	// �I��
	void Finalize();
	// �h���b�O�A���h�h���b�v
	void DragDrop();
	// �l�^����
	void MakeNeta();
	// ���i����
	void MakeSushi();
	// ���i���ʂɒu��
	void PutSushi();
	// �p�^�[������
	void Pattern();
	// ���딻��
	void Judge();

private: // �����o�ϐ�
	Keyboard* keyboard = Keyboard::GetInstance();
	Mouse* mouse = Mouse::GetInstance();

	// �摜
	// ���i����
	std::vector<Image2d*> sushi_getas;
	Image2d* sushi_geta_1 = nullptr;
	Image2d* sushi_geta_2 = nullptr;
	Image2d* sushi_geta_3 = nullptr;
	const XMFLOAT2 geta_1_pos = { 750.0f, 570.0f };
	const XMFLOAT2 geta_2_pos = { 165.0f, 570.0f };
	const XMFLOAT2 geta_3_pos = { 1335.0f, 570.0f };
	// ���ʂɏ���Ă�����i�ꗗ
	std::vector<Image2d*> geta_1_sushi_list;
	std::vector<Image2d*> geta_2_sushi_list;
	std::vector<Image2d*> geta_3_sushi_list;
	// ���ʂɏ���Ă�����i�̐�
	int geta_1_pieces = 0;
	int geta_2_pieces = 0;
	int geta_3_pieces = 0;
	// ���ʂɏ悹�Ă�����i�̔ԍ�
	std::vector<int> geta_1_number;
	std::vector<int> geta_2_number;
	std::vector<int> geta_3_number;
	// ���ʂɒu�������̃t���O
	bool isPut_1 = false;
	bool isPut_2 = false;
	bool isPut_3 = false;

	// �ĉ�
	const XMFLOAT2 kome_oke_position = { 150.0f, 850.0f };
	Image2d* kome_oke = nullptr;

	//���i�ꗗ
	std::vector<Image2d*> sushi_list;
	Image2d* maguro = nullptr;
	Image2d* samon = nullptr;
	Image2d* ebi = nullptr;
	Image2d* tamago = nullptr;
	Image2d* ika = nullptr;
	bool isCombine = false;

	// �l�^�ꗗ
	const XMFLOAT2 maguro_neta_position	 = {1250.0f, 900.0f};
	const XMFLOAT2 samon_neta_position	 = {1375.0f, 900.0f};
	const XMFLOAT2 ebi_neta_position	 = {1500.0f, 900.0f};
	const XMFLOAT2 tamago_neta_position	 = {1625.0f, 900.0f};
	const XMFLOAT2 ika_neta_position	 = {1750.0f, 900.0f};
	Image2d* maguro_neta = nullptr;
	Image2d* samon_neta = nullptr;
	Image2d* ebi_neta = nullptr;
	Image2d* tamago_neta = nullptr;
	Image2d* ika_neta = nullptr;

	// �h���b�O�\���p
	Image2d* maguro_neta_dis = nullptr;
	Image2d* samon_neta_dis = nullptr;
	Image2d* ebi_neta_dis = nullptr;
	Image2d* tamago_neta_dis = nullptr;
	Image2d* ika_neta_dis = nullptr;

	// ����p
	std::vector<Image2d*> pattern_1;
	std::vector<Image2d*> pattern_2;
	std::vector<Image2d*> pattern_3;
	// �����t���O
	bool pattern_1_flag = true;
	bool pattern_2_flag = true;
	bool pattern_3_flag = true;
	// �����܂ł̃^�C�}�[
	int pattern_1_timer = 30;
	int pattern_2_timer = Random::GetRanNum(300, 600);
	int pattern_3_timer = Random::GetRanNum(900, 1200);
	// �������ς��܂ł̃^�C�}�[�\��
	Image2d* wait_bar_1 = nullptr;
	Image2d* wait_bar_2 = nullptr;
	Image2d* wait_bar_3 = nullptr;
	Image2d* wait_gauge_1 = nullptr;
	Image2d* wait_gauge_2 = nullptr;
	Image2d* wait_gauge_3 = nullptr;
	// �������ς��܂ł̃^�C�}�[
	int wait_timer_1 = 1200;
	int wait_timer_2 = 1200;
	int wait_timer_3 = 1200;
	// �X�R�A�{�[�i�X
	int combo_bonus = 1;
	int time_bonus = 0;

	// �V����
	std::vector<Image2d*> shari_list;
	Image2d* shari = nullptr;

	// �X�R�A�\���p
	Image2d* score_back = nullptr;

	// �h���b�O���Ă���摜�f�[�^�擾�p
	Image2d* dragData = nullptr;
	XMFLOAT2 drag_maxPos = {};
	XMFLOAT2 drag_minPos = {};

	bool isDrag = false; // �w��̎��i���h���b�O���Ă��邩
	bool isDragNow = false; // �����̎��i���h���b�O���Ă��邩
	int dragNum = 0; // �h���b�O���Ă�����i�̔ԍ�

	int imgNumber = 0; // �摜�Ǘ��̔ԍ�
	int shariNumber = 0; // �V�����̔ԍ�
	int netaNumber = 0; // �l�^�̔ԍ�
	int sushiNumber = 0; // ���i�̔ԍ�
};

