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
	maguro_neta_dis = Image2d::Create(Image2d::ImgNumber::maguro_neta, maguro_neta_position);
	samon_neta_dis = Image2d::Create(Image2d::ImgNumber::samon_neta, samon_neta_position);
	ebi_neta_dis = Image2d::Create(Image2d::ImgNumber::ebi_neta, ebi_neta_position);
	tamago_neta_dis = Image2d::Create(Image2d::ImgNumber::tamago_neta, tamago_neta_position);
	ika_neta_dis = Image2d::Create(Image2d::ImgNumber::ika_neta, ika_neta_position);

	// 米桶
	kome_oke = Image2d::Create(Image2d::ImgNumber::kome_oke, kome_oke_position);

	// 寿司下駄
	sushi_geta_1 = Image2d::Create(Image2d::ImgNumber::sushi_geta, geta_1_pos);
	sushi_geta_2 = Image2d::Create(Image2d::ImgNumber::sushi_geta, geta_2_pos);
	sushi_geta_3 = Image2d::Create(Image2d::ImgNumber::sushi_geta, geta_3_pos);
	sushi_getas.push_back(sushi_geta_1);
	sushi_getas.push_back(sushi_geta_2);
	sushi_getas.push_back(sushi_geta_3);

	// タイマー表示
	wait_bar_1 = Image2d::Create(Image2d::ImgNumber::wait_bar, { 760.0f,750.0f });
	wait_bar_2 = Image2d::Create(Image2d::ImgNumber::wait_bar, { 175.0f,750.0f });
	wait_bar_3 = Image2d::Create(Image2d::ImgNumber::wait_bar, { 1345.0f,750.0f });
	wait_gauge_1 = Image2d::Create(Image2d::ImgNumber::wait_gauge, { 835.0f,752.0f });
	wait_gauge_2 = Image2d::Create(Image2d::ImgNumber::wait_gauge, { 250.0f,752.0f });
	wait_gauge_3 = Image2d::Create(Image2d::ImgNumber::wait_gauge, { 1415.0f,752.0f });

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
	// 正誤判定用
	isCorrect_1 = false;
	isCorrect_2 = false;
	isCorrect_3 = false;
	// 寿司が合っている数
	correct_count_1 = 0;
	correct_count_2 = 0;
	correct_count_3 = 0;
	// 前に置いた寿司のフラグ
	isCorrect_list_1 = {0, 0, 0};
	isCorrect_list_2 = {0, 0, 0};
	isCorrect_list_3 = {0, 0, 0};

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
		sushi_list.push_back(maguro_neta);
	}
	// サーモン生成
	if (mouse->TriggerMouseLeft() && 
		samon_neta_dis->GetCenterPosition() - samon_neta_dis->GetDataSize() / 2 < mouse->GetMousePos() &&
		mouse->GetMousePos() < samon_neta_dis->GetCenterPosition() + samon_neta_dis->GetDataSize() / 2)
	{
		samon_neta = Image2d::Create(Image2d::ImgNumber::samon_neta, { 0.0f, 0.0f });
		samon_neta->SetPosition(samon_neta_position);
		sushi_list.push_back(samon_neta);
	}
	// エビ生成
	if (mouse->TriggerMouseLeft() && 
		ebi_neta_dis->GetCenterPosition() - ebi_neta_dis->GetDataSize() / 2 < mouse->GetMousePos() &&
		mouse->GetMousePos() < ebi_neta_dis->GetCenterPosition() + ebi_neta_dis->GetDataSize() / 2)
	{
		ebi_neta = Image2d::Create(Image2d::ImgNumber::ebi_neta, { 0.0f, 0.0f });
		ebi_neta->SetPosition(ebi_neta_position);
		sushi_list.push_back(ebi_neta);
	}
	// タマゴ生成
	if (mouse->TriggerMouseLeft() && 
		tamago_neta_dis->GetCenterPosition() - tamago_neta_dis->GetDataSize() / 2 < mouse->GetMousePos() &&
		mouse->GetMousePos() < tamago_neta_dis->GetCenterPosition() + tamago_neta_dis->GetDataSize() / 2)
	{
		tamago_neta = Image2d::Create(Image2d::ImgNumber::tamago_neta, { 0.0f, 0.0f });
		tamago_neta->SetPosition(tamago_neta_position);
		sushi_list.push_back(tamago_neta);
	}
	// イカ生成
	if (mouse->TriggerMouseLeft() && 
		ika_neta_dis->GetCenterPosition() - ika_neta_dis->GetDataSize() / 2 < mouse->GetMousePos() &&
		mouse->GetMousePos() < ika_neta_dis->GetCenterPosition() + ika_neta_dis->GetDataSize() / 2)
	{
		ika_neta = Image2d::Create(Image2d::ImgNumber::ika_neta, { 0.0f, 0.0f });
		ika_neta->SetPosition(ika_neta_position);
		sushi_list.push_back(ika_neta);
	}

	// シャリ生成
	if (mouse->TriggerMouseLeft() &&
		kome_oke->GetCenterPosition() - kome_oke->GetDataSize() / 2 < mouse->GetMousePos() &&
		mouse->GetMousePos() < kome_oke->GetCenterPosition() + kome_oke->GetDataSize() / 2)
	{
		shari = Image2d::Create(Image2d::ImgNumber::shari, { 0.0f, 0.0f });
		shari->SetPosition(mouse->GetMousePos() - shari->GetDataSize() / 2);
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
				}
				else if (pattern_2_flag == false && j == 1)
				{
					geta_2_number.push_back(Image2d::ImgNumber::maguro);
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
				}
				else if (pattern_3_flag == false && j == 2)
				{
					geta_3_number.push_back(Image2d::ImgNumber::maguro);
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
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
				}
				else if (pattern_2_flag == false && j == 1)
				{
					geta_2_number.push_back(Image2d::ImgNumber::samon);
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
				}
				else if (pattern_3_flag == false && j == 2)
				{
					geta_3_number.push_back(Image2d::ImgNumber::samon);
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
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
				}
				else if (pattern_2_flag == false && j == 1)
				{
					geta_2_number.push_back(Image2d::ImgNumber::ebi);
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
				}
				else if (pattern_3_flag == false && j == 2)
				{
					geta_3_number.push_back(Image2d::ImgNumber::ebi);
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
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
				}
				else if (pattern_2_flag == false && j == 1)
				{
					geta_2_number.push_back(Image2d::ImgNumber::tamago);
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
				}
				else if (pattern_3_flag == false && j == 2)
				{
					geta_3_number.push_back(Image2d::ImgNumber::tamago);
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
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
				}
				else if (pattern_2_flag == false && j == 1)
				{
					geta_2_number.push_back(Image2d::ImgNumber::ika);
					geta_2_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
				}
				else if (pattern_3_flag == false && j == 2)
				{
					geta_3_number.push_back(Image2d::ImgNumber::ika);
					geta_3_sushi_list.push_back(sushi_list[dragNum]);
					sushi_list.erase(sushi_list.begin() + dragNum);
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
		pattern_1_timer = Random::GetRanNum(600, 900);
	}
	// 次を出題するまでの待機時間
	else if(pattern_1_flag == true || wait_timer_1 <= 0)
	{
		if (wait_timer_1 <= 0)
		{
			geta_1_pieces = 0;
			geta_1_number.clear();
			geta_1_sushi_list.clear();
			pattern_1_timer = 120;
			pattern_1_flag = true;
			combo_bonus = 1;
			correct_count_1 = 0;
			isCorrect_list_1 = { 0, 0, 0 };
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
		pattern_2_timer = Random::GetRanNum(600, 900);
	}
	// 次を出題するまでの待機時間
	else if (pattern_2_flag == true || wait_timer_2 <= 0)
	{
		if (wait_timer_2 <= 0)
		{
			geta_2_pieces = 0;
			geta_2_number.clear();
			geta_2_sushi_list.clear();
			pattern_2_timer = 120;
			pattern_2_flag = true;
			combo_bonus = 1;
			correct_count_2 = 0;
			isCorrect_list_2 = { 0, 0, 0 };
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
		pattern_3_timer = Random::GetRanNum(600, 900);
	}
	// 次を出題するまでの待機時間
	else if (pattern_3_flag == true || wait_timer_3 <= 0)
	{
		if (wait_timer_3 <= 0)
		{
			geta_3_pieces = 0;
			geta_3_number.clear();
			geta_3_sushi_list.clear();
			pattern_3_timer = 120;
			pattern_3_flag = true;
			combo_bonus = 1;
			correct_count_3 = 0;
			isCorrect_list_3 = { 0, 0, 0 };
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
#pragma region 寿司が1つ置かれたら下駄ごとに正誤判定を行う
	// 間違えた場合
	if (isPut_1 && (int)geta_1_sushi_list.size() >= 1)
	{
		isPut_1 = false;
		for (int i = 0; i < pattern_1.size(); i++)
		{
			// 違った場合
			if (pattern_1[i]->GetNumber() != geta_1_number[geta_1_pieces] || isCorrect_list_1[i] == 1)
			{
				isCorrect_1 = false;
				continue;
			}
			// 合っていた場合
			else
			{
				isCorrect_1 = true;
				geta_1_sushi_list[geta_1_pieces]->SetPosition({ geta_1_pos.x + 150 * i, geta_1_pos.y });
				correct_count_1++;
				geta_1_pieces++;
				isCorrect_list_1[i] = 1;
				break;
			}
		}

		if (isCorrect_1 == false)
		{
			geta_1_pieces = 0;
			geta_1_number.clear();
			pattern_1.clear();
			geta_1_sushi_list.clear();
			pattern_1_timer = 120;
			pattern_1_flag = true;
			combo_bonus = 1;
			correct_count_1 = 0;
			isCorrect_list_1 = { 0, 0, 0 };
			Audio::GetInstance()->PlayWave("Resources/SE/wrong.wav", 0, 0.1f);
		}
	}
	if (isPut_2 && (int)geta_2_sushi_list.size() >= 1)
	{
		isPut_2 = false;
		for (int i = 0; i < pattern_2.size(); i++)
		{
			if (pattern_2[i]->GetNumber() != geta_2_number[geta_2_pieces] || isCorrect_list_2[i] == 1)
			{
				isCorrect_2 = false;
				continue;
			}
			else
			{
				isCorrect_2 = true;
				geta_2_sushi_list[geta_2_pieces]->SetPosition({ geta_2_pos.x + 150 * i, geta_2_pos.y });
				correct_count_2++;
				geta_2_pieces++;
				isCorrect_list_2[i] = 1;
				break;
			}
		}

		if (isCorrect_2 == false)
		{
			geta_2_pieces = 0;
			geta_2_number.clear();
			pattern_2.clear();
			geta_2_sushi_list.clear();
			pattern_2_timer = 120;
			pattern_2_flag = true;
			combo_bonus = 1;
			correct_count_2 = 0;
			isCorrect_list_2 = { 0, 0, 0 };
			Audio::GetInstance()->PlayWave("Resources/SE/wrong.wav", 0, 0.1f);
		}
	}
	if (isPut_3 && (int)geta_3_sushi_list.size() >= 1)
	{
		isPut_3 = false;
		for (int i = 0; i < pattern_3.size(); i++)
		{
			if (pattern_3[i]->GetNumber() != geta_3_number[geta_3_pieces] || isCorrect_list_3[i] == 1)
			{
				isCorrect_3 = false;
				continue;
			}
			else
			{
				isCorrect_3 = true;
				geta_3_sushi_list[geta_3_pieces]->SetPosition({ geta_3_pos.x + 150 * i, geta_3_pos.y });
				correct_count_3++;
				geta_3_pieces++;
				isCorrect_list_3[i] = 1;
				break;
			}
		}

		if (isCorrect_3 == false)
		{
			geta_3_pieces = 0;
			geta_3_number.clear();
			pattern_3.clear();
			geta_3_sushi_list.clear();
			pattern_3_timer = 120;
			pattern_3_flag = true;
			combo_bonus = 1;
			correct_count_3 = 0;
			isCorrect_list_3 = { 0, 0, 0 };
			Audio::GetInstance()->PlayWave("Resources/SE/wrong.wav", 0, 0.1f);
		}
	}

	// 3つ合ってた場合
	if (geta_1_pieces >= 3)
	{
		geta_1_pieces = 0;
		if (correct_count_1 >= 3)
		{
			geta_1_number.clear();
			pattern_1.clear();
			geta_1_sushi_list.clear(); 
			pattern_1_flag = true;
			time_bonus = wait_timer_1;
			score += (500 + time_bonus) * combo_bonus;
			combo_bonus += combo_bonus;
			time_bonus = 0;
			isCorrect_list_1 = { 0, 0, 0 };
			Audio::GetInstance()->PlayWave("Resources/SE/correct.wav", 0, 0.1f);
			return;
		}
	}
	if (geta_2_pieces >= 3)
	{
		geta_2_pieces = 0;
		if (correct_count_2 >= 3)
		{
			geta_2_number.clear();
			pattern_2.clear();
			geta_2_sushi_list.clear();
			pattern_2_flag = true;
			time_bonus = wait_timer_2;
			score += (500 + time_bonus) * combo_bonus;
			combo_bonus += combo_bonus;
			time_bonus = 0;
			isCorrect_list_2 = { 0, 0, 0 };
			Audio::GetInstance()->PlayWave("Resources/SE/correct.wav", 0, 0.1f);
			return;
		}
	}
	if (geta_3_pieces >= 3)
	{
		geta_3_pieces = 0;
		if (correct_count_3 >= 3)
		{
			geta_3_number.clear();
			pattern_3.clear();
			geta_3_sushi_list.clear();
			pattern_3_flag = true;
			time_bonus = wait_timer_3;
			score += (500 + time_bonus) * combo_bonus;
			combo_bonus += combo_bonus;
			time_bonus = 0;
			isCorrect_list_3 = { 0, 0, 0 };
			Audio::GetInstance()->PlayWave("Resources/SE/correct.wav", 0, 0.1f);
			return;
		}
	}

#pragma endregion
}
