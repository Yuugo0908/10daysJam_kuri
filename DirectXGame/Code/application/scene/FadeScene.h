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
	// コピーコンストラクタを無効化
	FadeScene(const FadeScene& obj) = delete;
	// 代入演算子を無効化
	FadeScene& operator=(const FadeScene& obj) = delete;

public: // 静的メンバ関数
	static FadeScene* GetInstance();

public: // 静的メンバ変数
	static bool fadeInEnd;
	static bool fadeOutEnd;

public: // メンバ関数
	// 毎フレーム処理
	void Update();
	// 描画
	void Draw();
	// フェードイン
	void FadeIn(float alpha);
	// フェードアウト
	void FadeOut(float alpha);

	void reset();

private: // メンバ変数

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