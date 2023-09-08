#pragma once
#include <Windows.h>
#include <wrl.h>
#define DIRECTINPUT_VERSION     0x0800          // DirectInput�̃o�[�W�����w��
#include <dinput.h>
#include "WinApp.h"

#include "Operator.h"
class Mouse
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private:
	Mouse();

	~Mouse();
public:
	// �R�s�[�R���X�g���N�^�𖳌���
	Mouse(const Mouse& obj) = delete;
	// ������Z�q�𖳌���
	Mouse& operator=(const Mouse& obj) = delete;

public: // �ÓI�����o�ϐ�
	static Mouse* GetInstance();

public:
	// �}�E�X�̍��W
	struct MouseMove
	{
		long MouseX;
		long MouseY;
		long MouseZ;
	};
public: // �����o�֐�
	// ������
	bool Initialize(WinApp* win_app);

	// �X�V
	void Update();

	// �}�E�X�̈ړ�����
	void CursorLimit();

	// �}�E�X�̑��΍��W�̎擾
	XMFLOAT2 GetMousePos();

	// �L�[�̍��N���b�N���`�F�b�N
	bool PushMouseLeft();

	// �L�[�̒��{�^���������`�F�b�N
	bool PushMouseMiddle();

	// �L�[�̉E�N���b�N���`�F�b�N
	bool PushMouseRight();

	// �L�[�̍��N���b�N�g���K�[���`�F�b�N
	bool TriggerMouseLeft();

	// �L�[�̒��{�^���g���K�[���`�F�b�N
	bool TriggerMouseMiddle();

	// �L�[�̉E�N���b�N�g���K�[���`�F�b�N
	bool TriggerMouseRight();

	// �L�[�̍��N���b�N�����[�X���`�F�b�N
	bool ReleaseMouseLeft();

	// �L�[�̒��{�^�������[�X���`�F�b�N
	bool ReleaseMouseMiddle();

	// �L�[�̉E�N���b�N�����[�X���`�F�b�N
	bool ReleaseMouseRight();

	// �}�E�X�ړ��ʂ��擾
	MouseMove GetMouseMove();

private: // �����o�ϐ�

	WinApp* winApp = nullptr;

	// �f�o�C�X�֘A
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 mouseStatePre = {};

	// �E�B���h�E���W�擾�p
	HWND hwnd = NULL;
	RECT rcClient;
	POINT ptClientUL;
	POINT ptClientLR;

	// ���j�^�[���ォ��̐�΍��W(�}�E�X)
	POINT po;
};
