#include "include/SongSelect.h"
#include <windows.h>

bool SongSelect::Open() {

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ZeroMemory(&FILEBUFFER, sizeof(FILEBUFFER));
    FILEBUFFER[0] = L'\0';

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = FILEBUFFER;
    ofn.nMaxFile = sizeof(FILEBUFFER);
    ofn.lpstrFilter = L"All\0*.*\0Mp3\0*.mp3\0\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_NOCHANGEDIR;

    if (GetOpenFileName(&ofn) == TRUE) {
        FILEPATH = std::wstring(FILEBUFFER);
        return true;
    } else {
        return false;
    }
}

std::string SongSelect::GetFilePath()
{
    if (FILEPATH.empty()) return {};

    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, FILEPATH.c_str(), (int)FILEPATH.size(), NULL, 0, NULL, NULL);
    std::string result(sizeNeeded, 0);
    WideCharToMultiByte(CP_UTF8, 0, FILEPATH.c_str(), (int)FILEPATH.size(), &result[0], sizeNeeded, NULL, NULL);
    return result;
}

