#include "Sushi.h"

Sushi::Sushi()
{
	shari = Image2d::Create(Image2d::ImgNumber::shari, { 0.0f, 0.0f });
	shari->SetPosition({ 100.0f, 500.0f });
	shari->SetSize({ 160.0f, 160.0f });
	sushi_geta = Image2d::Create(Image2d::ImgNumber::sushi_geta, { 0.0f, 0.0f });
	sushi_geta->SetPosition({ 520.0f, 80.0f });
	sushi_geta->SetSize({ 240.0f, 240.0f });

	maguro = Image2d::Create(Image2d::ImgNumber::maguro, { 0.0f, 0.0f });
	maguro->SetPosition({ 300.0f, 500.0f });
	maguro->SetSize({ 160.0f, 160.0f });
	sushiList.push_back(maguro);
	maguro_neta = Image2d::Create(Image2d::ImgNumber::maguro_neta, { 0.0f, 0.0f });
	maguro_neta->SetPosition({ 500.0f, 500.0f });
	maguro_neta->SetSize({ 160.0f, 160.0f });
	sushiList.push_back(maguro_neta);
}

Sushi::~Sushi()
{
	safe_delete(shari);
	safe_delete(sushi_geta);
}

Sushi* Sushi::GetInstance()
{
	static Sushi instance;

	return &instance;
}

void Sushi::Update()
{
	for (Image2d*& image : sushiList)
	{
		XMFLOAT2 minPos = image->GetPosition();
		XMFLOAT2 maxPos = image->GetPosition() + image->GetSize();
		isDrag = image->GetIsDrag();

#pragma region �h���b�O�A���h�h���b�v
		// �摜���h���b�O��ԂȂ�
		if (isDrag)
		{
			// �摜�̒��S���}�E�X���W�ɂ���
			image->SetCenterPos(mouse->GetMousePos(), image->GetSize());

			// �h���b�O������Ԃŗ�������
			if (mouse->ReleaseMouseLeft())
			{
				image->SetIsDrag(false);
			}
		}
		else
		{
			//�}�E�X���N���b�N���摜���ŉ�����Ă��邩
			if (mouse->TriggerMouseLeft() && minPos < mouse->GetMousePos() && mouse->GetMousePos() < maxPos)
			{
				image->SetIsDrag(true);
			}
		}
#pragma endregion

#pragma region �V�����ƃl�^��g�ݍ��킹��

		if (shari->GetPosition() <= maxPos && shari->GetPosition() + shari->GetSize() >= minPos)
		{
			DebugText::GetInstance()->Print(10.0f, 40.0f, 2.0f, "hit");
		}

#pragma endregion
	}

	// �}�E�X�̑��΍��W��\��
	DebugText::GetInstance()->Print(10.0f, 10.0f, 2.0f, "(%d, %d)", (int)mouse->GetMousePos().x, (int)mouse->GetMousePos().y);
}

void Sushi::Draw()
{
	sushi_geta->Draw();
	shari->Draw();

	for (Image2d*& image : sushiList)
	{
		image->Draw();
	}
}
