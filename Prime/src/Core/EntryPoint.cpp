#include<iostream>
#include"Core/Application.h"

int main() {
    auto app = prm::getClientApplication();
    app->onInit();
    
    while (app->isRunning())
    {
        app->onUpdate();
    }

    app->onDestroyed();
    return 0;
}