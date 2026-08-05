#pragma once
#include <string>

class SongSelect {
public:
    std::string Open();

private:
    std::string GetFilePath();

private:
    wchar_t fileBuffer[260] = {};
    std::wstring filePath;
};