#pragma once
#include "DirectXCommon.h"
#include "Image2d.h"
#include "Object3d.h"
#include "BaseScene.h"
#include "SafeDelete.h"
#include "Easing.h"
#include "Audio.h"

enum FadeState
{
	None,
	FadeInPlay,
	FadeInEnd,
	FadeOutPlay,
	FadeOutEnd,
};

class FadeScene
{
private:

	FadeScene();

	~FadeScene();

public:
	// �R�s�[�R���X�g���N�^�𖳌���
	FadeScene(const FadeScene& obj) = delete;
	// ������Z�q�𖳌���
	FadeScene& operator=(const FadeScene& obj) = delete;

public: // �ÓI�����o�֐�
	static FadeScene* GetInstance();

public: // �ÓI�����o�ϐ�
	static bool fadeInEnd;
	static bool fadeOutEnd;

public: // �����o�֐�
	// ���t���[������
	void Update();
	// �`��
	void Draw();
	// �t�F�[�h�C��
	void FadeIn(float alpha);
	// �t�F�[�h�A�E�g
	void FadeOut(float alpha);

	void reset();

private: // �����o�ϐ�

	Image2d* door_right = nullptr;
	Image2d* door_left = nullptr;
	FadeState fadeState{};

	const XMFLOAT2 door_left_open_pos = { -960.0f, 0.0f };
	const XMFLOAT2 door_left_close_pos = { 0.0f, 0.0f };
	const XMFLOAT2 door_right_open_pos = { 1920.0f, 0.0f };
	const XMFLOAT2 door_right_close_pos = { 960.0f, 0.0f };

	float alpha = 0.0f;
	float alphaAdd = 0.0f;
	int fadeNum = 50;
	int fadeNumMax = 16;
	int fadeCount = 0;
};