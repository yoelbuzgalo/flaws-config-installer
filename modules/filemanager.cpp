#include "filemanager.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <Windows.h>
#include <urlmon.h>

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
        this->APBDirectoryPath = queryPath;
        return true;
    }
    return false;
}

fs::path FileManager::getAPBDirectoryPath(){
    return this->APBDirectoryPath;
}

bool FileManager::installConfigFiles(){
    // Guard clause, checking if APB Directory or config files path isn't empty so it won't download without valid path.
    if (this->APBDirectoryPath.empty() || this->configFilesPath.empty()){
        return false;
    }

    // Check if the config files path exists in system, if it doesn't - it'll install the config files remotely
    if (!fs::exists(this->configFilesPath)){
        std::cout << "No config files were detected. Proceeding to download the config files, please wait..." << std::endl;
        if(this->downloadConfigFiles()){
            std::cout << "Sucessfully downloaded the config files, now installing them" << std::endl;
        } else {
            std::cout << "There was an error trying to download the config files remotely. Aborting..." << std::endl;
            return false;
        }
    }
    
    // TODO: Add here the copy functionality
    return true;
}

bool FileManager::downloadConfigFiles(){
    std::string configFilesPathString = fs::absolute(this->configFilesPath).string();
    std::string downloadURLString = "https://github.com/flawsv/apb/releases/download/v1.4/Flaws.APB.Config.v1.4.zip";

    // Convert strings to wide strings
    std::wstring tempFilePath = std::wstring(configFilesPathString.begin(), configFilesPathString.end());
    std::wstring tempDownloadURL = std::wstring(downloadURLString.begin(), downloadURLString.end());

    // Convert wide string to LPCWSTR
    LPCWSTR wideFilePath = tempFilePath.c_str();
    LPCWSTR wideDownloadURL = tempDownloadURL.c_str();

    // A windows feature to download from url
    if (S_OK == URLDownloadToFile(NULL, wideDownloadURL, wideFilePath, 0, NULL)){
        std::cout << "Successfully downloaded the config files";
        return true;
    }
    return false;
}