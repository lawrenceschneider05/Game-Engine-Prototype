#include "application.h"
#include <chrono>
#include <iostream>
#include "rendering/renderer.h"
#include "log/logger.h"
#include <string>

using std::to_string;

GameEngine::Application::Application()
{
    window = Window("Game Engine", screenWidth, screenHeight);
    camera = Camera({ screenWidth, screenHeight });
    camera.setPosition({ 0,0 });
    camera.setZoom(1.0f);
}

GameEngine::Application::~Application()
{
    Renderer::shutdown();
}

void GameEngine::Application::init()
{
    window.init();
    Renderer::init();
}

void GameEngine::Application::run()
{
    const i32 TARGET_FPS = 60;
    const f64 TARGET_FRAME_TIME = 1.0 / 60.0;  // 60 FPS
    auto lastRenderTime = std::chrono::high_resolution_clock::now();
    auto lastUpdateTime = std::chrono::high_resolution_clock::now();
    int renderFrameCount = 0;
    int updateFrameCount = 0;
    auto lastRenderPrintTime = std::chrono::high_resolution_clock::now();
    auto lastUpdatePrintTime = std::chrono::high_resolution_clock::now();

    while (!window.shouldClose())
    {
        window.pollEvents();

        // Update loop (runs as fast as possible)
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> deltaTime = currentTime - lastUpdateTime;
        lastUpdateTime = currentTime;

        // Call update with the delta time
        update(deltaTime.count());
        updateFrameCount++;

        // Check time for rendering
        auto elapsedTime = std::chrono::high_resolution_clock::now() - lastRenderTime;
        if (elapsedTime.count() >= TARGET_FRAME_TIME) {
            // Clear screen and render
            window.clear(152 / 255.0, 245 / 255.0, 249 / 255.0, 1);
            render();
            window.swapBuffers();
            lastRenderTime = std::chrono::high_resolution_clock::now();
            renderFrameCount++;
        }

        // Print FPS for render and update every second
        auto currentPrintTime = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration<double>(currentPrintTime - lastRenderPrintTime).count() >= 1.0) {
            std::cout << "Render FPS: " << renderFrameCount << std::endl;
            renderFrameCount = 0;
            lastRenderPrintTime = currentPrintTime;
        }

        if (std::chrono::duration<double>(currentPrintTime - lastUpdatePrintTime).count() >= 1.0) {
            std::cout << "Update FPS: " << updateFrameCount << std::endl;
            updateFrameCount = 0;
            lastUpdatePrintTime = currentPrintTime;
        }
    }
}

void GameEngine::Application::update(f64 dt)
{
}

void GameEngine::Application::render()
{
    Renderer::beginScene(camera);
    Renderer::drawQuad({ 0,0 }, { 100,100 }, { 0,0,0,1 });
    Renderer::endScene();
}
