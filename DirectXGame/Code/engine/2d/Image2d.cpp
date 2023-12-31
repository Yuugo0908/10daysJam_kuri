#include "Image2d.h"
#include "WinApp.h"
#include <cassert>
#include <d3dx12.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

// 静的メンバ変数の実体
ID3D12Device* Image2d::device = nullptr;
UINT Image2d::descriptorHandleIncrementSize;
ID3D12GraphicsCommandList* Image2d::cmdList = nullptr;
ComPtr<ID3D12RootSignature> Image2d::rootSignature;
ComPtr<ID3D12PipelineState> Image2d::pipelineState;
XMMATRIX Image2d::matProjection;
ComPtr<ID3D12DescriptorHeap> Image2d::descHeap;
ComPtr<ID3D12Resource> Image2d::texBuffer[srvCount];
const std::string Image2d::baseDirectory = "Resources/Image/";
const std::string Image2d::Extension = ".png";

bool Image2d::StaticInitialize(ID3D12Device* device)
{
	// nullptrチェック
	assert(device);

	Image2d::device = device;

	// デスクリプタサイズを取得
	descriptorHandleIncrementSize = Image2d::device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	// パイプライン初期化
	CreateGraphicsPipeline();

	return true;
}

bool Image2d::LoadTexture(UINT texnumber, const std::string& fileName)
{
	// nullptrチェック
	assert(device);

	HRESULT result;
	// WICテクスチャのロード
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	std::string fullPath{};

	fullPath = baseDirectory + fileName + Extension;

	// ユニコード文字列に変換する
	wchar_t wfilepath[128];
	int iBufferSize = MultiByteToWideChar
	(
		CP_ACP,
		0,
		fullPath.c_str(),
		-1,
		wfilepath,
		_countof(wfilepath)
	);

	result = LoadFromWICFile
	(
		wfilepath, WIC_FLAGS_NONE,
		&metadata, scratchImg
	);
	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	const Image* img = scratchImg.GetImage(0, 0, 0); // 生データ抽出

	// リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D
	(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);

	// テクスチャ用バッファの生成
	result = device->CreateCommittedResource
	(
		&CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, // テクスチャ用指定
		nullptr,
		IID_PPV_ARGS(&texBuffer[texnumber])
	);
	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	// テクスチャバッファにデータ転送
	result = texBuffer[texnumber]->WriteToSubresource
	(
		0,
		nullptr, // 全領域へコピー
		img->pixels,    // 元データアドレス
		(UINT)img->rowPitch,  // 1ラインサイズ
		(UINT)img->slicePitch // 1枚サイズ
	);
	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	// シェーダリソースビュー作成
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; // 設定構造体
	D3D12_RESOURCE_DESC resDesc = texBuffer[texnumber]->GetDesc();

	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	device->CreateShaderResourceView
	(
		texBuffer[texnumber].Get(), //ビューと関連付けるバッファ
		&srvDesc, //テクスチャ設定情報
		CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), texnumber, descriptorHandleIncrementSize)
	);

	return true;
}

