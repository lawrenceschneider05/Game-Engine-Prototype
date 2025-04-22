#include "application.h"
#include <chrono>
#include <iostream>
#include "rendering/renderer.h"
#include "log/logger.h"
#include <string>
#include "input/input.h"

using std::to_string;

GameEngine::Application::Application()
{
    window = Window("Game Engine", screenWidth, screenHeight);
    camera = Camera(0.0f, screenWidth, 0.0f, screenHeight);

    game = new Game();
}

GameEngine::Application::~Application()
{
    Renderer::shutdown();
    delete game;
}

void GameEngine::Application::init()
{
    window.init(false);
    Renderer::init();
    Input::setWindowHandle(window);

    
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
    if (Input::isKeyPressed(GLFW_KEY_SPACE))
    {
        camera.ZoomOut(1 * dt);
    }
    if (Input::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
    {
        camera.ZoomOut(-1 * dt);
    }

    if (Input::isKeyPressed(GLFW_KEY_COMMA))
    {
        Renderer::setDebugMode(false);
    }
    else
    {
        Renderer::setDebugMode(true);
    }
    /*i32 camspeed = 500;
    
    if (Input::isKeyPressed(GLFW_KEY_W))
    {
        Logger::log(LOG_SUCCESS, "ok");
        camera.move({ 0, -camspeed * dt });
    }
    if (Input::isKeyPressed(GLFW_KEY_S))
    {
        camera.move({ 0, camspeed * dt });
    }
    if (Input::isKeyPressed(GLFW_KEY_A))
    {
        camera.move({ -camspeed * dt, 0 });
    }
    if (Input::isKeyPressed(GLFW_KEY_D))
    {
        camera.move({ camspeed * dt, 0 });
    }*/

    game->update(dt);
}

void GameEngine::Application::render()
{
    Renderer::beginScene(camera);
    game->render();
    Renderer::endScene();
}
