#ifndef AUDIOVISUALIZER_SONG_SELECT_H
#define AUDIOVISUALIZER_SONG_SELECT_H
#include <string>
#include <windows.h>

class SongSelect {
    public:
    bool Open();

    std::string GetFilePath();

private:
    wchar_t FILEBUFFER[260];
    std::wstring FILEPATH;
};



#endif //AUDIOVISUALIZER_SONG_SELECT_H