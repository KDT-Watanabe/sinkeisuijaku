#pragma once
bool TrumpHit(int box_x1, int box_y1, int mouse_x, int mouse_y) {
	if (mouse_x > box_x1 && mouse_x < box_x1 + 70
		&& mouse_y > box_y1 && mouse_y < box_y1 + 100) {
		return 1;
	}
	else {
		return 0;
	}
}