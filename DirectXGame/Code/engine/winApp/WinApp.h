#pragma once
#include <Windows.h>

class WinApp
{
public: // 静的メンバ変数
	// ウィンドウサイズ(最大化に合わせている)
	static const int window_width = 1920; // 横幅
	static const int window_height = 1080; // 縦幅
	static const wchar_t windowClassName[];

public: // 静的メンバ関数
	// ウィンドウプロシージャ
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

public: // メンバ関数
	// ゲームウィンドウの作成
	void CreateGameWindow();
	// ゲームウィンドウの破棄
	void TerminateGameWindow();
	// メッセージの処理
	bool ProcessMessage();

	// ウィンドウハンドルの取得
	HWND GetHwnd() { return hwnd; }
	// インスタンスの取得
	HINSTANCE GetInstance() { return wndClass.hInstance; }

private: // メンバ変数
	// Window関連
	HWND hwnd = nullptr; // ウィンドウハンドル
	WNDCLASSEX wndClass{}; // ウィンドウクラス
};