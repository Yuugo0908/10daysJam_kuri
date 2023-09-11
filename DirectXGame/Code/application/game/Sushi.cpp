#include "Sushi.h"

Sushi::Sushi()
{
	// ネタ表示用
	maguro_neta_dis = Image2d::Create(Image2d::ImgNumber::maguro_neta, { 0.0f, 0.0f });
	maguro_neta_dis->SetPosition(maguro_neta_position);
	maguro_neta_dis->SetSize(maguro_neta_dis->GetDataSize());
	maguro_neta_dis->SetNumber(Image2d::ImgNumber::maguro_neta);
	samon_neta_dis = Image2d::Create(Image2d::ImgNumber::samon_neta, { 0.0f, 0.0f });
	samon_neta_dis->SetPosition(samon_neta_position);
	samon_neta_dis->SetSize(samon_neta_dis->GetDataSize());
	samon_neta_dis->SetNumber(Image2d::ImgNumber::samon_neta);
	ebi_neta_dis = Image2d::Create(Image2d::ImgNumber::ebi_neta, { 0.0f, 0.0f });
	ebi_neta_dis->SetPosition(ebi_neta_position);
	ebi_neta_dis->SetSize(ebi_neta_dis->GetDataSize());
	ebi_neta_dis->SetNumber(Image2d::ImgNumber::ebi_neta);
	tamago_neta_dis = Image2d::Create(Image2d::ImgNumber::tamago_neta, { 0.0f, 0.0f });
	tamago_neta_dis->SetPosition(tamago_neta_position);
	tamago_neta_dis->SetSize(tamago_neta_dis->GetDataSize());
	tamago_neta_dis->SetNumber(Image2d::ImgNumber::tamago_neta);
	ika_neta_dis = Image2d::Create(Image2d::ImgNumber::ika_neta, { 0.0f, 0.0f });
	ika_neta_dis->SetPosition(ika_neta_position);
	ika_neta_dis->SetSize(ika_neta_dis->GetDataSize());
	ika_neta_dis->SetNumber(Image2d::ImgNumber::ika_neta);

	// 米桶
	kome_oke = Image2d::Create(Image2d::ImgNumber::kome_oke, { 0.0f, 0.0f });
	kome_oke->SetPosition(kome_oke_position);
	kome_oke->SetSize(kome_oke->GetDataSize());
	kome_oke->SetNumber(Image2d::ImgNumber::kome_oke);

	// 寿司下駄
	sushi_geta_1 = Image2d::Create(Image2d::ImgNumber::sushi_geta, { 0.0f, 0.0f });
	sushi_geta_1->SetPosition(geta_1_pos);
	sushi_geta_1->SetSize(sushi_geta_1->GetDataSize());
	sushi_geta_1->SetNumber(Image2d::ImgNumber::sushi_geta);
	sushi_geta_2 = Image2d::Create(Image2d::ImgNumber::sushi_geta, { 0.0f, 0.0f });
	sushi_geta_2->SetPosition(geta_2_pos);
	sushi_geta_2->SetSize(sushi_geta_2->GetDataSize());
	sushi_geta_2->SetNumber(Image2d::ImgNumber::sushi_geta);
	sushi_geta_3 = Image2d::Create(Image2d::ImgNumber::sushi_geta, { 0.0f, 0.0f });
	sushi_geta_3->SetPosition(geta_3_pos);
	sushi_geta_3->SetSize(sushi_geta_3->GetDataSize());
	sushi_geta_3->SetNumber(Image2d::ImgNumber::sushi_geta);
	sushi_getas.push_back(sushi_geta_1);
	sushi_getas.push_back(sushi_geta_2);
	sushi_getas.push_back(sushi_geta_3);
}

Sushi::~Sushi()
{
	safe_delete(shari);
}

Sushi* Sushi::GetInstance()
{
	static Sushi instance;
	return &instance;
}

void Sushi::Update()
{
	// ネタ、シャリ生成
	MakeNeta();
	// 寿司生成
	MakeSushi();
	// 寿司下駄に置く
	PutSushi();
	// ドラッグアンドドロップ
	DragDrop();
}

