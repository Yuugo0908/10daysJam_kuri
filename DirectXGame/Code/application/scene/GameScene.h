﻿#pragma once

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

private: // メンバ変数
	Keyboard* keyboard = Keyboard::GetInstance();
	Controller* controller = Controller::GetInstance();
	Mouse* mouse = Mouse::GetInstance();
	Camera* camera = Camera::GetInstance();
	Light* light = Light::GetInstance();

	// 画像
	Sushi* sushi = Sushi::GetInstance();
	Image2d* mouseImg = nullptr;
	Image2d* mouseLeftImg = nullptr;
	Image2d* mouseRightImg = nullptr;

	bool isClear = false;
	bool isGameOver = false;
	bool isDrag = false;
};