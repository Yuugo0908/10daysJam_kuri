#include "MyGame.h"
#include "SceneFactory.h"

void MyGame::Initialize()
{
	//基底クラスの初期化
	Framework::Initialize();

	// タイトル画像読み込み
	if (!Image2d::LoadTexture(Image2d::ImgNumber::titleNum, "title"))
	{
		assert(0);
	}
	// 背景画像読み込み
	if (!Image2d::LoadTexture(Image2d::ImgNumber::backNum, "backGround"))
	{
		assert(0);
	}
	// ゲームクリア画像読み込み
	if (!Image2d::LoadTexture(Image2d::ImgNumber::GameClearNum, "GameClear"))
	{
		assert(0);
	}
	// ゲームオーバー画像読み込み
	if (!Image2d::LoadTexture(Image2d::ImgNumber::GameOverNum, "GameOver"))
	{
		assert(0);
	}
	// チュートリアル用画像の読み込み
	if (!Image2d::LoadTexture(Image2d::ImgNumber::mouseNum, "mouse"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::mouseLeftNum, "mouse_left"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::mouseRightNum, "mouse_right"))
	{
		assert(0);
	}
	// 寿司画像の読み込み
	if (!Image2d::LoadTexture(Image2d::ImgNumber::shari, "shari"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::sushi_geta, "sushi_geta"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::maguro, "maguro"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::maguro_neta, "maguro_neta"))
	{
		assert(0);
	}

	// フェードの初期化
	FadeScene::GetInstance()->Initialize();

	// シーンファクトリーを生成し、マネージャーにセット
	sceneFactory_ = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory_);

	SceneManager::GetInstance()->ChangeScene("Game");
}

void MyGame::Finalize()
{
	// 基底クラスの終了
	Framework::Finalize();
}

void MyGame::Update()
{
	//基底クラスのアップデート
	Framework::Update();
}

void MyGame::Draw()
{
	//基底クラスのアップデート
	Framework::Draw();
}