void Sushi::Draw()
{
	maguro_neta_dis->Draw();
	samon_neta_dis->Draw();
	ebi_neta_dis->Draw();
	tamago_neta_dis->Draw();
	ika_neta_dis->Draw();

	kome_oke->Draw();

	for (int i = 0; i < sushi_getas.size(); i++)
	{
		sushi_getas[i]->Draw();
	}

	// 描画はリストの後ろから
	for (int j = (int)shari_list.size() - 1; j >= 0; --j)
	{
		shari_list[j]->Draw();
	}

	for (int i = (int)sushi_list.size() - 1; i >= 0; --i)
	{
		sushi_list[i]->Draw();
	}

	for (int i = 0; i < geta_1_sushi_list.size(); i++)
	{
		geta_1_sushi_list[i]->Draw();
	}
	for (int i = 0; i < geta_2_sushi_list.size(); i++)
	{
		geta_2_sushi_list[i]->Draw();
	}
	for (int i = 0; i < geta_3_sushi_list.size(); i++)
	{
		geta_3_sushi_list[i]->Draw();
	}

	if ((int)sushi_list.size() != 0)
	{
		// ドラッグしている寿司を最前面にする
		sushi_list[dragNum]->Draw();
	}
}

void Sushi::DragDrop()
{
#pragma region ドラッグアンドドロップ
	for (int i = 0; i < sushi_list.size(); i++)
	{
		// 画像の最小と最大
		XMFLOAT2 maxPos = sushi_list[i]->GetCenterPosition() + sushi_list[i]->GetSize() / 2;
		XMFLOAT2 minPos = sushi_list[i]->GetCenterPosition() - sushi_list[i]->GetSize() / 2;
		isDrag = sushi_list[i]->GetIsDrag();

		// 画像がドラッグ状態なら
		if (isDrag)
		{
			// 画像の中心をマウス座標にする
			sushi_list[i]->SetCenterPos(mouse->GetMousePos(), sushi_list[i]->GetSize());

			// ドラッグした状態で離したら
			if (mouse->ReleaseMouseLeft())
			{
				// ドラッグ状態の解除
				sushi_list[i]->SetIsDrag(false);
				// ネタの画像番号を取得
				netaNumber = sushi_list[i]->GetNumber();
				// 寿司の画像番号を取得
				sushiNumber = sushi_list[i]->GetNumber();
				// 現時点ではドラッグしていない
				isDragNow = false;

				if (dragData != nullptr)
				{
					drag_maxPos = dragData->GetCenterPosition() + dragData->GetSize() / 2;
					drag_minPos = dragData->GetCenterPosition() - dragData->GetSize() / 2;
				}
			}
		}
		else if (!isDragNow)
		{
			//マウス左クリックが画像内で押されているか
			if (mouse->TriggerMouseLeft() && minPos < mouse->GetMousePos() && mouse->GetMousePos() < maxPos)
			{
				sushi_list[i]->SetIsDrag(true);
				isDragNow = true;
				dragNum = i;
				dragData = sushi_list[i];
			}
		}
	}

	for (int i = 0; i < shari_list.size(); i++)
	{		
		// 画像の最小と最大
		XMFLOAT2 maxPos = shari_list[i]->GetCenterPosition() + shari_list[i]->GetSize() / 2;
		XMFLOAT2 minPos = shari_list[i]->GetCenterPosition() - shari_list[i]->GetSize() / 2;
		isDrag = shari_list[i]->GetIsDrag();

		// 画像がドラッグ状態なら
		if (isDrag)
		{
			// 画像の中心をマウス座標にする
			shari_list[i]->SetCenterPos(mouse->GetMousePos(), shari_list[i]->GetSize());

			// ドラッグした状態で離したら
			if (mouse->ReleaseMouseLeft())
			{
				// ドラッグ状態の解除
				shari_list[i]->SetIsDrag(false);
				// 現時点ではドラッグしていない
				isDragNow = false;
			}
		}
		else if (!isDragNow)
		{
			//マウス左クリックが画像内で押されているか
			if (mouse->TriggerMouseLeft() && minPos < mouse->GetMousePos() && mouse->GetMousePos() < maxPos)
			{
				shari_list[i]->SetIsDrag(true);
				isDragNow = true;
			}
		}
	}
#pragma endregion
}

