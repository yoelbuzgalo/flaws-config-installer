#include "app.h"
#include "./modules/filemanager.h"
#include <iostream>
#include <string>

// Initializes the file manager
App::App(){
    std::cout << "Starting flaws config installer app..." << std::endl;
    this->fileManager = new FileManager();
}

// Destructor to delete the fileManager object
App::~App(){
    delete this->fileManager;
};

void App::start(){
    
    // Requests the user to enter the APB file directory
    std::cout << "Please enter the APB file directory\ne.g. for most users: C:/Program Files (x86)/Steam/steamapps/common/APB Reloaded" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    
    //Checks if the input is empty or not.
    if (input.empty()){
        std::cout<<"Invalid input, please try again."<<std::endl;
        return;
    }

    // Sets the file path, it will return true if successful
    if(this->fileManager->setAPBFilePath(input)){
        std::cout << "Successfully set the file path to: " << this->fileManager->getAPBDirectoryPath().string() << std::endl;
        std::cout << "Please confirm that the file path is correct as shown above. Proceed with config installation? (y/n)" << std::endl;
        
        char cautionInput;
        std::cin >> cautionInput;
        std::cin.ignore();

        if (cautionInput != 'y'){
            std::cout << "Aborting..." << std::endl;
            return;
        }

        // If user confirms the config installation, it'll call the installConfigFiles function, upon completion itll return true.
        if(this->fileManager->installConfigFiles()){
            std::cout << "Successfully installed the config files" << std::endl;
        } else {
            std::cout << "There was an error trying to install the config files" << std::endl;
        }
        return;
    }

    std::cout << "Failed setting the APB file path" << std::endl;
    return;
}