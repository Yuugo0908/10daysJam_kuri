#include "GameClearScene.h"
#include "SceneManager.h"

void GameClearScene::Initialize()
{
	// ゲームクリア画像生成
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
#pragma region 背景画像描画
	// 背景画像描画前処理
	Image2d::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	// 画像描画後処理
	Image2d::PostDraw();
	// 深度バッファクリア
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion 背景画像描画

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	// 3Dオブクジェクトの描画


	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion 3Dオブジェクト描画

#pragma region 前景画像描画
	// 前景画像描画前処理
	Image2d::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	// 前景画像の描画
	result->Draw();
	space->Draw();

	// フェードの描画
	FadeScene::GetInstance()->Draw();

	// デバッグテキストの描画
	DebugText::GetInstance()->DrawAll(DirectXCommon::GetInstance()->GetCommandList());
	// 画像描画後処理
	Image2d::PostDraw();
#pragma endregion 前景画像描画
}