void Sushi::MakeNeta()
{
# pragma region ネタシャリ生成
	// マグロ生成
	if (mouse->TriggerMouseLeft() && 
		maguro_neta_dis->GetCenterPosition() - maguro_neta_dis->GetDataSize() / 2 < mouse->GetMousePos() && 
		mouse->GetMousePos() < maguro_neta_dis->GetCenterPosition() + maguro_neta_dis->GetDataSize() / 2)
	{
		maguro_neta = Image2d::Create(Image2d::ImgNumber::maguro_neta, { 0.0f, 0.0f });
		maguro_neta->SetPosition(maguro_neta_position);
		maguro_neta->SetSize(maguro_neta->GetDataSize());
		maguro_neta->SetNumber(Image2d::ImgNumber::maguro_neta);
		sushi_list.push_back(maguro_neta);
	}
	// サーモン生成
	if (mouse->TriggerMouseLeft() && 
		samon_neta_dis->GetCenterPosition() - samon_neta_dis->GetDataSize() / 2 < mouse->GetMousePos() &&
		mouse->GetMousePos() < samon_neta_dis->GetCenterPosition() + samon_neta_dis->GetDataSize() / 2)
	{
		samon_neta = Image2d::Create(Image2d::ImgNumber::samon_neta, { 0.0f, 0.0f });
		samon_neta->SetPosition(samon_neta_position);
		samon_neta->SetSize(samon_neta->GetDataSize());
		samon_neta->SetNumber(Image2d::ImgNumber::samon_neta);
		sushi_list.push_back(samon_neta);
	}
	// エビ生成
	if (mouse->TriggerMouseLeft() && 
		ebi_neta_dis->GetCenterPosition() - ebi_neta_dis->GetDataSize() / 2 < mouse->GetMousePos() &&
		mouse->GetMousePos() < ebi_neta_dis->GetCenterPosition() + ebi_neta_dis->GetDataSize() / 2)
	{
		ebi_neta = Image2d::Create(Image2d::ImgNumber::ebi_neta, { 0.0f, 0.0f });
		ebi_neta->SetPosition(ebi_neta_position);
		ebi_neta->SetSize(ebi_neta->GetDataSize());
		ebi_neta->SetNumber(Image2d::ImgNumber::ebi_neta);
		sushi_list.push_back(ebi_neta);
	}
	// タマゴ生成
	if (mouse->TriggerMouseLeft() && 
		tamago_neta_dis->GetCenterPosition() - tamago_neta_dis->GetDataSize() / 2 < mouse->GetMousePos() &&
		mouse->GetMousePos() < tamago_neta_dis->GetCenterPosition() + tamago_neta_dis->GetDataSize() / 2)
	{
		tamago_neta = Image2d::Create(Image2d::ImgNumber::tamago_neta, { 0.0f, 0.0f });
		tamago_neta->SetPosition(tamago_neta_position);
		tamago_neta->SetSize(tamago_neta->GetDataSize());
		tamago_neta->SetNumber(Image2d::ImgNumber::tamago_neta);
		sushi_list.push_back(tamago_neta);
	}
	// イカ生成
	if (mouse->TriggerMouseLeft() && 
		ika_neta_dis->GetCenterPosition() - ika_neta_dis->GetDataSize() / 2 < mouse->GetMousePos() &&
		mouse->GetMousePos() < ika_neta_dis->GetCenterPosition() + ika_neta_dis->GetDataSize() / 2)
	{
		ika_neta = Image2d::Create(Image2d::ImgNumber::ika_neta, { 0.0f, 0.0f });
		ika_neta->SetPosition(ika_neta_position);
		ika_neta->SetSize(ika_neta->GetDataSize());
		ika_neta->SetNumber(Image2d::ImgNumber::ika_neta);
		sushi_list.push_back(ika_neta);
	}

	// シャリ生成
	if (mouse->TriggerMouseLeft() &&
		kome_oke->GetCenterPosition() - kome_oke->GetDataSize() / 2 < mouse->GetMousePos() &&
		mouse->GetMousePos() < kome_oke->GetCenterPosition() + kome_oke->GetDataSize() / 2)
	{
		shari = Image2d::Create(Image2d::ImgNumber::shari, { 0.0f, 0.0f });
		shari->SetPosition(mouse->GetMousePos() - shari->GetDataSize() / 2);
		shari->SetSize(shari->GetDataSize());
		shari->SetNumber(Image2d::ImgNumber::shari);
		shariNumber = shari->GetNumber();
		shari_list.push_back(shari);
	}
#pragma endregion
}

