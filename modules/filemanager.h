#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class FileManager {
    public:
        bool installConfigFiles();
        bool downloadConfigFiles();
        bool setAPBFilePath(std::string path);
        fs::path getAPBDirectoryPath();
    private:
        fs::path APBDirectoryPath;
        fs::path configFilesPath = "../config.zip";
};

#endif // FILEMANAGER_H