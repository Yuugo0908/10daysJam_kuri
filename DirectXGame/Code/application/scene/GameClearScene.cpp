#include "GameClearScene.h"
#include "SceneManager.h"

void GameClearScene::Initialize()
{
	// �Q�[���N���A�摜����
	result = Image2d::Create(Image2d::ImgNumber::result, { 0.0f,0.0f });
	space = Image2d::Create(Image2d::ImgNumber::space_key, { 690.0f, 950.0f });

	Sushi::GetInstance()->Finalize();
}

void GameClearScene::Finalize()
{
	safe_delete(result);
}

void GameClearScene::Update()
{
	ClipCursor(NULL);
	if (!titleFlag)
	{
		FadeScene::GetInstance()->FadeOut(1.0f);
	}

	if (FadeScene::fadeOutEnd && keyboard->TriggerKey(DIK_SPACE) || controller->GetPadState(Controller::State::A, Controller::Type::TRIGGER))
	{
		titleFlag = true;
	}

	if (titleFlag)
	{
		FadeScene::GetInstance()->FadeIn(0.0f);
		if (FadeScene::fadeInEnd)
		{
			SceneManager::GetInstance()->ChangeScene("Title");
		}
	}

	if (FadeScene::fadeOutEnd)
	{
		if (!titleFlag)
		{
			DebugText::GetInstance()->Print(500, 350, 4, "%d", Sushi::score);
		}
		if (seFlag)
		{
			seFlag = false;
			Audio::GetInstance()->PlayWave("Resources/SE/result.wav", 0, 0.1f);
		}
	}
}

void GameClearScene::Draw()
{
#pragma region �w�i�摜�`��
	// �w�i�摜�`��O����
	Image2d::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	// �摜�`��㏈��
	Image2d::PostDraw();
	// �[�x�o�b�t�@�N���A
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion �w�i�摜�`��

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	// 3D�I�u�N�W�F�N�g�̕`��


	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
#pragma endregion 3D�I�u�W�F�N�g�`��

#pragma region �O�i�摜�`��
	// �O�i�摜�`��O����
	Image2d::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	// �O�i�摜�̕`��
	result->Draw();
	space->Draw();

	// �t�F�[�h�̕`��
	FadeScene::GetInstance()->Draw();

	// �f�o�b�O�e�L�X�g�̕`��
	DebugText::GetInstance()->DrawAll(DirectXCommon::GetInstance()->GetCommandList());
	// �摜�`��㏈��
	Image2d::PostDraw();
#pragma endregion �O�i�摜�`��
}
