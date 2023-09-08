#include "SceneFactory.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameClearScene.h"

BaseScene* SceneFactory::CreateScene(const std::string& sceneName)
{
	// Ÿ‚ÌƒV[ƒ“‚ğ¶¬
	BaseScene* newScene = nullptr;

	if (sceneName == "Title")
	{
		newScene = new TitleScene();
	}
	else if (sceneName == "Game")
	{
		newScene = new GameScene();
	}
	else if (sceneName == "GameClear")
	{
		newScene = new GameClearScene();
	}

	return newScene;
}
