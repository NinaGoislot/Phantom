#include "managers/sceneManager.hpp"

void SceneManager::setCurrentScene(std::shared_ptr<Scene> scene)
{
    if (currentScene)
    {
        try
        {
            currentScene->destroy();
            std::cout << "[SceneManager] Ancienne scene detruite." << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "[SceneManager] Erreur lors de la destruction de la scene précédente : " << e.what() << std::endl;
        }
    }
    // currentScene = scene;
    currentScene = std::move(scene);

    if (!currentScene)
    {
        std::cerr << "[SceneManager] La nouvelle scene est nulle." << std::endl;
        return;
    }
    try {
        currentScene->init();
        std::cout << "[SceneManager] New scene initialized" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[SceneManager] New scene initializatiion failure : " << e.what() << std::endl;
    }
}

std::shared_ptr<Scene> SceneManager::getCurrentScene()
{
    return currentScene;
}