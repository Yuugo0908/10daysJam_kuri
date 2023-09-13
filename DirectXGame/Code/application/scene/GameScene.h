#pragma once

#include "DirectXCommon.h"
#include "Keyboard.h"
#include "Controller.h"
#include "Mouse.h"
#include "Image2d.h"
#include "DebugText.h"
#include "Object3d.h"
#include "Model.h"
#include "Operator.h"
#include "Camera.h"
#include "Audio.h"
#include "Collision.h"
#include "Light.h"
#include "Easing.h"
#include "LevelLoader.h"
#include "Particle.h"
#include "BaseScene.h"
#include "SafeDelete.h"
#include "FadeScene.h"
#include "Sushi.h"

#include <stdlib.h>
#include <time.h>
#include <list>

class GameScene : public BaseScene
{
public: // メンバ関数
	// 初期化
	void Initialize() override;
	// 終了
	void Finalize() override;
	// 毎フレーム処理
	void Update() override;
	// 描画
	void Draw() override;
	// Imguiの設定
	void SetImgui();

private: // メンバ変数
	Keyboard* keyboard = Keyboard::GetInstance();
	Controller* controller = Controller::GetInstance();
	Mouse* mouse = Mouse::GetInstance();
	Camera* camera = Camera::GetInstance();
	Light* light = Light::GetInstance();

	// 画像
	Sushi* sushi = Sushi::GetInstance();
	Image2d* backGround_1 = nullptr;
	Image2d* people_1 = nullptr;
	Image2d* people_2 = nullptr;
	Image2d* people_3 = nullptr;
	Image2d* hukidasi_1 = nullptr;
	Image2d* hukidasi_2 = nullptr;
	Image2d* hukidasi_3 = nullptr;
	Image2d* backGround_2 = nullptr;
	Image2d* time_bar = nullptr;
	Image2d* time_gauge = nullptr;

	bool isClear = false;
	bool isDrag = false;
	bool sceneChange = false;

	int clear_timer = 60 * 90;
};