void Image2d::PreDraw(ID3D12GraphicsCommandList* cmdList)
{
	// PreDrawとPostDrawがペアで呼ばれていなければエラー
	assert(Image2d::cmdList == nullptr);

	// コマンドリストをセット
	Image2d::cmdList = cmdList;

	// パイプラインステートの設定
	Image2d::cmdList->SetPipelineState(pipelineState.Get());
	// ルートシグネチャの設定
	Image2d::cmdList->SetGraphicsRootSignature(rootSignature.Get());
	// プリミティブ形状を設定
	Image2d::cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void Image2d::PostDraw()
{
	// コマンドリストを解除
	Image2d::cmdList = nullptr;
}

Image2d* Image2d::Create(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY)
{
	// 仮サイズ
	XMFLOAT2 size = { 100.0f, 100.0f };

	if (texBuffer[texNumber])
	{
		// テクスチャ情報取得
		D3D12_RESOURCE_DESC resDesc = texBuffer[texNumber]->GetDesc();
		// スプライトのサイズをテクスチャのサイズに設定
		size = { (float)resDesc.Width, (float)resDesc.Height };
	}

	// Image2dのインスタンスを生成
	Image2d* image2d = new Image2d(texNumber, position, size, color, anchorpoint, isFlipX, isFlipY);
	if (image2d == nullptr)
	{
		return nullptr;
	}

	// 初期化
	if (!image2d->Initialize())
	{
		delete image2d;
		assert(0);
		return nullptr;
	}

	return image2d;
}

bool Image2d::CreateGraphicsPipeline()
{
	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob; // ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト

	// 頂点シェーダの読み込みとコンパイル
	result = D3DCompileFromFile
	(
		L"Resources/shaders/Image2dVS.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&vsBlob, &errorBlob
	);
	if (FAILED(result))
	{
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());

		return false;
	}

	// ピクセルシェーダの読み込みとコンパイル
	result = D3DCompileFromFile
	(
		L"Resources/shaders/Image2dPS.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&psBlob, &errorBlob
	);
	if (FAILED(result))
	{
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());

		return false;
	}

	// 頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
		{ // xy座標(1行で書いたほうが見やすい)
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{ // uv座標(1行で書いたほうが見やすい)
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};

	// グラフィックスパイプラインの流れを設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	// サンプルマスク
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定
	// ラスタライザステート
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
	// デプスステンシルステート
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // 常に上書きルール

	// レンダーターゲットのブレンド設定
	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; // RBGA全てのチャンネルを描画
	blenddesc.BlendEnable = true;
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

	// ブレンドステートの設定
	gpipeline.BlendState.RenderTarget[0] = blenddesc;

	// 深度バッファのフォーマット
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	// 頂点レイアウトの設定
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	// 図形の形状設定（三角形）
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 1; // 描画対象は1つ
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0〜255指定のRGBA
	gpipeline.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	// デスクリプタレンジ
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV{};
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); // t0 レジスタ

	// ルートパラメータ
	CD3DX12_ROOT_PARAMETER rootparams[2]{};
	rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[1].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);

	// スタティックサンプラー
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0, D3D12_FILTER_MIN_MAG_MIP_POINT); // s0 レジスタ

	// ルートシグネチャの設定
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob;
	// バージョン自動判定のシリアライズ
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	if (FAILED(result))
	{
		assert(0);
		return false;
	}
	// ルートシグネチャの生成
	result = device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	gpipeline.pRootSignature = rootSignature.Get();

	// グラフィックスパイプラインの生成
	result = device->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineState));

	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	// 射影行列計算
	matProjection = XMMatrixOrthographicOffCenterLH
	(
		0.0f, (float)WinApp::window_width,
		(float)WinApp::window_height, 0.0f,
		0.0f, 1.0f
	);

	// デスクリプタヒープを生成	
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
	descHeapDesc.NumDescriptors = srvCount;
	result = device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));//生成
	if (FAILED(result))
	{
		assert(0);
		return false;
	}
	return true;
}

Image2d::Image2d(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY)
{
	this->position = position;
	this->size = size;
	this->anchorpoint = anchorpoint;
	this->matWorld = XMMatrixIdentity();
	this->color = color;
	this->texNumber = texNumber;
	this->isFlipX = isFlipX;
	this->isFlipY = isFlipY;
	this->texSize = size;
}

bool Image2d::Initialize()
{
	// nullptrチェック
	assert(device);

	HRESULT result = S_FALSE;

	// 頂点バッファ生成
	result = device->CreateCommittedResource
	(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(VertexPosUv) * vertNum),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuffer)
	);
	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	// 頂点バッファへのデータ転送
	TransferVertices();

	// 頂点バッファビューの作成
	vbView.BufferLocation = vertBuffer->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeof(VertexPosUv) * 4;
	vbView.StrideInBytes = sizeof(VertexPosUv);

	// 定数バッファの生成
	result = device->CreateCommittedResource
	(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), // アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffer)
	);
	if (FAILED(result))
	{
		assert(0);
		return false;
	}

	// 定数バッファにデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuffer->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result))
	{
		constMap->color = color;
		constMap->mat = matProjection;
		constBuffer->Unmap(0, nullptr);
	}

	return true;
}

void Image2d::SetRotation(float rotation)
{
	this->rotation = rotation;

	// 頂点バッファへのデータ転送
	TransferVertices();
}

void Image2d::SetPosition(XMFLOAT2 position)
{
	this->position = position;

	// 頂点バッファへのデータ転送
	TransferVertices();
}

