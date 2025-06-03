#pragma once

#include <vector>
#include <string>
#include <memory>
#include "scenes/scene.hpp"

struct SceneManager {
    std::shared_ptr<Scene> getCurrentScene();
    void setCurrentScene(std::shared_ptr<Scene> scene);

    std::vector<std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> currentScene = nullptr;
};
