#include "TitleBar.h"

TitleBar::TitleBar(Window &window) : window(window) {
    hwnd = window.GetHWND();
}

void TitleBar::Initialize() {
    LONG style = GetWindowLong(hwnd, GWL_STYLE);

    style &= ~WS_CAPTION;
    style &= ~WS_THICKFRAME;

    SetWindowLong(hwnd, GWL_STYLE, style);

    SetWindowPos(
        hwnd,nullptr,
        0,0,
        0,0,SWP_NOMOVE | SWP_NOSIZE |
        SWP_NOZORDER | SWP_FRAMECHANGED);
}
