#include "Sushi.h"

Sushi::Sushi()
{
	// ���i����
	sushi_geta_1 = Image2d::Create(Image2d::ImgNumber::sushi_geta, { 0.0f, 0.0f });
	sushi_geta_1->SetPosition({ 1319.0f / 2, 1100.0f / 2 });
	sushi_geta_1->SetSize(sushi_geta_1->GetDataSize());
	sushi_geta_1->SetNumber(Image2d::ImgNumber::sushi_geta);
	sushi_geta_2 = Image2d::Create(Image2d::ImgNumber::sushi_geta, { 0.0f, 0.0f });
	sushi_geta_2->SetPosition({ 1319.0f / 2, 1100.0f / 2 });
	sushi_geta_2->SetSize(sushi_geta_2->GetDataSize());
	sushi_geta_2->SetNumber(Image2d::ImgNumber::sushi_geta);
	sushi_geta_3 = Image2d::Create(Image2d::ImgNumber::sushi_geta, { 0.0f, 0.0f });
	sushi_geta_3->SetPosition({ 1319.0f / 2, 1100.0f / 2 });
	sushi_geta_3->SetSize(sushi_geta_3->GetDataSize());
	sushi_geta_3->SetNumber(Image2d::ImgNumber::sushi_geta);
	sushi_getas.push_back(sushi_geta_1);
	sushi_getas.push_back(sushi_geta_2);
	sushi_getas.push_back(sushi_geta_3);
}

Sushi::~Sushi()
{
	safe_delete(shari);
}

Sushi* Sushi::GetInstance()
{
	static Sushi instance;
	return &instance;
}

void Sushi::Update()
{
	// �l�^�A�V��������
	MakeNeta();
	// ���i����
	MakeSushi();
	// �h���b�O�A���h�h���b�v
	DragDrop();
}

void Sushi::Draw()
{
	for (int i = 0; i < sushi_getas.size(); i++)
	{
		sushi_getas[i]->Draw();
	}

	// �`��̓��X�g�̌�납��
	for (int j = (int)shari_list.size() - 1; j >= 0; --j)
	{
		shari_list[j]->Draw();
	}

	for (int i = (int)sushi_list.size() - 1; i >= 0; --i)
	{
		sushi_list[i]->Draw();
	}

	if ((int)sushi_list.size() != 0)
	{
		// �h���b�O���Ă�����i���őO�ʂɂ���
		sushi_list[dragNum]->Draw();
	}
}

void Sushi::DragDrop()
{
#pragma region �h���b�O�A���h�h���b�v
	for (int i = 0; i < sushi_list.size(); i++)
	{
		// �摜�̍ŏ��ƍő�
		XMFLOAT2 minPos = sushi_list[i]->GetCenterPosition() - sushi_list[i]->GetSize() / 2;
		XMFLOAT2 maxPos = sushi_list[i]->GetCenterPosition() + sushi_list[i]->GetSize() / 2;
		isDrag = sushi_list[i]->GetIsDrag();

		// �摜���h���b�O��ԂȂ�
		if (isDrag)
		{
			// �摜�̒��S���}�E�X���W�ɂ���
			sushi_list[i]->SetCenterPos(mouse->GetMousePos(), sushi_list[i]->GetSize());

			// �h���b�O������Ԃŗ�������
			if (mouse->ReleaseMouseLeft())
			{
				// �h���b�O��Ԃ̉���
				sushi_list[i]->SetIsDrag(false);
				// �l�^�̉摜�ԍ����擾
				netaNumber = sushi_list[i]->GetNumber();
				// �����_�ł̓h���b�O���Ă��Ȃ�
				isDragNow = false;

				if (dragData != nullptr)
				{
					drag_maxPos = dragData->GetCenterPosition() + dragData->GetSize() / 2;
					drag_minPos = dragData->GetCenterPosition() - dragData->GetSize() / 2;
				}
			}
		}
		else if (!isDragNow)
		{
			//�}�E�X���N���b�N���摜���ŉ�����Ă��邩
			if (mouse->TriggerMouseLeft() && minPos < mouse->GetMousePos() && mouse->GetMousePos() < maxPos)
			{
				sushi_list[i]->SetIsDrag(true);
				isDragNow = true;
				dragNum = i;
				dragData = sushi_list[i];
			}
		}
	}
#pragma endregion
}

