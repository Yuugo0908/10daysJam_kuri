#include "GameScene.h"
#include <imgui.h>
#include <cassert>
#include "SceneManager.h"

void GameScene::Initialize()
{
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	// 画像の生成
	spaceImg = Image2d::Create(Image2d::ImgNumber::spaceNum, { 0.0f, 0.0f });
	spaceImg->SetPosition({ 0.0f, 0.0f });
	spaceImg->SetSize({ 128.0f, 36.0f });
	imageList.push_back(spaceImg);
	mouseImg = Image2d::Create(Image2d::ImgNumber::mouseNum, { 0.0f, 0.0f });
	mouseImg->SetPosition({ 1000.0f, 400.0f });
	mouseImg->SetSize({ 256.0f,256.0f });
	mouseLeftImg = Image2d::Create(Image2d::ImgNumber::mouseLeftNum, { 0.0f, 0.0f });
	mouseLeftImg->SetPosition({ 1000.0f, 400.0f });
	mouseLeftImg->SetSize({ 256.0f,256.0f });
	mouseRightImg = Image2d::Create(Image2d::ImgNumber::mouseRightNum, { 0.0f, 0.0f });
	mouseRightImg->SetPosition({ 1000.0f, 400.0f });
	mouseRightImg->SetSize({ 256.0f,256.0f });
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


	for (Image2d*& image : imageList)
	{
		XMFLOAT2 minPos = image->GetPosition();
		XMFLOAT2 maxPos = image->GetPosition() + image->GetSize();

#pragma region ドラッグアンドドロップ
		// 画像がドラッグ状態なら
		if (isDrag)
		{
			// 画像の中心をマウス座標にする
			image->SetCenterPos(mouse->GetMousePos(), image->GetSize());

			// ドラッグした状態で離したら
			if (mouse->ReleaseMouseLeft())
			{
				isDrag = false;
			}
		}
		else
		{
			//マウス左クリックが画像内で押されているか
			if (mouse->TriggerMouseLeft() && minPos < mouse->GetMousePos() && mouse->GetMousePos() < maxPos)
			{
				isDrag = true;
			}
		}
#pragma endregion

#pragma region スコア加算

		if (mouseImg->GetPosition() <= maxPos && mouseImg->GetPosition() + mouseImg->GetSize() >= minPos)
		{
			DebugText::GetInstance()->Print(10.0f, 40.0f, 2.0f, "hit");
		}

#pragma endregion
	}




	// マウスの相対座標を表示
	DebugText::GetInstance()->Print(10.0f, 10.0f, 2.0f, "(%d, %d)", (int)mouse->GetMousePos().x, (int)mouse->GetMousePos().y);
}

void GameScene::Draw()
{
	//SetImgui();

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

	for (Image2d*& image : imageList)
	{
		image->Draw();
	}

	mouseImg->Draw();
	if (mouse->PushMouseLeft())
	{
		mouseLeftImg->Draw();
	}
	if (mouse->PushMouseRight())
	{
		mouseRightImg->Draw();
	}
	// フェードの描画
	FadeScene::GetInstance()->Draw();

	// デバッグテキストの描画
	DebugText::GetInstance()->DrawAll(DirectXCommon::GetInstance()->GetCommandList());
	// 画像描画後処理
	Image2d::PostDraw();
#pragma endregion 前景画像描画
}