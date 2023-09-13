#include "TitleScene.h"
#include <cassert>
#include "SceneManager.h"

bool TitleScene::isTutorial_first = false;

void TitleScene::Initialize()
{
	// �^�C�g���摜����
	title = Image2d::Create(Image2d::ImgNumber::title, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
	title->SetSize({ 1920.0f,1080.0f });
	tutorial = Image2d::Create(Image2d::ImgNumber::tutorial, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
	tutorial->SetSize({ 1920.0f,1080.0f });
	space = Image2d::Create(Image2d::ImgNumber::space_key, { 690.0f, 950.0f });
	space->SetSize(space->GetDataSize());

	// ���C�g�̐���
	light = Light::Create();
	// ���C�g�̐F��ݒ�
	light->SetLightColor({ 1.0f, 1.0f, 1.0f });
	// 3D�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	Object3d::SetLight(light);

	// TODO �V�t�g�Ő�����\���ł���ē������
}

void TitleScene::Finalize()
{
	safe_delete(title);
}

void TitleScene::Update()
{
	if (!isChange)
	{
		FadeScene::GetInstance()->FadeOut(1.0f);
	}

	if (FadeScene::fadeOutEnd && keyboard->TriggerKey(DIK_SPACE))
	{
		if (isTutorial == false && isTutorial_first == false)
		{
			isTutorial = true;
			isTutorial_first = true;
			return;
		}

		if (isChange == false)
		{
			isChange = true;
		}
	}

	if (isChange)
	{
		FadeScene::GetInstance()->FadeIn(0.0f);
		if (FadeScene::fadeInEnd)
		{
			SceneManager::GetInstance()->ChangeScene("Game");
		}
	}
}

void TitleScene::Draw()
{
#pragma region �w�i�摜�`��
	// �w�i�摜�`��O����
	Image2d::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	title->Draw();
	if (isTutorial && isTutorial_first)
	{
		tutorial->Draw();
	}
	if (isTutorial)
	{
		space->SetPosition({ 50.0f, 20.0f });
	}
	space->Draw();

	// �摜�`��㏈��
	Image2d::PostDraw();
	// �[�x�o�b�t�@�N���A
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion �w�i�摜�`��

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
#pragma endregion 3D�I�u�W�F�N�g�`��

#pragma region �O�i�摜�`��
	// �O�i�摜�`��O����
	Image2d::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	// �t�F�[�h�̕`��
	FadeScene::GetInstance()->Draw();

	// �f�o�b�O�e�L�X�g�̕`��
	DebugText::GetInstance()->DrawAll(DirectXCommon::GetInstance()->GetCommandList());
	// �摜�`��㏈��
	Image2d::PostDraw();
#pragma endregion �O�i�摜�`��
}
