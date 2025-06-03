#include "managers/sceneManager.hpp"

void SceneManager::setCurrentScene(std::shared_ptr<Scene> scene) {
    if (currentScene) {
        currentScene->destroy();
    }
    currentScene = scene;
    currentScene->init();
}

std::shared_ptr<Scene> SceneManager::getCurrentScene() {
    return currentScene;
}