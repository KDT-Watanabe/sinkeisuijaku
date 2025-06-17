#include "Game.h"		// Gameクラスヘッダ


// ------------------------------
//  WinMain
// ------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{

	// ゲームオブジェクト生成
	Game* game_ptr = Game::GetObject();

	// 参照を作成
	Game& game = *game_ptr;


	// ゲーム初期化
	if (!game.Init()) {
		return -1;				// DxLibの初期化に失敗したら直ちに終了
	}

	// 参照を使ってゲームループ起動
	game.GameLoop();

	// ゲームオブジェクト破棄
	if (game_ptr != nullptr)
	{
		// オブジェクトの破棄
		delete game_ptr;
		// ポインター変数の初期化
		game_ptr = nullptr;
	}


	// ======================================
	//
	//  動作確認
	// 
	// ======================================

	//
	// 破棄したオブジェクトを参照してみる
	//

	//game_ptr->Init();			// ポインターは初期化されているのでnullptrチェックに掛かる。

	//game.Init();				// 参照はそのままなのでnullptrチェックに掛からない。（オブジェクトはすでに破棄されているので動作は不定）



	// ソフトの終了
	return 0;
}