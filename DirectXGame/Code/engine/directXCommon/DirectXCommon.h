#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <d3dx12.h>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "WinApp.h"

class DirectXCommon
{
protected: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
	// カメラ初期化
	DirectXCommon();

	~DirectXCommon();
public:
	// コピーコンストラクタを無効化
	DirectXCommon(const DirectXCommon& obj) = delete;
	// 代入演算子を無効化
	DirectXCommon& operator=(const DirectXCommon& obj) = delete;
public: // メンバ関数
	// インスタンス
	static DirectXCommon* GetInstance();

	// 初期化
	void Initialize(WinApp* win);
	// 描画前処理
	void PreDraw();
	/// 描画後処理
	void PostDraw();
	// レンダーターゲットのクリア
	void ClearRenderTarget();
	// 深度バッファのクリア
	void ClearDepthBuffer();

	// デバイスの取得
	ID3D12Device* GetDevice() { return device.Get(); }
	// 描画コマンドリストの取得
	ID3D12GraphicsCommandList* GetCommandList() { return commandList.Get(); }
	// ウィンドウハンドルの取得
	HWND GetHwnd() { return hwnd; }

private: // メンバ変数
	// ウィンドウズアプリケーション管理
	WinApp* winApp = nullptr;

	// Direct3D関連
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<ID3D12Device> device;
	ComPtr<ID3D12GraphicsCommandList> commandList;
	ComPtr<ID3D12CommandAllocator> commandAllocator;
	ComPtr<ID3D12CommandQueue> commandQueue;
	ComPtr<IDXGISwapChain4> swapchain;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;
	HWND hwnd = nullptr; // ウィンドウハンドル

	//imgui関連
	ComPtr<ID3D12DescriptorHeap> imguiHeap; // ヒープ保持用

	// FPS固定用変数
	// 記録時間(FPS固定用)
	std::chrono::steady_clock::time_point reference;

private: // メンバ関数
	// DXGIデバイス初期化
	bool InitializeDXGIDevice();
	// スワップチェーンの生成
	bool CreateSwapChain();
	// コマンド関連初期化
	bool InitializeCommand();
	// レンダーターゲット生成
	bool CreateFinalRenderTargets();
	// 深度バッファ生成
	bool CreateDepthBuffer();
	// フェンス生成
	bool CreateFence();
	// imguiの初期化
	bool InitImgui();
};