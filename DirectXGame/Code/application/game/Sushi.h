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
	// コピーコンストラクタを無効化
	Sushi(const Sushi& obj) = delete;
	// 代入演算子を無効化
	Sushi& operator=(const Sushi& obj) = delete;

public: // 静的メンバ変数
	static Sushi* GetInstance();

public: // メンバ関数
	// 毎フレーム処理
	void Update();
	// 描画
	void Draw();

private: // メンバ変数
	Controller* controller = Controller::GetInstance();
	Mouse* mouse = Mouse::GetInstance();
	Camera* camera = Camera::GetInstance();

	// 画像
	Image2d* shari = nullptr;
	Image2d* sushi_geta = nullptr;

	std::list<Image2d*> sushiList;
	Image2d* maguro = nullptr;
	Image2d* maguro_neta = nullptr;

	bool isDrag = false;
};

