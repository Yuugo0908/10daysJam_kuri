#include "Keyboard.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

Keyboard::Keyboard()
{

}

Keyboard::~Keyboard()
{

}

Keyboard* Keyboard::GetInstance()
{
	static Keyboard instance;

	return &instance;
}

bool Keyboard::Initialize(WinApp* win)
{
	HRESULT result = S_FALSE;

	// 初期化（一度だけ行う処理）
	result = DirectInput8Create
	(
		win->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr
	);
	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	// キーボードデバイスの生成
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	// 入力データ形式のセット
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	// 排他制御レベルのセット
	result = devkeyboard->SetCooperativeLevel
	(
		win->GetHwnd() , DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY
	);
	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	return true;
}

void Keyboard::Update()
{
	HRESULT result;

	// キーボード情報の取得開始
	result = devkeyboard->Acquire();
	// 前回のキー入力を保存
	memcpy(keyPre, key, sizeof(key));
	// 全キーの入力状態を取得する
	result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool Keyboard::PushKey(BYTE keyNumber)
{
	// 異常な引数を検出
	assert(0 <= keyNumber && keyNumber <= 256);

	// 0でなければ押している
	if (key[keyNumber])
	{
		return true;
	}

	// 押していない
	return false;
}

bool Keyboard::TriggerKey(BYTE keyNumber)
{
	// 異常な引数を検出
	assert(0 <= keyNumber && keyNumber <= 256);

	// 前回が0で、今回が0でなければトリガー
	if (!keyPre[keyNumber] && key[keyNumber])
	{
		return true;
	}

	// トリガーでない
	return false;
}

bool Keyboard::ReleaseKey(BYTE keyNumber)
{
	// 異常な引数を検出
	assert(0 <= keyNumber && keyNumber <= 256);

	// 前回が0で、今回が0でなければリリース
	if (keyPre[keyNumber] && !key[keyNumber])
	{
		return true;
	}

	// リリースでない
	return false;
}
