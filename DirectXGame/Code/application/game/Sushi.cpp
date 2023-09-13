#include "Sushi.h"

int Sushi::score = 0;

Sushi::Sushi()
{

}

Sushi::~Sushi()
{

}

Sushi* Sushi::GetInstance()
{
	static Sushi instance;
	return &instance;
}

void Sushi::Initialize()
{
	// ネタ表示用
	maguro_neta_dis = Image2d::Create(Image2d::ImgNumber::maguro_neta, { 0.0f, 0.0f });
	maguro_neta_dis->SetPosition(maguro_neta_position);
	maguro_neta_dis->SetSize(maguro_neta_dis->GetDataSize());
	samon_neta_dis = Image2d::Create(Image2d::ImgNumber::samon_neta, { 0.0f, 0.0f });
	samon_neta_dis->SetPosition(samon_neta_position);
	samon_neta_dis->SetSize(samon_neta_dis->GetDataSize());
	ebi_neta_dis = Image2d::Create(Image2d::ImgNumber::ebi_neta, { 0.0f, 0.0f });
	ebi_neta_dis->SetPosition(ebi_neta_position);
	ebi_neta_dis->SetSize(ebi_neta_dis->GetDataSize());
	tamago_neta_dis = Image2d::Create(Image2d::ImgNumber::tamago_neta, { 0.0f, 0.0f });
	tamago_neta_dis->SetPosition(tamago_neta_position);
	tamago_neta_dis->SetSize(tamago_neta_dis->GetDataSize());
	ika_neta_dis = Image2d::Create(Image2d::ImgNumber::ika_neta, { 0.0f, 0.0f });
	ika_neta_dis->SetPosition(ika_neta_position);
	ika_neta_dis->SetSize(ika_neta_dis->GetDataSize());

	// 米桶
	kome_oke = Image2d::Create(Image2d::ImgNumber::kome_oke, { 0.0f, 0.0f });
	kome_oke->SetPosition(kome_oke_position);
	kome_oke->SetSize(kome_oke->GetDataSize());

	// 寿司下駄
	sushi_geta_1 = Image2d::Create(Image2d::ImgNumber::sushi_geta, { 0.0f, 0.0f });
	sushi_geta_1->SetPosition(geta_1_pos);
	sushi_geta_1->SetSize(sushi_geta_1->GetDataSize());
	sushi_geta_2 = Image2d::Create(Image2d::ImgNumber::sushi_geta, { 0.0f, 0.0f });
	sushi_geta_2->SetPosition(geta_2_pos);
	sushi_geta_2->SetSize(sushi_geta_2->GetDataSize());
	sushi_geta_3 = Image2d::Create(Image2d::ImgNumber::sushi_geta, { 0.0f, 0.0f });
	sushi_geta_3->SetPosition(geta_3_pos);
	sushi_geta_3->SetSize(sushi_geta_3->GetDataSize());
	sushi_getas.push_back(sushi_geta_1);
	sushi_getas.push_back(sushi_geta_2);
	sushi_getas.push_back(sushi_geta_3);

	// タイマー表示
	wait_bar_1 = Image2d::Create(Image2d::ImgNumber::wait_bar, { 760.0f,750.0f });
	wait_bar_1->SetSize(wait_bar_1->GetDataSize());
	wait_bar_2 = Image2d::Create(Image2d::ImgNumber::wait_bar, { 175.0f,750.0f });
	wait_bar_2->SetSize(wait_bar_2->GetDataSize());
	wait_bar_3 = Image2d::Create(Image2d::ImgNumber::wait_bar, { 1345.0f,750.0f });
	wait_bar_3->SetSize(wait_bar_3->GetDataSize());
	wait_gauge_1 = Image2d::Create(Image2d::ImgNumber::wait_gauge, { 835.0f,752.0f });
	wait_gauge_1->SetSize(wait_gauge_1->GetDataSize());
	wait_gauge_2 = Image2d::Create(Image2d::ImgNumber::wait_gauge, { 250.0f,752.0f });
	wait_gauge_2->SetSize(wait_gauge_2->GetDataSize());
	wait_gauge_3 = Image2d::Create(Image2d::ImgNumber::wait_gauge, { 1415.0f,752.0f });
	wait_gauge_3->SetSize(wait_gauge_3->GetDataSize());

	// スコア表示背景
	score_back = Image2d::Create(Image2d::ImgNumber::score_back, { 50.0f, 20.0f });
	score_back->SetSize(score_back->GetDataSize() / 2);

	// スコアリセット
	score = 0;
}

