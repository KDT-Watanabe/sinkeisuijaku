#pragma once
#include <ctime>
#include "Dxlib.h"

//	定数の宣言
#define WINDOW_W 1280	// 画面サイズ　横
#define WINDOW_H 720	// 画面サイズ　縦
#define COLOR_DEPTH 32	// 色深度

/// <summary>
/// Gameクラス（シングルトン）
///  ゲーム本体の実装
/// </summary>
class Game
{

protected:
	int title_frame = 0;
	int count;
	/// <summary>
	/// シングルトンオブジェクト保持
	/// </summary>
	static Game* s_self_ptr;

	/// <summary>
	/// 隠蔽コンストラクター
	/// </summary>
	Game() {}

	int matched_cnt;
    int trump_BG;
	int bgm_mp=0;
public:
	int mj_bg;
	int click_bg;
	int nGame_mode=0;
	enum Mode {
		GraphInit,
		Title,
		GameNow,
		Result,
		Ending,

	};
	// マウス座標用の変数
	int mouse_x;
	int mouse_y;

	/// <summary>
	/// オブジェクトの取得
	/// </summary>
	/// <returns>オブジェクト</returns>
	static Game* GetObject()
	{
		// シングルトンオブジェクトの存在チェック
		if (Game::s_self_ptr == nullptr)
		{
			// オブジェクトを生成
			Game::s_self_ptr = new Game();
		}

		// シングルトンオブジェクトをリターン
		return Game::s_self_ptr;
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Game()
	{
		// =======================================
		//  終了処理
		// =======================================
		// DXライブラリ使用の終了処理
		DxLib_End();

		// シングルトン保持変数のリセット
		Game::s_self_ptr = nullptr;
		;
	}

	/// <summary>
	/// 初期化メソッド
	/// </summary>
	/// <returns>結果</returns>
	bool Init()
	{
		// オブジェクトチェック
		if (this == nullptr)
		{
			return false;
		}

		// =======================================
		//  初期化処理
		// =======================================
		// ログの書き出しを無効化
		SetOutApplicationLogValidFlag(FALSE);	// ログの書き出しを無効化

		// ウィンドウモードの設定
		ChangeWindowMode(TRUE);					// ウインドウモードを有効化

		// ウィンドウサイズとカラービットの設定
		SetGraphMode(WINDOW_W, WINDOW_H, COLOR_DEPTH);

		// ウィンドウのタイトル
		SetMainWindowText("DxLib Template");

		// 背景色の設定
		SetBackgroundColor(128, 128, 128);

		// ＤＸライブラリ初期化処理
		if (DxLib_Init() == -1)
		{
			return false;						// 初期化に失敗した場合はfalseを返す
		}

		// ウィンドウ描画モード設定
		SetDrawScreen(DX_SCREEN_BACK);			// 裏画面に描画する

		return true;


	}
	/// <summary>
	/// Gameループメソッド
	/// </summary>
	void GameLoop() {

		// オブジェクトチェック
		if (this == nullptr)
		{
			return;
		}

		// ------------------------------
		//  ゲームループ
		// ------------------------------
		while (ProcessMessage() == 0)
		{
			// リフレッシュレートを設定するための処理
			clock_t check_fps = clock() + CLOCKS_PER_SEC / 60;

			// マウスカーソル表示設定
			SetMouseDispFlag(TRUE);

			// printfDxの初期化
			clsDx();

			// 画面上の描画を初期化（画面を消去）
			ClearDrawScreen();

			//  入力処理
			this->input();

			//  画面描画処理
			this->update();

			//  描画処理
			this->render();


			// リフレッシュレートが一定になるまで待つ処理
			while (clock() < check_fps) {}

			// 裏画面の描画を表に反映
			ScreenFlip();


			// ESCキーでループから抜ける
			if (CheckHitKey(KEY_INPUT_ESCAPE)) {
				break;
			}

		}
	}

protected:

	/// <summary>
	/// 入力処理
	/// </summary>
	/// <returns>結果</returns>
	int input();


	/// <summary>
	/// 画面更新処理
	/// </summary>
	/// <returns>結果</returns>
	int update();


	/// <summary>
	/// 音声再生処理
	/// </summary>
	/// <returns>結果</returns>
	int render();

};
