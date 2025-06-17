#pragma once
#define CARD_MAX 52

struct sTrump {
	int type;
	int shuffle_num;
	int number;
	int x;
	int y;
	int hit;
	bool selected;
	bool matched;
};

class Cards {
protected:
	int count=0;
	int judge_cnt=0;
	int select_cnt=0;
	int select_num[2] = { 0,0 };
	int game_mode = 0;
	enum mode {
		select,
		judge,
	};
	
public:
	int collect_SE[4] = { 0 };
	int miss_SE = 0;
	bool miss_mode = false;
	int sellect_SE = 0;
	int miss_cnt=0;
	int trump_image[CARD_MAX] = { 0 };
	int back_image;
	int collect_cnt=0;
	Cards();
	~Cards();
	sTrump sTrump[CARD_MAX];
	
	void Init();
	void Update(int mouse_x, int mouse_y);
	void Render();
	void Exit();

};