void Sushi::Update()
{
	// 出題パターン生成
	Pattern();
	// ネタ、シャリ生成
	MakeNeta();
	// 寿司生成
	MakeSushi();
	// 寿司下駄に置く
	PutSushi();
	// 正誤判定
	Judge();
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
	score_back->Draw();

	for (int i = 0; i < sushi_getas.size(); i++)
	{
		sushi_getas[i]->Draw();
	}

	if (pattern_1_flag == false)
	{
		wait_bar_1->Draw();
		wait_gauge_1->SetSize({ (float)wait_timer_1 / 4, 51.0f });
		wait_gauge_1->Draw();
	}
	if (pattern_2_flag == false)
	{
		wait_bar_2->Draw();
		wait_gauge_2->SetSize({ (float)wait_timer_2 / 4, 51.0f });
		wait_gauge_2->Draw();
	}
	if (pattern_3_flag == false)
	{
		wait_bar_3->Draw();
		wait_gauge_3->SetSize({ (float)wait_timer_3 / 4, 51.0f });
		wait_gauge_3->Draw();
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

	for (int i = 0; i < pattern_1.size(); i++)
	{
		pattern_1[i]->Draw();
	}
	for (int i = 0; i < pattern_2.size(); i++)
	{
		pattern_2[i]->Draw();
	}
	for (int i = 0; i < pattern_3.size(); i++)
	{
		pattern_3[i]->Draw();
	}

	if ((int)sushi_list.size() != 0 && isDragNow == true)
	{
		// ドラッグしている寿司を最前面にする
		sushi_list[dragNum]->Draw();
	}
}

void Sushi::Finalize()
{
	// 画像
	safe_delete(maguro_neta_dis);
	safe_delete(samon_neta_dis);
	safe_delete(ebi_neta_dis);
	safe_delete(tamago_neta_dis);
	safe_delete(ika_neta_dis);
	safe_delete(kome_oke);
	safe_delete(sushi_geta_1);
	safe_delete(sushi_geta_2);
	safe_delete(sushi_geta_3);

	// 寿司下駄
	sushi_getas.clear();
	// 下駄に乗っている寿司一覧
	geta_1_sushi_list.clear();
	geta_2_sushi_list.clear();
	geta_3_sushi_list.clear();
	// 下駄に乗っている寿司の数
	geta_1_pieces = 0;
	geta_2_pieces = 0;
	geta_3_pieces = 0;
	// 下駄に乗せている寿司の番号
	geta_1_number.clear();
	geta_2_number.clear();
	geta_3_number.clear();
	// 下駄に置いたかのフラグ
	isPut_1 = false;
	isPut_2 = false;
	isPut_3 = false;

	//寿司一覧
	sushi_list.clear();
	isCombine = false;

	// お題用
	pattern_1.clear();
	pattern_2.clear();
	pattern_3.clear();
	// 生成フラグ
	pattern_1_flag = true;
	pattern_2_flag = true;
	pattern_3_flag = true;
	// 生成までのタイマー
	pattern_1_timer = 0;
	pattern_2_timer = 600;
	pattern_3_timer = 1200;
	// 注文が変わるまでのタイマー
	wait_timer_1 = 1200;
	wait_timer_2 = 1200;
	wait_timer_3 = 1200;
	// スコアボーナス
	combo_bonus = 1;
	time_bonus = 0;

	// シャリ
	shari_list.clear();

	// ドラッグしている画像データ取得用
	drag_maxPos = {};
	drag_minPos = {};

	isDrag = false; // 指定の寿司をドラッグしているか
	isDragNow = false; // 何かの寿司をドラッグしているか
	dragNum = 0; // ドラッグしている寿司の番号

	imgNumber = 0; // 画像管理の番号
	shariNumber = 0; // シャリの番号
	netaNumber = 0; // ネタの番号
	sushiNumber = 0; // 寿司の番号
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
			// 寿司下駄にマグロを置く
			if (sushiNumber == Image2d::ImgNumber::maguro)
			{
				drag_maxPos = {};
				drag_minPos = {};
				if (pattern_1_flag == false && j == 0)
				{
					geta_1_number.push_back(Image2d::ImgNumber::maguro);
					geta_1_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_1_sushi_list[geta_1_pieces]->SetPosition({ geta_1_pos.x + 150 * geta_1_pieces, geta_1_pos.y });
				}
				else if (pattern_2_flag == false && j == 1)
				{
					geta_2_number.push_back(Image2d::ImgNumber::maguro);
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_2_sushi_list[geta_2_pieces]->SetPosition({ geta_2_pos.x + 150 * geta_2_pieces, geta_2_pos.y });
				}
				else if (pattern_3_flag == false && j == 2)
				{
					geta_3_number.push_back(Image2d::ImgNumber::maguro);
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_3_sushi_list[geta_3_pieces]->SetPosition({ geta_3_pos.x + 150 * geta_3_pieces, geta_3_pos.y });
				}
			}
			// 寿司下駄にサーモンを置く
			else if (sushiNumber == Image2d::ImgNumber::samon)
			{
				drag_maxPos = {};
				drag_minPos = {};
				if (pattern_1_flag == false && j == 0)
				{
					geta_1_number.push_back(Image2d::ImgNumber::samon);
					geta_1_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_1_sushi_list[geta_1_pieces]->SetPosition({ geta_1_pos.x + 150 * geta_1_pieces, geta_1_pos.y });
				}
				else if (pattern_2_flag == false && j == 1)
				{
					geta_2_number.push_back(Image2d::ImgNumber::samon);
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_2_sushi_list[geta_2_pieces]->SetPosition({ geta_2_pos.x + 150 * geta_2_pieces, geta_2_pos.y });
				}
				else if (pattern_3_flag == false && j == 2)
				{
					geta_3_number.push_back(Image2d::ImgNumber::samon);
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_3_sushi_list[geta_3_pieces]->SetPosition({ geta_3_pos.x + 150 * geta_3_pieces, geta_3_pos.y });
				}
			}
			// 寿司下駄にエビを置く
			else if (sushiNumber == Image2d::ImgNumber::ebi)
			{
				drag_maxPos = {};
				drag_minPos = {};
				if (pattern_1_flag == false && j == 0)
				{
					geta_1_number.push_back(Image2d::ImgNumber::ebi);
					geta_1_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_1_sushi_list[geta_1_pieces]->SetPosition({ geta_1_pos.x + 150 * geta_1_pieces, geta_1_pos.y });
				}
				else if (pattern_2_flag == false && j == 1)
				{
					geta_2_number.push_back(Image2d::ImgNumber::ebi);
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_2_sushi_list[geta_2_pieces]->SetPosition({ geta_2_pos.x + 150 * geta_2_pieces, geta_2_pos.y });
				}
				else if (pattern_3_flag == false && j == 2)
				{
					geta_3_number.push_back(Image2d::ImgNumber::ebi);
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_3_sushi_list[geta_3_pieces]->SetPosition({ geta_3_pos.x + 150 * geta_3_pieces, geta_3_pos.y });
				}
			}
			// 寿司下駄にタマゴを置く
			else if (sushiNumber == Image2d::ImgNumber::tamago)
			{
				drag_maxPos = {};
				drag_minPos = {};
				if (pattern_1_flag == false && j == 0)
				{
					geta_1_number.push_back(Image2d::ImgNumber::tamago);
					geta_1_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_1_sushi_list[geta_1_pieces]->SetPosition({ geta_1_pos.x + 150 * geta_1_pieces, geta_1_pos.y });
				}
				else if (pattern_2_flag == false && j == 1)
				{
					geta_2_number.push_back(Image2d::ImgNumber::tamago);
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_2_sushi_list[geta_2_pieces]->SetPosition({ geta_2_pos.x + 150 * geta_2_pieces, geta_2_pos.y });
				}
				else if (pattern_3_flag == false && j == 2)
				{
					geta_3_number.push_back(Image2d::ImgNumber::tamago);
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_3_sushi_list[geta_3_pieces]->SetPosition({ geta_3_pos.x + 150 * geta_3_pieces, geta_3_pos.y });
				}
			}
			// 寿司下駄にイカを置く
			else if (sushiNumber == Image2d::ImgNumber::ika)
			{
				drag_maxPos = {};
				drag_minPos = {};
				if (pattern_1_flag == false && j == 0)
				{
					geta_1_number.push_back(Image2d::ImgNumber::ika);
					geta_1_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_1_sushi_list[geta_1_pieces]->SetPosition({ geta_1_pos.x + 150 * geta_1_pieces, geta_1_pos.y });
				}
				else if (pattern_2_flag == false && j == 1)
				{
					geta_2_number.push_back(Image2d::ImgNumber::ika);
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_2_sushi_list[geta_2_pieces]->SetPosition({ geta_2_pos.x + 150 * geta_2_pieces, geta_2_pos.y });
				}
				else if (pattern_3_flag == false && j == 2)
				{
					geta_3_number.push_back(Image2d::ImgNumber::ika);
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
					geta_3_sushi_list[geta_3_pieces]->SetPosition({ geta_3_pos.x + 150 * geta_3_pieces, geta_3_pos.y });
				}
			}

			if (pattern_1_flag == false && j == 0)
			{
				isPut_1 = true;
				dragNum = 0;
			}
			if (pattern_2_flag == false && j == 1)
			{
				isPut_2 = true;
				dragNum = 0;
			}
			if (pattern_3_flag == false && j == 2)
			{
				isPut_3 = true;
				dragNum = 0;
			}
		}
	}

	if (isDragNow == false)
	{
		sushiNumber = 0;
	}
