#pragma once
#include "Framework.h"
#include <chrono>
#include <functional>

// �Q�[���S��
class MyGame : public Framework
{
public: // �����o�֐�

	// ������
	void Initialize() override;
	// �I��
	void Finalize() override;
	// ���t���[���X�V
	void Update() override;
	// �`��
	void Draw() override;

private: // �����o�ϐ�

	std::function<long long(void)> currentTimeMicro;
	int fps;
	long long end;
	long long next;
};