#include "Card.h"
#include "DxLib.h"
#include "InputMouse.h"
#include "Hit.h"

Cards::Cards() {

	Init();
	back_image = LoadGraph("data/card_back.png");
	for (int i = 0; i < CARD_MAX; i++)
	{
		// ‰æ‘œ‚ª‚·‚Å‚É“Ç‚Ýž‚Ü‚ê‚Ä‚¢‚½‚çíœ‚·‚é
		if (trump_image[i] != -1)
		{
			DeleteGraph(trump_image[i]);
		}

		char fname[64];
		sprintf_s(fname, "data/%d.png", i);
		trump_image[i] = LoadGraph(fname);
	}
	for (int i = 0; i < 4; i++) {
		if (collect_SE[i] != -1) {
			DeleteSoundMem(collect_SE[i]);
		}

		char fname[64];
		sprintf_s(fname, "data/mp/collect%d.mp3", i);

		collect_SE[i] = LoadSoundMem(fname);
	}
	sellect_SE = LoadSoundMem("data/mp/sellect.mp3");
	miss_SE = LoadSoundMem("data/mp/miss.mp3");
	count = 0;
	select_cnt = 0;
	for (int i = 0; i < 2; i++) {
		select_num[i] = 0;
	}
	game_mode = 0;
}

Cards::~Cards() {
	for (int i = 0; i < CARD_MAX; i++) {
		DeleteGraph(trump_image[i]);
	}

}

void Cards::Init() {

	InputMouseInit();

	for (int i = 0; i < CARD_MAX; i++) {
		sTrump[i].shuffle_num = i;
		sTrump[i].matched = 0;
		sTrump[i].hit = 0;
	}
	for (int i = 0; i < 2; i++) {
		select_num[i] = 0;
	}
	select_cnt = 0;
	game_mode = select;

	for (int i = 0; i < 100000; i++) {
		int shuffle_base = GetRand(CARD_MAX - 1);
		int shuffle_moved = GetRand(CARD_MAX - 1);
		while (shuffle_base == shuffle_moved) {
			shuffle_moved = GetRand(CARD_MAX - 1);
		}
		int base_keep = sTrump[shuffle_base].shuffle_num;
		sTrump[shuffle_base].shuffle_num = sTrump[shuffle_moved].shuffle_num;
		sTrump[shuffle_moved].shuffle_num = base_keep;
	}

	for (int i = 0; i < CARD_MAX; i++) {
		sTrump[i].type = sTrump[i].shuffle_num % 4;
		sTrump[i].number = sTrump[i].shuffle_num / 4;
		sTrump[i].x = i % 13;
		sTrump[i].y = i / 13 % 4;
	}
}



void Cards::Update(int mouse_x, int mouse_y) {
	InputMouseUpdate();
	switch (game_mode) {
	case select:
		if (IsMouseOn(MOUSE_INPUT_LEFT)) {
			for (int i = 0; i < CARD_MAX; i++) {
				if (TrumpHit(sTrump[i].x * 90 + 40, sTrump[i].y * 140 + 70, mouse_x, mouse_y) == 1) {
					if (sTrump[i].hit != 1 && sTrump[i].matched != 1) {
						PlaySoundMem(sellect_SE, DX_PLAYTYPE_BACK, TRUE);
						sTrump[i].hit = 1;
						select_num[select_cnt] = i;
						select_cnt++;
					}
				}
			}
		}
		if (select_cnt >= 2) {
			game_mode = judge;
		}
		break;
	case judge:
		if (sTrump[select_num[0]].number == sTrump[select_num[1]].number) {
			for (int i = 0; i < 2; i++) {
				sTrump[select_num[i]].matched = 1;
			}
			for (int i = 0; i < CARD_MAX; i++) {
				sTrump[i].hit = 0;
			}
			game_mode = select;
			select_cnt = 0;
			judge_cnt = 0;
			PlaySoundMem(collect_SE[collect_cnt], DX_PLAYTYPE_BACK, TRUE);
			collect_cnt++;
			if (collect_cnt > 3)collect_cnt = 3;
			break;
		}
		if (select_cnt >= 2) {
			if (miss_mode == false) {
				PlaySoundMem(miss_SE, DX_PLAYTYPE_BACKBIT, TRUE);
				miss_mode = true;
			}
			if (IsMouseOn(MOUSE_INPUT_LEFT)) {
				for (int i = 0; i < CARD_MAX; i++) {
					sTrump[i].hit = 0;
				}
				collect_cnt = 0;
				game_mode = select;
				select_cnt = 0;
				judge_cnt = 0;
				miss_cnt++;
				miss_mode = false;
			}
		}
		break;
	}
}
void Cards::Render() {
	for (int h = 0; h < 4; h++) {
		for (int w = 0; w < 13; w++) {
			DrawBox(w * 90 + 40, h * 140 + 70, w * 90 + 120, h * 140 + 170, GetColor(255, 255, 255), TRUE);
			/*DrawGraph(w * 90, h * 160, trump_image[count], TRUE);*/
			DrawRotaGraph(w * 90 + 80, h * 140 + 120, 0.1, 0, trump_image[sTrump[count].shuffle_num], TRUE);
			if (sTrump[count].hit != 1 && sTrump[count].matched != 1) {
				DrawRotaGraph(w * 90 + 80, h * 140 + 120, 0.5, 0, back_image, TRUE);
			}
			//DrawFormatString(w * 90 + 40, h * 140 + 70, GetColor(255, 255, 255), "type:%d\nnum:%d\n(x,y):(%d,%d)\n%d", sTrump[count].type, sTrump[count].number + 1, sTrump[count].x, sTrump[count].y, sTrump[count].shuffle_num);
			count++;
		}
	}

	for (int i = 0; i < CARD_MAX; i++) {
		if (sTrump[i].hit == 1) {
			DrawLineBox(sTrump[i].x * 90 + 40, sTrump[i].y * 140 + 70, sTrump[i].x * 90 + 120, sTrump[i].y * 140 + 170, GetColor(255, 0, 0), 5);
		}
		if (sTrump[i].matched == 1) {
			DrawLineBox(sTrump[i].x * 90 + 40, sTrump[i].y * 140 + 70, sTrump[i].x * 90 + 120, sTrump[i].y * 140 + 170, GetColor(255, 255, 0), 5);
		}
	}
	count = 0;
	//DrawFormatString(0, 0, GetColor(0, 0, 0), "%d", game_mode);
	//DrawFormatString(0, 40, GetColor(0, 0, 0), "%d", miss_cnt);
}
void Cards::Exit() {
	InputMouseExit();
}