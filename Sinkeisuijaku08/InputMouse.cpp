//---------------------------------------------------------------------------
//!	@file	InputMouse.cpp
//! @brief	マウス入力管理
//---------------------------------------------------------------------------
#include "InputMouse.h"
#include "DxLib.h"

namespace
{
constexpr int MAX_MOUSE_BUTTON = 8;

int mouseX_;
int mouseY_;

int mouseButtons_[MAX_MOUSE_BUTTON];

// マウスの配列検証用
bool IsOverMouseNum(int mouseID)
{
    return (mouseID >= MAX_MOUSE_BUTTON) || (mouseID < 0);
}
};   // namespace

//---------------------------------------------------------------------------
// 初期化
//---------------------------------------------------------------------------
void InputMouseInit()
{
    mouseX_ = 0;
    mouseY_ = 0;

    for(int i = 0; i < MAX_MOUSE_BUTTON; ++i) {
        mouseButtons_[i] = 0;
    }
}

//---------------------------------------------------------------------------
// 更新
//---------------------------------------------------------------------------
void InputMouseUpdate()
{
    int mouse_state = GetMouseInput();
    GetMousePoint(&mouseX_, &mouseY_);

    for(int i = 0; i < MAX_MOUSE_BUTTON; ++i) {
        if(mouse_state - 1 == i) {
            ++mouseButtons_[i];
            if(mouseButtons_[i] >= INT_MAX)
                mouseButtons_[i] = INT_MAX;
            continue;
        }

        mouseButtons_[i] = 0;
    }
}

//---------------------------------------------------------------------------
// 終了
//---------------------------------------------------------------------------
void InputMouseExit()
{
    ;
}

//---------------------------------------------------------------------------
// 指定マウスボタンの1回だけ押下検証
//---------------------------------------------------------------------------
bool IsMouseOn(int mouseID)
{
    int tmp_mouseID = mouseID - 1;
    if(IsOverMouseNum(tmp_mouseID))
        return false;
    return (mouseButtons_[tmp_mouseID] == 1);
}

//---------------------------------------------------------------------------
// 指定キーが押されていない検証
//---------------------------------------------------------------------------
bool IsMouseRelease(int mouseID)
{
    int tmp_mouseID = mouseID - 1;
    if(IsOverMouseNum(tmp_mouseID))
        return false;
    return (mouseButtons_[tmp_mouseID] == 0);
}

//---------------------------------------------------------------------------
// 指定キーの長押し検証
//---------------------------------------------------------------------------
bool IsMouseRepeat(int mouseID)
{
    int tmp_mouseID = mouseID - 1;
    if(IsOverMouseNum(tmp_mouseID))
        return false;
    return (mouseButtons_[tmp_mouseID] > 1);
}

//---------------------------------------------------------------------------
// マウスのX座標 取得
//---------------------------------------------------------------------------
int GetMouseX()
{
    return mouseX_;
}

//---------------------------------------------------------------------------
// マウスのY座標 習得
//---------------------------------------------------------------------------
int GetMouseY()
{
    return mouseY_;
}
