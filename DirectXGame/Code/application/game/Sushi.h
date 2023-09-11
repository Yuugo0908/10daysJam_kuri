#pragma once
#include "DirectXCommon.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "DebugText.h"
#include "SafeDelete.h"

#include <stdlib.h>
#include <time.h>
#include <list>

class Sushi
{
private:
	Sushi();

	~Sushi();
public:
	// コピーコンストラクタを無効化
	Sushi(const Sushi& obj) = delete;
	// 代入演算子を無効化
	Sushi& operator=(const Sushi& obj) = delete;

public: // 静的メンバ変数
	static Sushi* GetInstance();

public: // メンバ関数
	// 毎フレーム処理
	void Update();
	// 描画
	void Draw();
	// ドラッグアンドドロップ
	void DragDrop();
	// ネタ生成
	void MakeNeta();
	// 寿司生成
	void MakeSushi();
	// 寿司下駄に置く
	void PutSushi();
	// パターン生成
	void Pattern();
	// 下駄に置いた寿司の数
	void SetGeta();

private: // メンバ変数
	Keyboard* keyboard = Keyboard::GetInstance();
	Mouse* mouse = Mouse::GetInstance();

	// 画像
	// 寿司下駄
	std::vector<Image2d*> sushi_getas;
	Image2d* sushi_geta_1 = nullptr;
	Image2d* sushi_geta_2 = nullptr;
	Image2d* sushi_geta_3 = nullptr;
	XMFLOAT2 geta_1_pos = { 750.0f, 570.0f };
	XMFLOAT2 geta_2_pos = { 165.0f, 570.0f };
	XMFLOAT2 geta_3_pos = { 1335.0f, 570.0f };
	// 下駄に乗っている寿司一覧
	std::vector<Image2d*> geta_1_sushi_list;
	std::vector<Image2d*> geta_2_sushi_list;
	std::vector<Image2d*> geta_3_sushi_list;
	// 下駄に乗っている寿司の数
	int geta_1_pieces = 0;
	int geta_2_pieces = 0;
	int geta_3_pieces = 0;
	// 下駄に乗せている寿司の番号
	int geta_1_number[3] = {};
	int geta_2_number[3] = {};
	int geta_3_number[3] = {};
	bool isPut = false;
	bool isGetaSet = false;

	// 米桶
	XMFLOAT2 kome_oke_position = { -50.0f, 850.0f };
	Image2d* kome_oke = nullptr;

	//寿司一覧
	std::vector<Image2d*> sushi_list;
	Image2d* maguro = nullptr;
	Image2d* samon = nullptr;
	Image2d* ebi = nullptr;
	Image2d* tamago = nullptr;
	Image2d* ika = nullptr;
	bool isCombine = false;

	// ネタ一覧
	const XMFLOAT2 maguro_neta_position	 = {1250.0f, 900.0f};
	const XMFLOAT2 samon_neta_position	 = {1375.0f, 900.0f};
	const XMFLOAT2 ebi_neta_position	 = {1500.0f, 900.0f};
	const XMFLOAT2 tamago_neta_position	 = {1625.0f, 900.0f};
	const XMFLOAT2 ika_neta_position	 = {1750.0f, 900.0f};
	Image2d* maguro_neta = nullptr;
	Image2d* samon_neta = nullptr;
	Image2d* ebi_neta = nullptr;
	Image2d* tamago_neta = nullptr;
	Image2d* ika_neta = nullptr;

	// ドラッグ表示用
	Image2d* maguro_neta_dis = nullptr;
	Image2d* samon_neta_dis = nullptr;
	Image2d* ebi_neta_dis = nullptr;
	Image2d* tamago_neta_dis = nullptr;
	Image2d* ika_neta_dis = nullptr;

	// お題用
	std::vector<Image2d*> pattern;
	Image2d* maguro_neta_pat = nullptr;
	Image2d* samon_neta_pat = nullptr;
	Image2d* ebi_neta_pat = nullptr;
	Image2d* tamago_neta_pat = nullptr;
	Image2d* ika_neta_pat = nullptr;

	// シャリ
	std::vector<Image2d*> shari_list;
	Image2d* shari = nullptr;

	// ドラッグしている画像データ取得用
	Image2d* dragData = nullptr;
	XMFLOAT2 drag_maxPos;
	XMFLOAT2 drag_minPos;

	bool isDrag = false; // 指定の寿司をドラッグしているか
	bool isDragNow = false; // 何かの寿司をドラッグしているか
	int dragNum = 0; // ドラッグしている寿司の番号

	int imgNumber = 0; // 画像管理の番号
	int shariNumber = 0; // シャリの番号
	int netaNumber = 0; // ネタの番号
	int sushiNumber = 0; // 寿司の番号
};

