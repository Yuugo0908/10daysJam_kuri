#include "Light.h"

/// <summary>
/// 静的メンバ変数の実体
/// </summary>
ID3D12Device* Light::device = nullptr;

Light* Light::Create()
{
	//3Dオブジェクトのインスタンスの生成
	Light* instance = new Light();
	//初期化
	instance->Initialize();
	//生成したインスタンスを返す
	return instance;
}

Light::Light()
{
}

Light::~Light()
{
}

Light* Light::GetInstance()
{
	static Light instance;

	return &instance;
}

bool Light::StaticInitialize(ID3D12Device* device)
{
	// 再初期化チェック
	assert(!Light::device);
	// nullptrチェック
	assert(device);
	// 静的メンバ変数のセット
	Light::device = device;

	return true;
}

void Light::Initialize()
{
	// nullptrチェック
	assert(device);

	HRESULT result;
	// 定数バッファの生成
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffer));

	//定数バッファへデータ転送
	TransferConstBuffer();
}

void Light::TransferConstBuffer()
{
	HRESULT result;
	//定数バッファへデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuffer->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result))
	{
		constMap->lightVec = -lightdir;
		constMap->lightColor = lightColor;
		constBuffer->Unmap(0, nullptr);
	}
}

void Light::SetLightDir(const XMVECTOR& lightdir)
{
	//正規化してセット
	this->lightdir = XMVector3Normalize(lightdir);
	dirty = true;
}

void Light::SetLightColor(const XMFLOAT3& lightcolor)
{
	this->lightColor = lightcolor;
	dirty = true;
}

void Light::Update()
{
	//値の更新があった時だけ定数バッファに転送する
	if (dirty)
	{
		TransferConstBuffer();
		dirty = false;
	}
}

void Light::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	//定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex,
		constBuffer->GetGPUVirtualAddress());
}
