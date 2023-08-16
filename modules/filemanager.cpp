#include "filemanager.h"
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

bool FileManager::setAPBFilePath(std::string path){

    fs::path queryPath = path;
    fs::path APBGame = queryPath/"APBGame";
    fs::path Binaries = queryPath/"Binaries";
    fs::path Engine = queryPath/"Engine";

    bool isValidPath = fs::exists(queryPath);
    bool isDirectory = fs::is_directory(queryPath);
    bool validAPBFiles = fs::exists(APBGame) && fs::exists(Binaries) && fs::exists(Engine);
    
    if (isValidPath && isDirectory && validAPBFiles){
        this->filePath = queryPath;
        return true;
    }
    return false;
}

fs::path FileManager::getAPBFilePath(){
    return this->filePath;
}

void FileManager::installConfigFiles(){
    
}