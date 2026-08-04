#include "include/SongSelect.h"

#include <stdexcept>
#include <windows.h>
using namespace std;

string SongSelect::Open() {

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ZeroMemory(&fileBuffer, sizeof(fileBuffer));
    fileBuffer[0] = L'\0';

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = fileBuffer;
    ofn.nMaxFile = sizeof(fileBuffer);
    ofn.lpstrFilter = L"All\0*.*\0Mp3\0*.mp3\0\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = nullptr;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = nullptr;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_NOCHANGEDIR;

    if (GetOpenFileName(&ofn) != TRUE) {
        throw runtime_error("File selection cancelled or failed");
    }
    filePath = wstring(fileBuffer);
    return GetFilePath();
}

string SongSelect::GetFilePath()
{
    if (filePath.empty()) return {};

    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, filePath.c_str(), (int)filePath.size(), nullptr, 0, nullptr, nullptr);
    string result(sizeNeeded, 0);
    WideCharToMultiByte(CP_UTF8, 0, filePath.c_str(), (int)filePath.size(), &result[0], sizeNeeded, nullptr, nullptr);
    return result;
}

