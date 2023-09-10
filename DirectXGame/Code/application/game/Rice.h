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
	// コピーコンストラクタを無効化
	Rice(const Rice& obj) = delete;
	// 代入演算子を無効化
	Rice& operator=(const Rice& obj) = delete;
public: // 静的メンバ変数
	static Rice* GetInstance();
public: // メンバ関数
	// 毎フレーム処理
	void Update();
	// 描画
	void Draw();

private: // メンバ変数
	Mouse* mouse = Mouse::GetInstance();

	// 画像
	Image2d* rice = nullptr;
	Image2d* watar = nullptr;

	Image2d* kama = nullptr;
	Image2d* kama_watar = nullptr;
	Image2d* kama_rice_watar = nullptr;
	Image2d* kama_rice = nullptr;

	Image2d* suihan_open = nullptr;
	Image2d* suihan_close = nullptr;
};

