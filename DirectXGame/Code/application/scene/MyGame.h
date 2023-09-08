#pragma once
#include "Framework.h"
#include <chrono>
#include <functional>

// ゲーム全体
class MyGame : public Framework
{
public: // メンバ関数

	// 初期化
	void Initialize() override;
	// 終了
	void Finalize() override;
	// 毎フレーム更新
	void Update() override;
	// 描画
	void Draw() override;

private: // メンバ変数

	std::function<long long(void)> currentTimeMicro;
	int fps;
	long long end;
	long long next;
};