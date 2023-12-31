#pragma once
#include "DirectXCommon.h"
#include "Audio.h"
#include "Keyboard.h"
#include "Camera.h"
#include "Object3d.h"
#include "PostEffect.h"
#include "SceneManager.h"
#include "Controller.h"
#include "Light.h"
#include "Mouse.h"
#include "AbstructSceneFactory.h"
#include "SafeDelete.h"
#include "FadeScene.h"

class Framework
{
public: // メンバ関数

	virtual ~Framework() = default;

	// 初期化
	virtual void Initialize();

	// 終了
	virtual void Finalize();

	// 毎フレーム更新
	virtual void Update();

	// 描画
	virtual void Draw();

	// 終了チェック
	virtual bool IsEndRequest() { return endRequest_; }

	// 実行
	void Run();

protected: // メンバ変数
	bool endRequest_ = false;
	//ポインタ置き場
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	Keyboard* keyboard = nullptr;
	Mouse* mouse = nullptr;
	Controller* controller = nullptr;
	Audio* audio = nullptr;
	Camera* camera = nullptr;
	PostEffect* postEffect = nullptr;
	SceneManager* sceneManager = nullptr;
	AbstructSceneFactory* sceneFactory_ = nullptr;
	// 初回起動確認用のフラグ
	bool firstBootFlag = false;
};

