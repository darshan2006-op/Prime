#include<iostream>
#include"Core/Application.h"
#include"Core/Log.h" 

int main() {
    prm::Logger::init();
    auto app = prm::getClientApplication();
    app->onInit();
    
    while (app->isRunning())
    {
        app->onUpdate();
    }

    app->onDestroyed();
    return 0;
}