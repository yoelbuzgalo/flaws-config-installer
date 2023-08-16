#ifndef APP_H
#define APP_H

#include "./modules/filemanager.h"

class App{
    public:
        App();
        ~App();
        void start();
    private:
        FileManager* fileManager;
};

#endif //APP_H