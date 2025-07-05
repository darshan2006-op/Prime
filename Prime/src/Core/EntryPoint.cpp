#include<iostream>
#include<chrono>
#include"Core/Application.h"
#include"Core/Log.h" 

int main() {
    prm::Logger::init();
    auto app = prm::getClientApplication();
    app->onInit();
    
    auto start = std::chrono::high_resolution_clock::now();

    while (app->isRunning())
    {
        auto end = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration<float>(end - start).count();
        start = end;
        app->onUpdate(dt);
    }

    app->onDestroyed();
    return 0;
}