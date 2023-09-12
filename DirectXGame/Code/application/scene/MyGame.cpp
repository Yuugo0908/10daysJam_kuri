#include "MyGame.h"
#include "SceneFactory.h"

void MyGame::Initialize()
{
	//基底クラスの初期化
	Framework::Initialize();

	// タイトル画像読み込み
	if (!Image2d::LoadTexture(Image2d::ImgNumber::title, "title"))
	{
		assert(0);
	}
	// 背景画像読み込み
	if (!Image2d::LoadTexture(Image2d::ImgNumber::back_1, "backGround_1"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::back_2, "backGround_2"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::people, "people"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::hukidasi, "hukidasi"))
	{
		assert(0);
	}
	// リザルト画像読み込み
	if (!Image2d::LoadTexture(Image2d::ImgNumber::result, "result"))
	{
		assert(0);
	}
	// インサート画像読み込み
	if (!Image2d::LoadTexture(Image2d::ImgNumber::door_right, "door_right"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::door_left, "door_left"))
	{
		assert(0);
	}
	// チュートリアル用画像の読み込み
	if (!Image2d::LoadTexture(Image2d::ImgNumber::mouse, "mouse"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::mouseLeft, "mouse_left"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::mouseRight, "mouse_right"))
	{
		assert(0);
	}
	// 寿司画像の読み込み
	if (!Image2d::LoadTexture(Image2d::ImgNumber::kome_oke, "kome_oke"))
	{
		assert(0);
	}
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
	if (!Image2d::LoadTexture(Image2d::ImgNumber::samon, "samon"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::ebi, "ebi"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::tamago, "tamago"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::ika, "ika"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::maguro_neta, "maguro_neta"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::samon_neta, "samon_neta"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::ebi_neta, "ebi_neta"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::tamago_neta, "tamago_neta"))
	{
		assert(0);
	}
	if (!Image2d::LoadTexture(Image2d::ImgNumber::ika_neta, "ika_neta"))
	{
		assert(0);
	}

	// シーンファクトリーを生成し、マネージャーにセット
	sceneFactory_ = new SceneFactory();
	SceneManager::GetInstance()->SetSceneFactory(sceneFactory_);
	SceneManager::GetInstance()->ChangeScene("Title");

	//現在時刻をマイクロ秒で取得
	currentTimeMicro = []()
	{
		std::chrono::system_clock::duration d = std::chrono::system_clock::now().time_since_epoch();
		return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
	};
	//60fpsで動作させる
	fps = 60;

	//現在時刻を取得
	end = currentTimeMicro();

	//次の更新時間を計算
	next = end + (1000 * 1000 / fps);
}

void MyGame::Finalize()
{
	// 基底クラスの終了
	Framework::Finalize();
}

void MyGame::Update()
{
	//できるだけ60fpsになるようにスレッド待機
	end = currentTimeMicro();
	if (end < next)
	{
		//更新時間まで待機
		std::this_thread::sleep_for(std::chrono::microseconds(next - end));
		//次の更新時間を計算（1秒/フレームレート加算）
		next += (1000 * 1000 / fps);
	}
	else
	{
		//更新時間を過ぎた場合は現在時刻から次の更新時間を計算
		next = end + (1000 * 1000 / fps);
	}

	//基底クラスのアップデート
	Framework::Update();
}

void MyGame::Draw()
{
	//基底クラスのアップデート
	Framework::Draw();
}
