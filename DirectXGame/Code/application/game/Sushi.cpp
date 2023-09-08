#include "Sushi.h"

Sushi::Sushi()
{
	// シャリと寿司下駄
	shari = Image2d::Create(Image2d::ImgNumber::shari, { 0.0f, 0.0f });
	shari->SetPosition({ 100.0f, 500.0f });
	shari->SetSize(shari->GetDataSize());
	shari->SetNumber(Image2d::ImgNumber::shari);
	sushi_geta = Image2d::Create(Image2d::ImgNumber::sushi_geta, { 0.0f, 0.0f });
	sushi_geta->SetPosition({ 520.0f, 80.0f });
	sushi_geta->SetSize({ 240.0f, 240.0f });
	sushi_geta->SetNumber(Image2d::ImgNumber::sushi_geta);

	// 寿司(ネタ)
	maguro_neta = Image2d::Create(Image2d::ImgNumber::maguro_neta, { 0.0f, 0.0f });
	maguro_neta->SetPosition({ 500.0f, 500.0f });
	maguro_neta->SetSize(maguro_neta->GetDataSize());
	maguro_neta->SetNumber(Image2d::ImgNumber::maguro_neta);
	sushiList.push_back(maguro_neta);
	samon_neta = Image2d::Create(Image2d::ImgNumber::samon_neta, { 0.0f, 0.0f });
	samon_neta->SetPosition({ 500.0f, 500.0f });
	samon_neta->SetSize(samon_neta->GetDataSize());
	samon_neta->SetNumber(Image2d::ImgNumber::samon_neta);
	sushiList.push_back(samon_neta);
	ebi_neta = Image2d::Create(Image2d::ImgNumber::ebi_neta, { 0.0f, 0.0f });
	ebi_neta->SetPosition({ 500.0f, 500.0f });
	ebi_neta->SetSize(ebi_neta->GetDataSize());
	ebi_neta->SetNumber(Image2d::ImgNumber::ebi_neta);
	sushiList.push_back(ebi_neta);
	tamago_neta = Image2d::Create(Image2d::ImgNumber::tamago_neta, { 0.0f, 0.0f });
	tamago_neta->SetPosition({ 500.0f, 500.0f });
	tamago_neta->SetSize(tamago_neta->GetDataSize());
	tamago_neta->SetNumber(Image2d::ImgNumber::tamago_neta);
	sushiList.push_back(tamago_neta);
	ika_neta = Image2d::Create(Image2d::ImgNumber::ika_neta, { 0.0f, 0.0f });
	ika_neta->SetPosition({ 500.0f, 500.0f });
	ika_neta->SetSize(ika_neta->GetDataSize());
	ika_neta->SetNumber(Image2d::ImgNumber::ika_neta);
	sushiList.push_back(ika_neta);

	// 寿司(完成)
	maguro = Image2d::Create(Image2d::ImgNumber::maguro, { 0.0f, 0.0f });
	maguro->SetPosition({ 300.0f, 500.0f });
	maguro->SetSize(maguro->GetDataSize());
	maguro->SetNumber(Image2d::ImgNumber::maguro);
	sushiList.push_back(maguro);
	samon = Image2d::Create(Image2d::ImgNumber::samon, { 0.0f, 0.0f });
	samon->SetPosition({ 300.0f, 500.0f });
	samon->SetSize(samon->GetDataSize());
	samon->SetNumber(Image2d::ImgNumber::samon);
	sushiList.push_back(samon);
	ebi = Image2d::Create(Image2d::ImgNumber::ebi, { 0.0f, 0.0f });
	ebi->SetPosition({ 300.0f, 500.0f });
	ebi->SetSize(ebi->GetDataSize());
	ebi->SetNumber(Image2d::ImgNumber::ebi);
	sushiList.push_back(ebi);
	tamago = Image2d::Create(Image2d::ImgNumber::tamago, { 0.0f, 0.0f });
	tamago->SetPosition({ 300.0f, 500.0f });
	tamago->SetSize(tamago->GetDataSize());
	tamago->SetNumber(Image2d::ImgNumber::tamago);
	sushiList.push_back(tamago);
	ika = Image2d::Create(Image2d::ImgNumber::ika, { 0.0f, 0.0f });
	ika->SetPosition({ 300.0f, 500.0f });
	ika->SetSize(ika->GetDataSize());
	ika->SetNumber(Image2d::ImgNumber::ika);
	sushiList.push_back(ika);
}

Sushi::~Sushi()
{
	safe_delete(shari);
	safe_delete(sushi_geta);
}

Sushi* Sushi::GetInstance()
{
	static Sushi instance;
	return &instance;
}

void Sushi::Update()
{
	for (int i = 0; i < sushiList.size(); i++)
	{
		// 画像の最小と最大
		XMFLOAT2 minPos = sushiList[i]->GetCenterPosition() - sushiList[i]->GetSize() / 2;
		XMFLOAT2 maxPos = sushiList[i]->GetCenterPosition() + sushiList[i]->GetSize() / 2;
		isDrag = sushiList[i]->GetIsDrag();
		imgNumber = sushiList[i]->GetNumber();

#pragma region ドラッグアンドドロップ
		// 画像がドラッグ状態なら
		if (isDrag)
		{
			// 画像の中心をマウス座標にする
			sushiList[i]->SetCenterPos(mouse->GetMousePos(), sushiList[i]->GetSize());

			// ドラッグした状態で離したら
			if (mouse->ReleaseMouseLeft())
			{
				sushiList[i]->SetIsDrag(false);
				isDragNow = false;
				dragNum = 0;
			}
		}
		else if(!isDragNow)
		{
			//マウス左クリックが画像内で押されているか
			if (mouse->TriggerMouseLeft() && minPos < mouse->GetMousePos() && mouse->GetMousePos() < maxPos)
			{
				sushiList[i]->SetIsDrag(true);
				isDragNow = true;
				dragNum = i;
			}
		}
#pragma endregion

#pragma region シャリにわさびをつける

#pragma endregion

#pragma region シャリとネタを組み合わせる

		if (shari->GetPosition() <= maxPos && shari->GetPosition() + shari->GetSize() >= minPos &&
			imgNumber >= Image2d::ImgNumber::maguro_neta)
		{
			DebugText::GetInstance()->Print(10.0f, 40.0f, 2.0f, "hit");
		}

#pragma endregion

#pragma region 寿司を寿司下駄にのせる

		if (sushi_geta->GetPosition() <= maxPos && sushi_geta->GetPosition() + sushi_geta->GetSize() >= minPos &&
			imgNumber >= Image2d::ImgNumber::maguro && imgNumber < Image2d::ImgNumber::maguro_neta)
		{
			DebugText::GetInstance()->Print(10.0f, 40.0f, 2.0f, "hit");
		}

#pragma endregion
	}

	// マウスの相対座標を表示
	DebugText::GetInstance()->Print(10.0f, 10.0f, 2.0f, "(%d, %d)", (int)mouse->GetMousePos().x, (int)mouse->GetMousePos().y);
}

void Sushi::Draw()
{
	sushi_geta->Draw();
	shari->Draw();

	// 描画はリストの後ろから
	for (int i = (int)sushiList.size() - 1; i >= 0; --i)
	{
		sushiList[i]->Draw();
	}

	// ドラッグしている寿司を最前面にする
	sushiList[dragNum]->Draw();
}