void Sushi::MakeSushi()
{
#pragma region シャリとネタを組み合わせる
	for (int j = 0; j < shari_list.size(); j++)
	{
		if (isDragNow == false && shari_list[j]->GetPosition() < drag_maxPos && shari_list[j]->GetPosition() + shari_list[j]->GetSize() > drag_minPos)
		{
			if (netaNumber == Image2d::ImgNumber::maguro_neta)
			{
				shari_list.erase(shari_list.begin() + j);
				maguro = Image2d::Create(Image2d::ImgNumber::maguro, { 0.0f, 0.0f });
				maguro->SetPosition(mouse->GetMousePos() - maguro->GetDataSize() / 2);
				maguro->SetSize(maguro->GetDataSize());
				maguro->SetNumber(Image2d::ImgNumber::maguro);
				sushi_list.push_back(maguro);
				drag_maxPos = {};
				drag_minPos = {};
				isCombine = true;
			}
			else if (netaNumber == Image2d::ImgNumber::samon_neta)
			{
				shari_list.erase(shari_list.begin() + j);
				samon = Image2d::Create(Image2d::ImgNumber::samon, { 0.0f, 0.0f });
				samon->SetPosition(mouse->GetMousePos() - samon->GetDataSize() / 2);
				samon->SetSize(samon->GetDataSize());
				samon->SetNumber(Image2d::ImgNumber::samon);
				sushi_list.push_back(samon);
				drag_maxPos = {};
				drag_minPos = {};
				isCombine = true;
			}
			else if (netaNumber == Image2d::ImgNumber::ebi_neta)
			{
				shari_list.erase(shari_list.begin() + j);
				ebi = Image2d::Create(Image2d::ImgNumber::ebi, { 0.0f, 0.0f });
				ebi->SetPosition(mouse->GetMousePos() - ebi->GetDataSize() / 2);
				ebi->SetSize(ebi->GetDataSize());
				ebi->SetNumber(Image2d::ImgNumber::ebi);
				sushi_list.push_back(ebi);
				drag_maxPos = {};
				drag_minPos = {};
				isCombine = true;
			}
			else if (netaNumber == Image2d::ImgNumber::tamago_neta)
			{
				shari_list.erase(shari_list.begin() + j);
				tamago = Image2d::Create(Image2d::ImgNumber::tamago, { 0.0f, 0.0f });
				tamago->SetPosition(mouse->GetMousePos() - tamago->GetDataSize() / 2);
				tamago->SetSize(tamago->GetDataSize());
				tamago->SetNumber(Image2d::ImgNumber::tamago);
				sushi_list.push_back(tamago);
				drag_maxPos = {};
				drag_minPos = {};
				isCombine = true;
			}
			else if (netaNumber == Image2d::ImgNumber::ika_neta)
			{
				shari_list.erase(shari_list.begin() + j);
				ika = Image2d::Create(Image2d::ImgNumber::ika, { 0.0f, 0.0f });
				ika->SetPosition(mouse->GetMousePos() - ika->GetDataSize() / 2);
				ika->SetSize(ika->GetDataSize());
				ika->SetNumber(Image2d::ImgNumber::ika);
				sushi_list.push_back(ika);
				drag_maxPos = {};
				drag_minPos = {};
				isCombine = true;
			}

			if (isCombine)
			{
				isCombine = false;
				sushi_list.erase(sushi_list.begin() + dragNum);
				dragNum = 0;
			}
		}
	}
	if (isDragNow == false)
	{
		netaNumber = 0;
	}
#pragma endregion
}

