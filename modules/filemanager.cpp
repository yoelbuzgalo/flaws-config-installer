#include "filemanager.h"
#include <iostream>
#include <string>
#include <filesystem>
#include <Windows.h>

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
    // Guard clause, checking if APB Directory or config directory path stored isn't empty so it won't download without valid path.
    if (this->APBDirectoryPath.empty() || this->configFilesPath.empty()){
        return false;
    }

    // Check if the config files path exists in system, if it doesn't - it'll download and install the config files remotely
    if (!fs::exists(this->configFilesPath)){
        std::cout << "No config files were detected. Proceeding to download the config files, please wait..." << std::endl;

        // DOWNLOAD PROCEDURE STARTS HERE
        try{
            // Creates the config directory
            if(fs::create_directory(this->configFilesPath)){
                std::cout << "Created a directory at " << fs::absolute(this->configFilesPath).string() << std::endl;

                std::cout << "Initializing download process..." << std::endl;
                // Proceeds to download the config files from URL
                if(this->downloadConfigFiles()){
                    std::cout << "Sucessfully downloaded the config files" << std::endl;
                
                    // If download was sucessfull, it will proceed to extract the downloaded zip file to the directory
                    if(this->extractConfigFiles()){
                        std::cout << "Successfully extracted the config files" << std::endl;
                        // If all is successful, it will not return and continue to install
                    } else {
                        throw("There was an error with extracting the config files");
                    }

                } else {
                    throw("There was an error trying to download the config files remotely.");
                }

            } else {
                throw("There was a problem with creating the directory");
            }
        } catch (const char* error){
            std::cout << error << std::endl;
            return false;
        }

    } else {
        std::cout << "Config file already exists! Skipping download process." << std::endl;
    }

    // INSTALLATION PROCEDURE HERE
    // TODO: Add here the copy (install) functionality
    return true;
}

bool FileManager::downloadConfigFiles(){
    // Gets the absolute config directory path and creates a file string path named flaswsconfig.zip for the downloader
    std::string configFilesPathString = fs::absolute(this->configFilesPath).string()+"flawsconfig.zip";
    // Convert strings to wide strings
    std::wstring tempFilePath = std::wstring(configFilesPathString.begin(), configFilesPathString.end());
    // Convert wide string to LPCWSTR
    LPCWSTR wideFilePath = tempFilePath.c_str();
    // Download URL in LPCWSTR format
    LPCWSTR downloadURL = L"https://github.com/flawsv/apb/releases/download/v1.4/Flaws.APB.Config.v1.4.zip";

    // A windows feature to download from url
    HRESULT hr = URLDownloadToFileW(NULL, downloadURL, wideFilePath, 0, NULL);
    if (SUCCEEDED(hr)){
        return true;
    }
    return false;
}

bool FileManager::extractConfigFiles(){
    // TODO: Add here ZIP extraction functionality
    return true;
}