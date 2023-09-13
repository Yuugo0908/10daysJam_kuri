#include "GameScene.h"
#include <imgui.h>
#include <cassert>
#include "SceneManager.h"

void GameScene::Initialize()
{
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	// 画像の生成
	// 背景画像生成
	backGround_1 = Image2d::Create(Image2d::ImgNumber::back_1, { 0.0f,0.0f });
	backGround_1->SetSize({ 1920.0f,1080.0f });
	backGround_1->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	backGround_2 = Image2d::Create(Image2d::ImgNumber::back_2, { 0.0f,0.0f });
	backGround_2->SetSize({ 1920.0f,1080.0f });
	backGround_2->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	people_1 = Image2d::Create(Image2d::ImgNumber::people, { 80.0f,120.0f });
	people_1->SetSize({ 600.0f, 450.0f });
	people_2 = Image2d::Create(Image2d::ImgNumber::people, { 660.0f,120.0f });
	people_2->SetSize({ 600.0f, 450.0f });
	people_3 = Image2d::Create(Image2d::ImgNumber::people, { 1240.0f,120.0f });
	people_3->SetSize({ 600.0f, 450.0f });
	hukidasi_1 = Image2d::Create(Image2d::ImgNumber::hukidasi, { 80.0f,140.0f });
	hukidasi_1->SetSize({ 600.0f, 450.0f });
	hukidasi_2 = Image2d::Create(Image2d::ImgNumber::hukidasi, { 660.0f,140.0f });
	hukidasi_2->SetSize({ 600.0f, 450.0f });
	hukidasi_3 = Image2d::Create(Image2d::ImgNumber::hukidasi, { 1240.0f,140.0f });
	hukidasi_3->SetSize({ 600.0f, 450.0f });

	time_bar = Image2d::Create(Image2d::ImgNumber::time_bar, { 1840.0f, 200.0f });
	time_bar->SetSize({ 64.0f, 600.0f });
	time_gauge = Image2d::Create(Image2d::ImgNumber::time_gauge, { 1842.0f, 800.0f });
	time_gauge->SetSize({ 60.0f, (float)clear_timer / 9.0f });
	time_gauge->SetIsFlipY(true);

	sushi->Initialize();

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
	if (!isClear)
	{
		FadeScene::GetInstance()->FadeOut(1.0f);
	}

	if (isClear)
	{
		FadeScene::GetInstance()->FadeIn(0.0f);
		if (FadeScene::fadeInEnd)
		{
			clear_timer = 60 * 90;
			SceneManager::GetInstance()->ChangeScene("GameClear");
		}
	}

	if (FadeScene::fadeOutEnd && !isClear)
	{
		DebugText::GetInstance()->Print(90.0f, 20.0f, 2.0f, "%d", Sushi::score);
	}

#pragma endregion

	// TODO タイムアップでリザルト画面に移行
	if (clear_timer <= 0)
	{
		isClear = true;
	}
	else
	{
		clear_timer--;
	}

	sushi->Update();
}

void GameScene::Draw()
{
	// ImGuiの描画
	//SetImgui();

#pragma region 背景画像描画
	// 背景画像描画前処理
	Image2d::PreDraw(DirectXCommon::GetInstance()->GetCommandList());

	backGround_1->Draw();
	people_1->Draw();
	people_2->Draw();
	people_3->Draw();
	hukidasi_1->Draw();
	hukidasi_2->Draw();
	hukidasi_3->Draw();
	backGround_2->Draw();

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

	time_bar->Draw();

	time_gauge->SetSize({ 60.0f, (float)clear_timer / 9.0f });
	time_gauge->Draw();

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
