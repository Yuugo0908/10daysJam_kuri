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

private: // メンバ変数
	Keyboard* keyboard = Keyboard::GetInstance();
	Mouse* mouse = Mouse::GetInstance();

	// 画像
	Image2d* sushi_geta = nullptr;
	Image2d* wasabi = nullptr;

	//寿司一覧
	std::vector<Image2d*> sushi_list;
	Image2d* maguro = nullptr;
	Image2d* samon = nullptr;
	Image2d* ebi = nullptr;
	Image2d* tamago = nullptr;
	Image2d* ika = nullptr;
	bool isCombine = false;
	// ネタ一覧
	Image2d* maguro_neta = nullptr;
	Image2d* samon_neta = nullptr;
	Image2d* ebi_neta = nullptr;
	Image2d* tamago_neta = nullptr;
	Image2d* ika_neta = nullptr;

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
};

