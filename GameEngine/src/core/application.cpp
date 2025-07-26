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

    game = new Game(camera);
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
    constexpr i32 TARGET_FPS = 60;
    constexpr double TARGET_FRAME_TIME = 1.0 / TARGET_FPS;

    using Clock = std::chrono::high_resolution_clock;
    using Duration = std::chrono::duration<double>;

    auto lastRenderTime = Clock::now();
    auto lastUpdateTime = Clock::now();

    int renderFrameCount = 0;
    int updateFrameCount = 0;

    auto lastRenderPrintTime = Clock::now();
    auto lastUpdatePrintTime = Clock::now();

    while (!window.shouldClose())
    {
        window.pollEvents();

        // Update loop (runs as fast as possible)
        auto currentTime = Clock::now();
        Duration deltaTime = currentTime - lastUpdateTime;
        lastUpdateTime = currentTime;

        update(deltaTime.count());
        updateFrameCount++;

        // Render loop (capped to target FPS)
        Duration timeSinceLastRender = Clock::now() - lastRenderTime;
        if (timeSinceLastRender.count() >= TARGET_FRAME_TIME) {
            window.clear(152 / 255.0f, 245 / 255.0f, 249 / 255.0f, 1);
            render(deltaTime.count());
            window.swapBuffers();

            lastRenderTime += std::chrono::duration_cast<Clock::duration>(Duration(TARGET_FRAME_TIME));
            renderFrameCount++;
        }

        // Print FPS every second
        auto currentPrintTime = Clock::now();

        if ((currentPrintTime - lastRenderPrintTime) >= std::chrono::seconds(1)) {
            std::cout << "Render FPS: " << renderFrameCount << std::endl;
            renderFrameCount = 0;
            lastRenderPrintTime = currentPrintTime;
        }

        if ((currentPrintTime - lastUpdatePrintTime) >= std::chrono::seconds(1)) {
            //std::cout << "Update FPS: " << updateFrameCount << std::endl;
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
    i32 camspeed = 500;
    
    if (Input::isKeyPressed(GLFW_KEY_UP))
    {
        camera.move({ 0, camspeed * dt });
    }
    if (Input::isKeyPressed(GLFW_KEY_DOWN))
    {
        camera.move({ 0, -camspeed * dt });
    }
    if (Input::isKeyPressed(GLFW_KEY_LEFT))
    {
        camera.move({ camspeed * dt, 0 });
    }
    if (Input::isKeyPressed(GLFW_KEY_RIGHT))
    {
        camera.move({ -camspeed * dt, 0 });
    }

    game->update(dt);
}

void GameEngine::Application::render(f64 dt)
{
    Renderer::beginScene(camera);
    game->render(dt);
    //Renderer::drawQuad({ 0,0 }, { 4,4 }, { 0,0,0,1.0f });
    Renderer::endScene();
}
