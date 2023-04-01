#include "baseGame.h"

#include "glew.h"
#include "glfw3.h"
#include "window.h"
#include "renderer.h"
#include "input.h"
#include "collisionManager.h"
#include <random>
#include <iostream>

namespace engine
{
    baseGame::baseGame()
    {
        currentWindow = NULL;
        currentRenderer = NULL;
        currentInput = NULL;
        currentTimer = NULL;
        currentCollisionManager = NULL;
    }
    baseGame::~baseGame()
    {
        delete currentWindow;
        delete currentRenderer;
        delete currentInput;
        delete currentTimer;
    }
    bool baseGame::init_Internal(int windowSizeX, int windowSizeY, const char* windowName)
    {
        if (!glfwInit())
            return false;

        currentWindow = new window(windowSizeX, windowSizeY, windowName);
        if (!currentWindow->getGLFWwindow())
        {
            glfwTerminate();
            delete currentWindow;
            return false;
        }
        currentWindow->init();

        if (glewInit() != GLEW_OK) // tiene que ir despues de la creacion del contexto de glfw si o si
        {
            std::cout << "Glew error" << std::endl;
            return false;
        }

        currentRenderer = new renderer(currentWindow);

        currentInput = new input(currentWindow);

        currentCollisionManager = new collisionManager();

        currentTimer = new time();

        return true;
    }
    void baseGame::deinit_Internal()
    {
        glfwTerminate();
    }
    void baseGame::play(int windowSizeX, int windowSizeY, const char* windowName)
    {
        if(init_Internal(windowSizeX, windowSizeY, windowName))
        {
            init();
            while (!windowExitEvent())
            {
                glfwPollEvents();
                currentTimer->updateDeltaTime(getCurrentTime());
                update();
                currentInput->setOffset(glm::vec2(0, 0));
                //currentCollisionManager->updateCollisions();
                currentRenderer->startDraw();
                draw();
                currentRenderer->endDraw();
            }
            deInit();
            deinit_Internal();
        }
    }
    void baseGame::changeClearColor(glm::vec4 color)
    {
        currentRenderer->setClearColor(color);
    }
    bool baseGame::windowExitEvent()
    {
        return glfwWindowShouldClose(currentWindow->getGLFWwindow());
    }

    bool baseGame::isKeyPressed(int keycode)
    {
        return currentInput->isKeyPressed(keycode, currentWindow);
    }
    bool baseGame::isKeyDown(int keycode)
    {
        return currentInput->isKeyDown(keycode, currentWindow);
    }
    glm::vec2 baseGame::getMousePosition()
    {
        return currentInput->getMousePosition();
    }
    glm::vec2 baseGame::getMouseOffset()
    {
        return currentInput->getMouseOffSet();
    }

    double baseGame::getCurrentTime()
    {
        return glfwGetTime();
    }
    float baseGame::getRandomNumber(float min, float max)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(min, max);
        return dist(mt);
    }
    glm::vec4 baseGame::getRandomColor()
    {
        float r = getRandomNumber(0, 1);
        float g = getRandomNumber(0, 1);
        float b = getRandomNumber(0, 1);
        float a = getRandomNumber(0, 1);
        return glm::vec4(r, g, b, a);
    }
    void baseGame::addCollider(entity2D* entity, bool isStatic)
    {
        currentCollisionManager->addToCollisionList(entity, isStatic);
    }
    void baseGame::removeCollider(entity2D* entity)
    {
        currentCollisionManager->removeFromCollisionList(entity);
    }
    bool baseGame::hasCollider(entity2D* entity)
    {
        return currentCollisionManager->isInCollisionList(entity);
    }
    void baseGame::updateCollisions(engine::tileMap* tileMap)
    {
        currentCollisionManager->updateCollisionsInTileMap(tileMap);
    }
    float baseGame::lerp(float v0, float v1, float t)
    {
        return v0 + t * (v1 - v0);
    }
    glm::vec4 baseGame::lerp(glm::vec4 color1, glm::vec4 color2, float t)
    {
        float r = lerp(color1.r, color2.r, t);
        float g = lerp(color1.g, color2.g, t);
        float b = lerp(color1.b, color2.b, t);
        float a = lerp(color1.a, color2.a, t);
        return glm::vec4(r, g, b, a);
    }
}