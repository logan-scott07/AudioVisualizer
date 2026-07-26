#pragma once
#include <string>

class SongSelect {
    public:
    bool Open();

    std::string GetFilePath();

private:
    wchar_t FILEBUFFER[260];
    std::wstring FILEPATH;
};