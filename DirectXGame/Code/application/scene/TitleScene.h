#pragma once

#include "DirectXCommon.h"
#include "Keyboard.h"
#include "Controller.h"
#include "Mouse.h"
#include "Image2d.h"
#include "DebugText.h"
#include "Object3d.h"
#include "Audio.h"
#include "BaseScene.h"
#include "SafeDelete.h"
#include "Easing.h"
#include "LevelLoader.h"
#include "FadeScene.h"

class TitleScene : public BaseScene
{
public: // �����o�֐�
	// ������
	void Initialize() override;
	// �I��
	void Finalize() override;
	// ���t���[������
	void Update() override;
	// �`��
	void Draw() override;

	static bool isTutorial_first;

private: // �����o�ϐ�

	Keyboard* keyboard = Keyboard::GetInstance();
	Controller* controller = Controller::GetInstance();
	Mouse* mouse = Mouse::GetInstance();
	Audio* audio = Audio::GetInstance();
	Camera* camera = Camera::GetInstance();
	Light* light = Light::GetInstance();

	// �摜
	Image2d* title = nullptr;
	Image2d* tutorial = nullptr;
	Image2d* space = nullptr;

	float alpha = 0.0f;
	bool isChange = false;
	bool isTutorial = false;
};