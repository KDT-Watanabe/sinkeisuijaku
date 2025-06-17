#include "DxLib.h"		// DxLib
#include<iostream>
#include "Game.h"		// Gameヘッダ
#include "Card.h"
#include "InputMouse.h"

//
// シングルトン保持変数の初期化
//
Game* Game::s_self_ptr = nullptr;
//Cards* cTrump = new Cards;
std::shared_ptr<Cards> cTrump(new Cards());

/// <summary>
/// 入力処理
/// </summary>
/// <returns>結果</returns>
int Game::input()
{
	GetMousePoint(&mouse_x, &mouse_y);
	return 0;
}

/// <summary>
/// 画面更新処理
/// </summary>
/// <returns>結果</returns>
int Game::update()
{
	switch (nGame_mode)
	{
	case GraphInit:
		bgm_mp = LoadSoundMem("data/mp/BGM.mp3");
		mj_bg = LoadGraph("data/mj.png");
		click_bg = LoadGraph("data/click_mj.png");
		trump_BG = LoadGraph("data/trump_BG.jpg");
		cTrump->back_image = LoadGraph("data/card_back.png");
		for (int i = 0; i < CARD_MAX; i++)
		{
			// 画像がすでに読み込まれていたら削除する
			if (cTrump->trump_image[i] != -1)
			{
				DeleteGraph(cTrump->trump_image[i]);
			}

			char fname[64];
			sprintf_s(fname, "data/%d.png", i);
			cTrump->trump_image[i] = LoadGraph(fname);
		}
		for (int i = 0; i < 4; i++) {
			if (cTrump->collect_SE[i] != -1) {
				DeleteSoundMem(cTrump->collect_SE[i]);
			}

			char fname[64];
			sprintf_s(fname, "data/mp/collect%d.mp3", i);

			cTrump->collect_SE[i] = LoadSoundMem(fname);
		}
		cTrump->sellect_SE = LoadSoundMem("data/mp/sellect.mp3");
		cTrump->miss_SE = LoadSoundMem("data/mp/miss.mp3");
		nGame_mode = Title;
		//PlaySoundMem(bgm_mp, DX_PLAYTYPE_LOOP);
		break;
	case Title:
		title_frame++;
		if (title_frame > 60) {
			title_frame = 0;
		}
		if (IsMouseOn(MOUSE_INPUT_LEFT)) {
			nGame_mode = GameNow;
			cTrump->Init();
		}
		break;
	case GameNow:
		cTrump->Update(mouse_x, mouse_y);
		for (int i = 0; i < CARD_MAX; i++) {
			if (cTrump->sTrump[i].matched == 1) {
				matched_cnt++;
			}
			if (matched_cnt >= CARD_MAX) {
				nGame_mode = Result;
			}

		}
		//if (CheckHitKey(KEY_INPUT_SPACE))nGame_mode = Result;
		matched_cnt = 0;
		break;
	case Result:
		if (IsMouseOn(MOUSE_INPUT_LEFT)) {
			title_frame = 0;
			nGame_mode = Title;
		}
		break;
	}
	
	InputMouseUpdate();
	return 0;
}

/// <summary>
/// 描画処理
/// </summary>
/// <returns>結果</returns>
int Game::render()
{
	DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, 2.5, 0, trump_BG, TRUE);
	//DrawFormatString(0, 20, GetColor(0, 0, 0), "%d", nGame_mode);
	switch (nGame_mode) {
	case Title:
		DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, 4, 0, mj_bg, TRUE);
		if (title_frame < 30) {
			DrawRotaGraph(WINDOW_W / 2, WINDOW_H * 3 / 4, 2, 0, click_bg, TRUE);
		}
		break;
	case GameNow:
		cTrump->Render();
		break;
	case Result:
		SetFontSize(80);
		char fstring[1000];
		sprintf_s(fstring, "お手付きの数：%d", cTrump->miss_cnt);
		float string_w = GetDrawFormatStringWidth(fstring);
		DrawFormatString(WINDOW_W / 2 - string_w / 2, WINDOW_H*2 / 5, GetColor(255, 255, 255),
			fstring, cTrump->miss_cnt);
		if (cTrump->miss_cnt < 10) {
			SetFontSize(40);
			char fstring[100];
			sprintf_s(fstring, "チーター？");
			float string_w = GetDrawFormatStringWidth(fstring);
			DrawString(WINDOW_W / 2 - string_w / 2, WINDOW_H * 3 / 5, fstring, GetColor(255, 255, 255));
		}
		else if (cTrump->miss_cnt < 20) {
			SetFontSize(40);
			char fstring[100];
			sprintf_s(fstring, "天才！！");
			float string_w = GetDrawFormatStringWidth(fstring);
			DrawString(WINDOW_W / 2 - string_w / 2, WINDOW_H * 3 / 5, fstring, GetColor(255, 255, 255));
		}
		else if (cTrump->miss_cnt < 30) {
			SetFontSize(40);
			char fstring[100];
			sprintf_s(fstring, "プレイしてくれてありがとう！");
			float string_w = GetDrawFormatStringWidth(fstring);
			DrawString(WINDOW_W / 2 - string_w / 2, WINDOW_H * 3 / 5, fstring, GetColor(255, 255, 255));
		}
		else if (cTrump->miss_cnt < 40) {
			SetFontSize(40);
			char fstring[100];
			sprintf_s(fstring, "クリアおめでとう");
			float string_w = GetDrawFormatStringWidth(fstring);
			DrawString(WINDOW_W / 2 - string_w / 2, WINDOW_H * 3 / 5, fstring, GetColor(255, 255, 255));
		}
		else if (cTrump->miss_cnt >= 40) {
			SetFontSize(40);
			char fstring[100];
			sprintf_s(fstring, "頑張ったで賞\n受賞！！");
			float string_w = GetDrawFormatStringWidth(fstring);
			DrawString(WINDOW_W / 2 - string_w / 2, WINDOW_H * 3 / 5, fstring, GetColor(255, 255, 255));
		}
		break;
	}
	return 0;

}