#pragma endregion
}

void Sushi::Pattern()
{
#pragma region 出題パターンの生成
	// 次の注文を出す
	if (pattern_1_timer <= 0)
	{
		pattern_1.push_back(Image2d::Create(Random::GetRanNum(Image2d::ImgNumber::maguro, Image2d::ImgNumber::ika), { 760, 400 }));
		pattern_1.push_back(Image2d::Create(Random::GetRanNum(Image2d::ImgNumber::maguro, Image2d::ImgNumber::ika), { 900, 400 }));
		pattern_1.push_back(Image2d::Create(Random::GetRanNum(Image2d::ImgNumber::maguro, Image2d::ImgNumber::ika), { 1040, 400 }));
		pattern_1_flag = false;
		pattern_1_timer = Random::GetRanNum(600, 1200);
	}
	// 次を出題するまでの待機時間
	else if(pattern_1_flag == true || wait_timer_1 <= 0)
	{
		if (wait_timer_1 <= 0)
		{
			geta_1_pieces = 0;
			geta_1_number.clear();
			geta_1_sushi_list.clear();
			combo_bonus = 1;
			pattern_1_timer = 120;
			pattern_1_flag = true;
			Audio::GetInstance()->PlayWave("Resources/SE/wrong.wav", 0, 0.1f);
		}
		wait_timer_1 = 1200;
		pattern_1.clear();
		pattern_1_timer--;
	}

	// 次の注文を出す
	if (pattern_2_timer <= 0)
	{
		pattern_2.push_back(Image2d::Create(Random::GetRanNum(Image2d::ImgNumber::maguro, Image2d::ImgNumber::ika), { 180, 400 }));
		pattern_2.push_back(Image2d::Create(Random::GetRanNum(Image2d::ImgNumber::maguro, Image2d::ImgNumber::ika), { 320, 400 }));
		pattern_2.push_back(Image2d::Create(Random::GetRanNum(Image2d::ImgNumber::maguro, Image2d::ImgNumber::ika), { 460, 400 }));
		pattern_2_flag = false;
		pattern_2_timer = Random::GetRanNum(600, 1200);
	}
	// 次を出題するまでの待機時間
	else if (pattern_2_flag == true || wait_timer_2 <= 0)
	{
		if (wait_timer_2 <= 0)
		{
			geta_2_pieces = 0;
			geta_2_number.clear();
			geta_2_sushi_list.clear();
			combo_bonus = 1;
			pattern_2_timer = 120;
			pattern_2_flag = true;
			Audio::GetInstance()->PlayWave("Resources/SE/wrong.wav", 0, 0.1f);
		}
		wait_timer_2 = 1200;
		pattern_2.clear();
		pattern_2_timer--;
	}

	// 次の注文を出す
	if (pattern_3_timer <= 0)
	{
		pattern_3.push_back(Image2d::Create(Random::GetRanNum(Image2d::ImgNumber::maguro, Image2d::ImgNumber::ika), { 1340, 400 }));
		pattern_3.push_back(Image2d::Create(Random::GetRanNum(Image2d::ImgNumber::maguro, Image2d::ImgNumber::ika), { 1480, 400 }));
		pattern_3.push_back(Image2d::Create(Random::GetRanNum(Image2d::ImgNumber::maguro, Image2d::ImgNumber::ika), { 1620, 400 }));
		pattern_3_flag = false;
		pattern_3_timer = Random::GetRanNum(600, 1200);
	}
	// 次を出題するまでの待機時間
	else if (pattern_3_flag == true || wait_timer_3 <= 0)
	{
		if (wait_timer_3 <= 0)
		{
			geta_3_pieces = 0;
			geta_3_number.clear();
			geta_3_sushi_list.clear();
			combo_bonus = 1;
			pattern_3_timer = 120;
			pattern_3_flag = true;
			Audio::GetInstance()->PlayWave("Resources/SE/wrong.wav", 0, 0.1f);
		}
		wait_timer_3 = 1200;
		pattern_3.clear();
		pattern_3_timer--;
	}

	if (pattern_1_flag == false)
	{
		wait_timer_1--;
	}
	if (pattern_2_flag == false)
	{
		wait_timer_2--;
	}
	if (pattern_3_flag == false)
	{
		wait_timer_3--;
	}
#pragma endregion
}

