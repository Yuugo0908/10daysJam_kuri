#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <string>
#include "Operator.h"

class Image2d
{
protected: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT2 uv;  // uv���W
	};
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		XMFLOAT4 color; // �F (RGBA)
		XMMATRIX mat; // �R�c�ϊ��s��
	};
	// �Ǘ��ԍ�
	enum ImgNumber
	{
		debugTextNum,
		titleNum, backNum, resultNum,
		mouseNum, mouseLeftNum, mouseRightNum,

		rice, watar, 
		kama, kama_watar, kama_rice_watar, kama_rice,
		suihan_open, suihan_close,
		shari, wasabi, sushi_geta,

		maguro, samon, ebi, tamago, ika,
		maguro_neta, samon_neta, ebi_neta, tamago_neta, ika_neta
	};

public: // �ÓI�����o�֐�
	// �ÓI������
	static bool StaticInitialize(ID3D12Device* device);
	// �e�N�X�`���ǂݍ���
	static bool LoadTexture(UINT texnumber, const std::string& fileName);
	// �`��O����
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
	// �`��㏈��
	static void PostDraw();
	// �摜����
	static Image2d* Create(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color = { 1, 1, 1, 1 }, XMFLOAT2 anchorpoint = { 0.0f, 0.0f }, bool isFlipX = false, bool isFlipY = false);
	// �O���t�B�b�N�p�C�v���C������
	static bool CreateGraphicsPipeline();

protected: // �ÓI�����o�ϐ�
	// �e�N�X�`���̍ő喇��
	static const int srvCount = 512;
	// ���_��
	static const int vertNum = 4;
	// �f�o�C�X
	static ID3D12Device* device;
	// �f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootSignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelineState;
	// �ˉe�s��
	static XMMATRIX matProjection;
	// �f�X�N���v�^�q�[�v
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// �e�N�X�`���o�b�t�@
	static ComPtr<ID3D12Resource> texBuffer[srvCount];
	// �f�B���N�g��
	static const std::string baseDirectory;
	// �g���q
	static const std::string Extension;

public: // �����o�֐�
	// �R���X�g���N�^
	Image2d(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint, bool isFlipX, bool isFlipY);
	// ������
	bool Initialize();
	// �p�x�̐ݒ�
	void SetRotation(float rotation);
	// ���W�̐ݒ�
	void SetPosition(XMFLOAT2 position);
	// ���S���W�̐ݒ�
	void SetCenterPos(XMFLOAT2 position, XMFLOAT2 size);
	// �T�C�Y�̐ݒ�
	void SetSize(XMFLOAT2 size);
	// �F�̐ݒ�
	void SetColor(XMFLOAT4 color);
	// �A���J�[�|�C���g�̐ݒ�
	void SetAnchorPoint(XMFLOAT2 anchorpoint);
	// ���E���]�̐ݒ�
	void SetIsFlipX(bool isFlipX);
	// �㉺���]�̐ݒ�
	void SetIsFlipY(bool isFlipY);
	// �e�N�X�`���͈͐ݒ�
	void SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize);
	// �`��
	void Draw();
	// ���_�f�[�^�]��
	void TransferVertices();

	// ���W�擾
	const XMFLOAT2& GetPosition() { return position; }
	const XMFLOAT2& GetCenterPosition()
	{
		centerPos = position + (size / 2.0f);
		return centerPos;
	}
	// �T�C�Y�擾
	const XMFLOAT2& GetSize() { return size; }
	// �𑜓x�擾
	const XMFLOAT2& GetDataSize() { return dataSize; }

	// �h���b�O�ݒ�
	void SetIsDrag(bool isDrag) { this->isDrag = isDrag; }
	// �h���b�O�擾
	const bool& GetIsDrag() { return isDrag; }

	// �ԍ��ݒ�
	void SetNumber(int number) { this->number = number; }
	// �ԍ��擾
	const int& GetNumber() { return number; }
protected: // �����o�ϐ�
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuffer;
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffer;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// �e�N�X�`���ԍ�
	UINT texNumber = 0;
	// Z�����̉�]�p
	float rotation = 0.0f;
	// ���W
	XMFLOAT2 position{};
	// ���S���W
	XMFLOAT2 centerPos{};
	// �摜���A����
	XMFLOAT2 size = { 100.0f, 100.0f };
	// �A���J�[�|�C���g
	XMFLOAT2 anchorpoint = { 0, 0 };
	// ���[���h�s��
	XMMATRIX matWorld{};
	// �F
	XMFLOAT4 color = { 1, 1, 1, 1 };
	// ���E���]
	bool isFlipX = false;
	// �㉺���]
	bool isFlipY = false;
	// �e�N�X�`���n�_
	XMFLOAT2 texBase = { 0, 0 };
	// �e�N�X�`�����A����
	XMFLOAT2 texSize = { 100.0f, 100.0f };
	// �}�E�X�Œ͂�ł��邩
	bool isDrag = false;
	// ���f�[�^�̉𑜓x
	XMFLOAT2 dataSize{};
	// �摜�̖��O
	int number{};
};