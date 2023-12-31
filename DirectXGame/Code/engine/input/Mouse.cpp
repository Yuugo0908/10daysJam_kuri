#include "Mouse.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

Mouse* Mouse::GetInstance()
{
	static Mouse instance;

	return &instance;
}

bool Mouse::Initialize(WinApp* win_app)
{
	HRESULT result = S_FALSE;

	assert(!dinput);
	assert(win_app);

	this->winApp = win_app;

	// DirectInputオブジェクトの生成	
	result = DirectInput8Create(win_app->GetInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	// マウスデバイスの生成	
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	// 入力データ形式のセット
	result = devMouse->SetDataFormat(&c_dfDIMouse2); // 標準形式
	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	// 排他制御レベルのセット
	result = devMouse->SetCooperativeLevel(win_app->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	return true;
}

void Mouse::Update()
{
	HRESULT result;
	// マウス動作開始
	result = devMouse->Acquire();

	// 前回の入力を保存
	mouseStatePre = mouseState;

	// マウスの入力
	result = devMouse->GetDeviceState(sizeof(mouseState), &mouseState);
}

void Mouse::CursorLimit()
{
	hwnd = winApp->GetHwnd();
	GetClientRect(hwnd, &rcClient);

	ptClientUL.x = rcClient.left;
	ptClientUL.y = rcClient.top;
	ptClientLR.x = rcClient.right;
	ptClientLR.y = rcClient.bottom;
	ClientToScreen(hwnd, &ptClientUL);
	ClientToScreen(hwnd, &ptClientLR);

	SetRect(&rcClient, ptClientUL.x, ptClientUL.y, ptClientLR.x, ptClientLR.y);

	ClipCursor(&rcClient);
}

XMFLOAT2 Mouse::GetMousePos()
{
	//マウス座標取得
	GetCursorPos(&po);

	hwnd = winApp->GetHwnd();
	GetClientRect(hwnd, &rcClient);

	ptClientUL.x = rcClient.left;
	ptClientUL.y = rcClient.top;
	ptClientLR.x = rcClient.right;
	ptClientLR.y = rcClient.bottom;
	ClientToScreen(hwnd, &ptClientUL);
	ClientToScreen(hwnd, &ptClientLR);

	SetRect(&rcClient, ptClientUL.x, ptClientUL.y, ptClientLR.x, ptClientLR.y);

	XMFLOAT2 cursorPos = { (float)po.x * WinApp::window_width / rcClient.right + WinApp::window_width / rcClient.right,
							(float)po.y * WinApp::window_height / rcClient.bottom + WinApp::window_height / rcClient.bottom };
	return cursorPos;
}

bool Mouse::PushMouseLeft()
{
	// 0でなければ押している
	if (mouseState.rgbButtons[0])
	{
		return true;
	}

	// 押していない
	return false;
}

bool Mouse::PushMouseMiddle()
{
	// 0でなければ押している
	if (mouseState.rgbButtons[2])
	{
		return true;
	}

	// 押していない
	return false;
}

bool Mouse::PushMouseRight()
{
	// 0でなければ押している
	if (mouseState.rgbButtons[1])
	{
		return true;
	}

	// 押していない
	return false;
}

bool Mouse::TriggerMouseLeft()
{
	// 前回が0で、今回が0でなければトリガー
	if (!mouseStatePre.rgbButtons[0] && mouseState.rgbButtons[0])
	{
		return true;
	}

	// トリガーでない
	return false;
}

bool Mouse::TriggerMouseMiddle()
{
	// 前回が0で、今回が0でなければトリガー
	if (!mouseStatePre.rgbButtons[2] && mouseState.rgbButtons[2])
	{
		return true;
	}

	// トリガーでない
	return false;
}

bool Mouse::TriggerMouseRight()
{
	// 前回が0で、今回が0でなければトリガー
	if (!mouseStatePre.rgbButtons[1] && mouseState.rgbButtons[1])
	{
		return true;
	}

	// トリガーでない
	return false;
}

bool Mouse::ReleaseMouseLeft()
{
	// 前回が1で、今回が1でなければリリース
	if (mouseStatePre.rgbButtons[0] && !mouseState.rgbButtons[0])
	{
		return true;
	}

	// リリースでない
	return false;
}

bool Mouse::ReleaseMouseMiddle()
{
	// 前回が1で、今回が1でなければリリース
	if (mouseStatePre.rgbButtons[2] && !mouseState.rgbButtons[2])
	{
		return true;
	}

	// リリースでない
	return false;
}

bool Mouse::ReleaseMouseRight()
{
	// 前回が1で、今回が1でなければリリース
	if (mouseStatePre.rgbButtons[1] && !mouseState.rgbButtons[1])
	{
		return true;
	}

	// リリースでない
	return false;
}

Mouse::MouseMove Mouse::GetMouseMove()
{
	MouseMove tmp = {};
	tmp.MouseX = mouseState.lX;
	tmp.MouseY = mouseState.lY;
	tmp.MouseZ = mouseState.lZ;
	return tmp;
}
