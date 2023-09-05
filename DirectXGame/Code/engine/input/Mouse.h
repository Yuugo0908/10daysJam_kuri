#pragma once
#include <Windows.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定
#include <dinput.h>
#include "Operator.h"
#include "WinApp.h"
class Mouse
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	Mouse();

	~Mouse();
public:
	// コピーコンストラクタを無効化
	Mouse(const Mouse& obj) = delete;
	// 代入演算子を無効化
	Mouse& operator=(const Mouse& obj) = delete;

public: // 静的メンバ変数
	static Mouse* GetInstance();

public:
	// マウスの座標
	struct MouseMove
	{
		long MouseX;
		long MouseY;
		long MouseZ;
	};
public: // メンバ関数
	// 初期化
	bool Initialize(WinApp* win_app);

	// 更新
	void Update();

	// マウスの移動制限
	void CursorLimit();

	// マウスの相対座標の取得
	XMFLOAT2 GetMousePos();

	// キーの左クリックをチェック
	bool PushMouseLeft();

	// キーの中ボタン押下をチェック
	bool PushMouseMiddle();

	// キーの右クリックをチェック
	bool PushMouseRight();

	// キーの左クリックトリガーをチェック
	bool TriggerMouseLeft();

	// キーの中ボタントリガーをチェック
	bool TriggerMouseMiddle();

	// キーの右クリックトリガーをチェック
	bool TriggerMouseRight();

	// キーの左クリックリリースをチェック
	bool ReleaseMouseLeft();

	// キーの中ボタンリリースをチェック
	bool ReleaseMouseMiddle();

	// キーの右クリックリリースをチェック
	bool ReleaseMouseRight();

	// マウス移動量を取得
	MouseMove GetMouseMove();

private: // メンバ変数

	WinApp* winApp = nullptr;

	// デバイス関連
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 mouseStatePre = {};

	// ウィンドウ座標取得用
	HWND hwnd = NULL;
	RECT rcClient;
	POINT ptClientUL;
	POINT ptClientLR;

	// モニター左上からの絶対座標(マウス)
	POINT po;
};

