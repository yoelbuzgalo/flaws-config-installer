#include "app.h"
#include <iostream>

int main(){
    App* app = new App();
    app->start();
    delete app;
    return 0;
}