void Sushi::MakeNeta()
{
# pragma region �l�^�V��������
	// �}�O������
	if (keyboard->TriggerKey(DIK_1))
	{
		maguro_neta = Image2d::Create(Image2d::ImgNumber::maguro_neta, { 0.0f, 0.0f });
		maguro_neta->SetPosition({ 200.0f, 500.0f });
		maguro_neta->SetSize(maguro_neta->GetDataSize());
		maguro_neta->SetNumber(Image2d::ImgNumber::maguro_neta);
		sushi_list.push_back(maguro_neta);
	}
	// �T�[��������
	if (keyboard->TriggerKey(DIK_2))
	{
		samon_neta = Image2d::Create(Image2d::ImgNumber::samon_neta, { 0.0f, 0.0f });
		samon_neta->SetPosition({ 300.0f, 500.0f });
		samon_neta->SetSize(samon_neta->GetDataSize());
		samon_neta->SetNumber(Image2d::ImgNumber::samon_neta);
		sushi_list.push_back(samon_neta);
	}
	// �G�r����
	if (keyboard->TriggerKey(DIK_3))
	{
		ebi_neta = Image2d::Create(Image2d::ImgNumber::ebi_neta, { 0.0f, 0.0f });
		ebi_neta->SetPosition({ 400.0f, 500.0f });
		ebi_neta->SetSize(ebi_neta->GetDataSize());
		ebi_neta->SetNumber(Image2d::ImgNumber::ebi_neta);
		sushi_list.push_back(ebi_neta);
	}
	// �^�}�S����
	if (keyboard->TriggerKey(DIK_4))
	{
		tamago_neta = Image2d::Create(Image2d::ImgNumber::tamago_neta, { 0.0f, 0.0f });
		tamago_neta->SetPosition({ 500.0f, 500.0f });
		tamago_neta->SetSize(tamago_neta->GetDataSize());
		tamago_neta->SetNumber(Image2d::ImgNumber::tamago_neta);
		sushi_list.push_back(tamago_neta);
	}
	// �C�J����
	if (keyboard->TriggerKey(DIK_5))
	{
		ika_neta = Image2d::Create(Image2d::ImgNumber::ika_neta, { 0.0f, 0.0f });
		ika_neta->SetPosition({ 600.0f, 500.0f });
		ika_neta->SetSize(ika_neta->GetDataSize());
		ika_neta->SetNumber(Image2d::ImgNumber::ika_neta);
		sushi_list.push_back(ika_neta);
	}

	// �V��������
	if (keyboard->TriggerKey(DIK_Z))
	{
		shari = Image2d::Create(Image2d::ImgNumber::shari, { 0.0f, 0.0f });
		shari->SetPosition({ 100.0f, 500.0f });
		shari->SetSize(shari->GetDataSize());
		shari->SetNumber(Image2d::ImgNumber::shari);
		shariNumber = shari->GetNumber();
		shari_list.push_back(shari);
	}
#pragma endregion
}

void Sushi::MakeSushi()
{
	for (int j = 0; j < shari_list.size(); j++)
	{
#pragma region �V�����ƃl�^��g�ݍ��킹��
		if (isDragNow == false && shari_list[j]->GetPosition() <= drag_maxPos && shari_list[j]->GetPosition() + shari_list[j]->GetSize() >= drag_minPos)
		{
			if (netaNumber == Image2d::ImgNumber::maguro_neta)
			{
				shari_list.erase(shari_list.begin() + j);
				maguro = Image2d::Create(Image2d::ImgNumber::maguro, { 0.0f, 0.0f });
				maguro->SetPosition(mouse->GetMousePos() - maguro->GetDataSize() / 2);
				maguro->SetSize(maguro->GetDataSize());
				maguro->SetNumber(Image2d::ImgNumber::maguro);
				sushi_list.push_back(maguro);
				drag_maxPos = {};
				drag_minPos = {};
				isCombine = true;
			}
			else if (netaNumber == Image2d::ImgNumber::samon_neta)
			{
				shari_list.erase(shari_list.begin() + j);
				samon = Image2d::Create(Image2d::ImgNumber::samon, { 0.0f, 0.0f });
				samon->SetPosition(mouse->GetMousePos() - samon->GetDataSize() / 2);
				samon->SetSize(samon->GetDataSize());
				samon->SetNumber(Image2d::ImgNumber::samon);
				sushi_list.push_back(samon);
				drag_maxPos = {};
				drag_minPos = {};
				isCombine = true;
			}
			else if (netaNumber == Image2d::ImgNumber::ebi_neta)
			{
				shari_list.erase(shari_list.begin() + j);
				ebi = Image2d::Create(Image2d::ImgNumber::ebi, { 0.0f, 0.0f });
				ebi->SetPosition(mouse->GetMousePos() - ebi->GetDataSize() / 2);
				ebi->SetSize(ebi->GetDataSize());
				ebi->SetNumber(Image2d::ImgNumber::ebi);
				sushi_list.push_back(ebi);
				drag_maxPos = {};
				drag_minPos = {};
				isCombine = true;
			}
			else if (netaNumber == Image2d::ImgNumber::tamago_neta)
			{
				shari_list.erase(shari_list.begin() + j);
				tamago = Image2d::Create(Image2d::ImgNumber::tamago, { 0.0f, 0.0f });
				tamago->SetPosition(mouse->GetMousePos() - tamago->GetDataSize() / 2);
				tamago->SetSize(tamago->GetDataSize());
				tamago->SetNumber(Image2d::ImgNumber::tamago);
				sushi_list.push_back(tamago);
				drag_maxPos = {};
				drag_minPos = {};
				isCombine = true;
			}
			else if (netaNumber == Image2d::ImgNumber::ika_neta)
			{
				shari_list.erase(shari_list.begin() + j);
				ika = Image2d::Create(Image2d::ImgNumber::ika, { 0.0f, 0.0f });
				ika->SetPosition(mouse->GetMousePos() - ika->GetDataSize() / 2);
				ika->SetSize(ika->GetDataSize());
				ika->SetNumber(Image2d::ImgNumber::ika);
				sushi_list.push_back(ika);
				drag_maxPos = {};
				drag_minPos = {};
				isCombine = true;
			}

			if (isCombine)
			{
				isCombine = false;
				sushi_list.erase(sushi_list.begin() + dragNum);
				dragNum = 0;
			}

		}
		else if (isDragNow == false)
		{
			netaNumber = 0;
		}
#pragma endregion

#pragma region ���i�����i���ʂɂ̂���

#pragma endregion
	}
}

void Sushi::Pattern()
{
}
