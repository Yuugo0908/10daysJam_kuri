#include "GameScene.h"
#include <imgui.h>
#include <cassert>
#include "SceneManager.h"

void GameScene::Initialize()
{
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	// 画像の生成
	mouseImg = Image2d::Create(Image2d::ImgNumber::mouseNum, { 0.0f, 0.0f });
	mouseImg->SetPosition({ 1130.0f, 570.0f });
	mouseImg->SetSize({ 128.0f,128.0f });
	mouseLeftImg = Image2d::Create(Image2d::ImgNumber::mouseLeftNum, { 0.0f, 0.0f });
	mouseLeftImg->SetPosition({ 1130.0f, 570.0f });
	mouseLeftImg->SetSize({ 128.0f,128.0f });
	mouseRightImg = Image2d::Create(Image2d::ImgNumber::mouseRightNum, { 0.0f, 0.0f });
	mouseRightImg->SetPosition({ 1130.0f, 570.0f });
	mouseRightImg->SetSize({ 128.0f,128.0f });

	// パーティクル生成

	// ライトの生成
	light = Light::Create();
	// ライトの色を設定
	light->SetLightColor({ 1.0f, 1.0f, 1.0f });
	// 3Dオブジェクトにライトをセット
	Object3d::SetLight(light);
}

void GameScene::Finalize()
{
	//Bgm->Stop();
}

void GameScene::Update()
{
	// マウスの移動範囲の制限
	mouse->CursorLimit();

#pragma region フェードアウト
	if (!isClear && !isGameOver)
	{
		FadeScene::GetInstance()->FadeOut(1.0f);
	}

	if (isClear)
	{
		FadeScene::GetInstance()->FadeIn(-5.0f);
		if (FadeScene::fadeInEnd)
		{
		}
	}
	else if (isGameOver)
	{
		FadeScene::GetInstance()->FadeIn(-10.0f);
		if (FadeScene::fadeInEnd)
		{
		}
	}
#pragma endregion

	sushi->Update();

}

void GameScene::Draw()
{
	// ImGuiの描画
	SetImgui();

#pragma region 背景画像描画
	// 背景画像描画前処理
	Image2d::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	mouseImg->Draw();
	if (mouse->PushMouseLeft())
	{
		mouseLeftImg->Draw();
	}
	if (mouse->PushMouseRight())
	{
		mouseRightImg->Draw();
	}

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

#pragma region パーティクル描画

	//// パーティクル描画前処理
	//Particle::PreDraw(DirectXCommon::GetInstance()->GetCommandList());


	//// パーティクル描画後処理
	//Particle::PostDraw();

#pragma endregion パーティクル描画

#pragma region 前景画像描画
	// 前景画像描画前処理
	Image2d::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	sushi->Draw();

	// フェードの描画
	FadeScene::GetInstance()->Draw();

	// デバッグテキストの描画
	DebugText::GetInstance()->DrawAll(DirectXCommon::GetInstance()->GetCommandList());
	// 画像描画後処理
	Image2d::PostDraw();
#pragma endregion 前景画像描画
}

void GameScene::SetImgui()
{
	ImGui::Begin("DebugText");
	ImGui::SetWindowSize(ImVec2(300, 200));
	ImGui::Separator();
	ImGui::Text("Frame rate: %6.2f fps", ImGui::GetIO().Framerate);
	ImGui::End();
}