void Sushi::Judge()
{
#pragma region 寿司が3つ置かれたら下駄ごとに正誤判定を行う
	// 間違えた場合
	if (isPut_1 && (int)geta_1_sushi_list.size() >= 1)
	{
		isPut_1 = false;
		int pattern_1_num = pattern_1[geta_1_pieces]->GetNumber();
		if (geta_1_number[geta_1_pieces] != pattern_1_num)
		{
			geta_1_pieces = 0;
			geta_1_number.clear();
			pattern_1.clear();
			geta_1_sushi_list.clear();
			pattern_1_timer = 120;
			pattern_1_flag = true;
			combo_bonus = 1;
			Audio::GetInstance()->PlayWave("Resources/SE/wrong.wav", 0, 0.1f);
			return;
		}
		else
		{
			geta_1_pieces++;
		}
	}
	if (isPut_2 && (int)geta_2_sushi_list.size() >= 1)
	{
		isPut_2 = false;
		int pattern_2_num = pattern_2[geta_2_pieces]->GetNumber();
		if (geta_2_number[geta_2_pieces] != pattern_2_num)
		{
			geta_2_pieces = 0;
			geta_2_number.clear();
			pattern_2.clear();
			geta_2_sushi_list.clear();
			pattern_2_timer = 120;
			pattern_2_flag = true;
			combo_bonus = 1;
			Audio::GetInstance()->PlayWave("Resources/SE/wrong.wav", 0, 0.1f);
			return;
		}
		else
		{
			geta_2_pieces++;
		}
	}
	if (isPut_3 && (int)geta_3_sushi_list.size() >= 1)
	{
		isPut_3 = false;
		int pattern_3_num = pattern_3[geta_3_pieces]->GetNumber();
		if (geta_3_number[geta_3_pieces] != pattern_3_num)
		{
			geta_3_pieces = 0;
			geta_3_number.clear();
			pattern_3.clear();
			geta_3_sushi_list.clear();
			pattern_3_timer = 120;
			pattern_3_flag = true;
			combo_bonus = 1;
			Audio::GetInstance()->PlayWave("Resources/SE/wrong.wav", 0, 0.1f);
			return;
		}
		else
		{
			geta_3_pieces++;
		}
	}

	// 合ってた場合
	if (geta_1_pieces >= 3)
	{
		geta_1_pieces = 0;
		if (geta_1_number[0] == pattern_1[0]->GetNumber() && geta_1_number[1] == pattern_1[1]->GetNumber() && geta_1_number[2] == pattern_1[2]->GetNumber())
		{
			geta_1_number.clear();
			pattern_1.clear();
			geta_1_sushi_list.clear(); 
			pattern_1_flag = true;
			time_bonus = wait_timer_1;
			score += (500 + time_bonus) * combo_bonus;
			combo_bonus += combo_bonus;
			time_bonus = 0;
			Audio::GetInstance()->PlayWave("Resources/SE/correct.wav", 0, 0.1f);
			return;
		}
	}
	if (geta_2_pieces >= 3)
	{
		geta_2_pieces = 0;
		if (geta_2_number[0] == pattern_2[0]->GetNumber() && geta_2_number[1] == pattern_2[1]->GetNumber() && geta_2_number[2] == pattern_2[2]->GetNumber())
		{
			geta_2_number.clear();
			pattern_2.clear();
			geta_2_sushi_list.clear();
			pattern_2_flag = true;
			time_bonus = wait_timer_2;
			score += (500 + time_bonus) * combo_bonus;
			combo_bonus += combo_bonus;
			time_bonus = 0;
			Audio::GetInstance()->PlayWave("Resources/SE/correct.wav", 0, 0.1f);
			return;
		}
	}
	if (geta_3_pieces >= 3)
	{
		geta_3_pieces = 0;
		if (geta_3_number[0] == pattern_3[0]->GetNumber() && geta_3_number[1] == pattern_3[1]->GetNumber() && geta_3_number[2] == pattern_3[2]->GetNumber())
		{
			geta_3_number.clear();
			pattern_3.clear();
			geta_3_sushi_list.clear();
			pattern_3_flag = true;
			time_bonus = wait_timer_3;
			score += (500 + time_bonus) * combo_bonus;
			combo_bonus += combo_bonus;
			time_bonus = 0;
			Audio::GetInstance()->PlayWave("Resources/SE/correct.wav", 0, 0.1f);
			return;
		}
	}

#pragma endregion
}
