#include "TitleScene.h"
#include <cassert>
#include "SceneManager.h"

bool TitleScene::isTutorial_first = false;

void TitleScene::Initialize()
{
	// タイトル画像生成
	title = Image2d::Create(Image2d::ImgNumber::title, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
	title->SetSize({ 1920.0f,1080.0f });
	tutorial = Image2d::Create(Image2d::ImgNumber::tutorial, { 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
	tutorial->SetSize({ 1920.0f,1080.0f });
	space = Image2d::Create(Image2d::ImgNumber::space_key, { 690.0f, 950.0f });
	space->SetSize(space->GetDataSize());

	// ライトの生成
	light = Light::Create();
	// ライトの色を設定
	light->SetLightColor({ 1.0f, 1.0f, 1.0f });
	// 3Dオブジェクトにライトをセット
	Object3d::SetLight(light);

	// TODO シフトで説明を表示できる案内を作る
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
#pragma region 背景画像描画
	// 背景画像描画前処理
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

	// 画像描画後処理
	Image2d::PostDraw();
	// 深度バッファクリア
	DirectXCommon::GetInstance()->ClearDepthBuffer();
#pragma endregion 背景画像描画

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion 3Dオブジェクト描画

#pragma region 前景画像描画
	// 前景画像描画前処理
	Image2d::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	// フェードの描画
	FadeScene::GetInstance()->Draw();

	// デバッグテキストの描画
	DebugText::GetInstance()->DrawAll(DirectXCommon::GetInstance()->GetCommandList());
	// 画像描画後処理
	Image2d::PostDraw();
#pragma endregion 前景画像描画
}