void Image2d::SetCenterPos(XMFLOAT2 position, XMFLOAT2 size)
{
	this->position = position - (size / 2.0f);
	// 頂点バッファへのデータ転送
	TransferVertices();
}

void Image2d::SetSize(XMFLOAT2 size)
{
	this->size = size;

	// 頂点バッファへのデータ転送
	TransferVertices();
}

void Image2d::SetColor(XMFLOAT4 color)
{
	this->color = color;
}

void Image2d::SetAnchorPoint(XMFLOAT2 anchorpoint)
{
	this->anchorpoint = anchorpoint;

	// 頂点バッファへのデータ転送
	TransferVertices();
}

void Image2d::SetIsFlipX(bool isFlipX)
{
	this->isFlipX = isFlipX;

	// 頂点バッファへのデータ転送
	TransferVertices();
}

void Image2d::SetIsFlipY(bool isFlipY)
{
	this->isFlipY = isFlipY;

	// 頂点バッファへのデータ転送
	TransferVertices();
}

void Image2d::SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize)
{
	this->texBase = texBase;
	this->texSize = texSize;

	// 頂点バッファへのデータ転送
	TransferVertices();
}

void Image2d::Draw()
{
	// ワールド行列の更新
	this->matWorld = XMMatrixIdentity();
	this->matWorld *= XMMatrixRotationZ(XMConvertToRadians(rotation));
	this->matWorld *= XMMatrixTranslation(position.x, position.y, 0.0f);

	// 定数バッファにデータ転送
	ConstBufferData* constMap = nullptr;
	HRESULT result = this->constBuffer->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result))
	{
		constMap->color = this->color;
		constMap->mat = this->matWorld * matProjection;	// 行列の合成	
		this->constBuffer->Unmap(0, nullptr);
	}

	// 頂点バッファの設定
	cmdList->IASetVertexBuffers(0, 1, &this->vbView);

	ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
	// デスクリプタヒープをセット
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	// 定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(0, this->constBuffer->GetGPUVirtualAddress());
	// シェーダリソースビューをセット
	cmdList->SetGraphicsRootDescriptorTable(1, CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), this->texNumber, descriptorHandleIncrementSize));
	// 描画コマンド
	cmdList->DrawInstanced(4, 1, 0, 0);
}

void Image2d::TransferVertices()
{
	HRESULT result = S_FALSE;

	// 左下、左上、右下、右上
	enum { LB, LT, RB, RT };

	float left = (0.0f - anchorpoint.x) * size.x;
	float right = (1.0f - anchorpoint.x) * size.x;
	float top = (0.0f - anchorpoint.y) * size.y;
	float bottom = (1.0f - anchorpoint.y) * size.y;

	if (isFlipX)
	{// 左右入れ替え
		left = -left;
		right = -right;
	}

	if (isFlipY)
	{// 上下入れ替え
		top = -top;
		bottom = -bottom;
	}

	// 頂点データ
	VertexPosUv vertices[vertNum]{};

	vertices[LB].pos = { left,	bottom,	0.0f }; // 左下
	vertices[LT].pos = { left,	top,	0.0f }; // 左上
	vertices[RB].pos = { right,	bottom,	0.0f }; // 右下
	vertices[RT].pos = { right,	top,	0.0f }; // 右上

	// テクスチャ情報取得
	if (texBuffer[texNumber])
	{
		D3D12_RESOURCE_DESC resDesc = texBuffer[texNumber]->GetDesc();

		float tex_left = texBase.x / resDesc.Width;
		float tex_right = (texBase.x + texSize.x) / resDesc.Width;
		float tex_top = texBase.y / resDesc.Height;
		float tex_bottom = (texBase.y + texSize.y) / resDesc.Height;

		// 解像度として保存する(ゲッター用)
		dataSize = { (float)resDesc.Width, (float)resDesc.Height};

		vertices[LB].uv = { tex_left,	tex_bottom }; // 左下
		vertices[LT].uv = { tex_left,	tex_top }; // 左上
		vertices[RB].uv = { tex_right,	tex_bottom }; // 右下
		vertices[RT].uv = { tex_right,	tex_top }; // 右上
	}

	// 頂点バッファへのデータ転送
	VertexPosUv* vertMap = nullptr;
	result = vertBuffer->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result))
	{
		memcpy(vertMap, vertices, sizeof(vertices));
		vertBuffer->Unmap(0, nullptr);
	}
}