void Sushi::PutSushi()
{
#pragma region 寿司を寿司下駄にのせる
	for (int j = 0; j < sushi_getas.size(); j++)
	{
		if (isDragNow == false && sushi_getas[j]->GetPosition() < drag_maxPos && sushi_getas[j]->GetPosition() + sushi_getas[j]->GetSize() > drag_minPos)
		{
			if (sushiNumber == Image2d::ImgNumber::maguro)
			{
				drag_maxPos = {};
				drag_minPos = {};
				isPut = true;
				if (j == 0)
				{
					geta_1_number[geta_1_pieces] = Image2d::ImgNumber::maguro;
					geta_1_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_1_sushi_list[geta_1_pieces]->SetPosition({ geta_1_pos.x + 150 * geta_1_pieces, geta_1_pos.y });
				}
				else if (j == 1)
				{
					geta_2_number[geta_2_pieces] = Image2d::ImgNumber::maguro;
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_2_sushi_list[geta_2_pieces]->SetPosition({ geta_2_pos.x + 150 * geta_2_pieces, geta_2_pos.y });
				}
				else if (j == 2)
				{
					geta_3_number[geta_3_pieces] = Image2d::ImgNumber::maguro;
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_3_sushi_list[geta_3_pieces]->SetPosition({ geta_3_pos.x + 150 * geta_3_pieces, geta_3_pos.y });
				}
			}
			else if (sushiNumber == Image2d::ImgNumber::samon)
			{
				drag_maxPos = {};
				drag_minPos = {};
				isPut = true;
				if (j == 0)
				{
					geta_1_number[geta_1_pieces] = Image2d::ImgNumber::samon;
					geta_1_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_1_sushi_list[geta_1_pieces]->SetPosition({ geta_1_pos.x + 150 * geta_1_pieces, geta_1_pos.y });
				}
				else if (j == 1)
				{
					geta_2_number[geta_2_pieces] = Image2d::ImgNumber::samon;
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_2_sushi_list[geta_2_pieces]->SetPosition({ geta_2_pos.x + 150 * geta_2_pieces, geta_2_pos.y });
				}
				else if (j == 2)
				{
					geta_3_number[geta_3_pieces] = Image2d::ImgNumber::samon;
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_3_sushi_list[geta_3_pieces]->SetPosition({ geta_3_pos.x + 150 * geta_3_pieces, geta_3_pos.y });
				}
			}
			else if (sushiNumber == Image2d::ImgNumber::ebi)
			{
				drag_maxPos = {};
				drag_minPos = {};
				isPut = true;
				if (j == 0)
				{
					geta_1_number[geta_1_pieces] = Image2d::ImgNumber::ebi;
					geta_1_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_1_sushi_list[geta_1_pieces]->SetPosition({ geta_1_pos.x + 150 * geta_1_pieces, geta_1_pos.y });
				}
				else if (j == 1)
				{
					geta_2_number[geta_2_pieces] = Image2d::ImgNumber::ebi;
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_2_sushi_list[geta_2_pieces]->SetPosition({ geta_2_pos.x + 150 * geta_2_pieces, geta_2_pos.y });
				}
				else if (j == 2)
				{
					geta_3_number[geta_3_pieces] = Image2d::ImgNumber::ebi;
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_3_sushi_list[geta_3_pieces]->SetPosition({ geta_3_pos.x + 150 * geta_3_pieces, geta_3_pos.y });
				}
			}
			else if (sushiNumber == Image2d::ImgNumber::tamago)
			{
				drag_maxPos = {};
				drag_minPos = {};
				isPut = true;
				if (j == 0)
				{
					geta_1_number[geta_1_pieces] = Image2d::ImgNumber::tamago;
					geta_1_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_1_sushi_list[geta_1_pieces]->SetPosition({ geta_1_pos.x + 150 * geta_1_pieces, geta_1_pos.y });
				}
				else if (j == 1)
				{
					geta_2_number[geta_2_pieces] = Image2d::ImgNumber::tamago;
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_2_sushi_list[geta_2_pieces]->SetPosition({ geta_2_pos.x + 150 * geta_2_pieces, geta_2_pos.y });
				}
				else if (j == 2)
				{
					geta_3_number[geta_3_pieces] = Image2d::ImgNumber::tamago;
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_3_sushi_list[geta_3_pieces]->SetPosition({ geta_3_pos.x + 150 * geta_3_pieces, geta_3_pos.y });
				}
			}
			else if (sushiNumber == Image2d::ImgNumber::ika)
			{
				drag_maxPos = {};
				drag_minPos = {};
				isPut = true;
				if (j == 0)
				{
					geta_1_number[geta_1_pieces] = Image2d::ImgNumber::ika;
					geta_1_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_1_sushi_list[geta_1_pieces]->SetPosition({ geta_1_pos.x + 150 * geta_1_pieces, geta_1_pos.y });
				}
				else if (j == 1)
				{
					geta_2_number[geta_2_pieces] = Image2d::ImgNumber::ika;
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_2_sushi_list[geta_2_pieces]->SetPosition({ geta_2_pos.x + 150 * geta_2_pieces, geta_2_pos.y });
				}
				else if (j == 2)
				{
					geta_3_number[geta_3_pieces] = Image2d::ImgNumber::ika;
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_3_sushi_list[geta_3_pieces]->SetPosition({ geta_3_pos.x + 150 * geta_3_pieces, geta_3_pos.y });
				}
			}

			if (isPut)
			{
				if (j == 0)
				{
					geta_1_pieces++;
				}
				else if (j == 1)
				{
					geta_2_pieces++;
				}
				else if (j == 2)
				{
					geta_3_pieces++;
				}
			}
		}
	}
	if (isDragNow == false)
	{
		sushiNumber = 0;
	}

	//TODO 正誤判定はここで行うと良い
	if (geta_1_pieces >= 3)
	{
		geta_1_pieces = 0;
		geta_1_sushi_list.clear();
	}
	if (geta_2_pieces >= 3)
	{
		geta_2_pieces = 0;
		geta_2_sushi_list.clear();
	}
	if (geta_3_pieces >= 3)
	{
		geta_3_pieces = 0;
		geta_3_sushi_list.clear();
	}
#pragma endregion
}

void Sushi::Pattern()
{
}

void Sushi::SetGeta()
{
}
