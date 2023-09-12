#include "FadeScene.h"

bool FadeScene::fadeInEnd = false;
bool FadeScene::fadeOutEnd = false;

FadeScene::FadeScene()
{
	door_left = Image2d::Create(Image2d::ImgNumber::door_left, { 0.0f,0.0f });
	door_left->SetPosition(door_left_open_pos);
	door_left->SetSize({ 960.0f ,1080.0f });
	door_left->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });

	door_right = Image2d::Create(Image2d::ImgNumber::door_right, { 0.0f,0.0f });
	door_right->SetPosition(door_right_open_pos);
	door_right->SetSize({ 960.0f ,1080.0f });
	door_right->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
}

FadeScene::~FadeScene()
{
	safe_delete(door_right);
	safe_delete(door_left);
}

FadeScene* FadeScene::GetInstance()
{
	static FadeScene instance;

	return &instance;
}

void FadeScene::Update()
{
	switch (fadeState)
	{
	case None:
		fadeInEnd = false;
		fadeOutEnd = false;
		alphaAdd = 0.0f;
		break;
	case FadeInPlay:
		if (!fadeInEnd && alpha <= 3.0f)
		{
			alpha += alphaAdd;

			if (alpha < 1.0f)
			{
				door_left->SetPosition(Easing::easeIn(door_left_open_pos, door_left_close_pos, alpha));
				door_right->SetPosition(Easing::easeIn(door_right_open_pos, door_right_close_pos, alpha));
			}
		}
		else
		{
			fadeState = FadeInEnd;
		}
		break;
	case FadeInEnd:
		fadeInEnd = true;
		fadeCount = 0;
		break;
	case FadeOutPlay:
		if (!fadeOutEnd && alpha > 0.0f)
		{
			alpha -= alphaAdd;

			door_left->SetPosition(Easing::easeOut(door_left_open_pos, door_left_close_pos, alpha));
			door_right->SetPosition(Easing::easeOut(door_right_open_pos, door_right_close_pos, alpha));
		}
		else
		{
			fadeState = FadeOutEnd;
		}
		break;
	case FadeOutEnd:
		fadeOutEnd = true;
		fadeCount = 0;
		break;
	default:
		break;
	}
}

void FadeScene::Draw()
{
	door_left->Draw();
	door_right->Draw();
}

void FadeScene::reset()
{
	fadeState = None;
}

void FadeScene::FadeIn(float alpha)
{
	if (fadeState != FadeInPlay && fadeState != FadeInEnd)
	{
		this->alpha = alpha;
		alphaAdd = 0.02f;
		fadeInEnd = false;
		Audio::GetInstance()->PlayWave("Resources/SE/scene_change.wav", 0, 0.1f);
		// フェードイン開始
		fadeState = FadeInPlay;
	}
}

void FadeScene::FadeOut(float alpha)
{
	if (fadeState != FadeOutPlay && fadeState != FadeOutEnd)
	{
		this->alpha = alpha;
		alphaAdd = 0.02f;
		fadeOutEnd = false;
		// フェードアウト開始
		fadeState = FadeOutPlay;
	}
}
