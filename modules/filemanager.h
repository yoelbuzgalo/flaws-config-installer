#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class FileManager {
    public:
        void installConfigFiles();
        bool setAPBFilePath(std::string path);
        fs::path getAPBFilePath();
    private:
        fs::path filePath;
};

#endif // FILEMANAGER_H