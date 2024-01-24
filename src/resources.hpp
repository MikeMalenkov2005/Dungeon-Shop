#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "framework.hpp"

#include "scene.hpp"
#include "title.hpp"

#include "shader.hpp"

struct Resources {
    Resources(std::filesystem::path& path);
    ~Resources();
    struct {
        Shader* sprite;
    } shaders;
    struct {
        TitleScreen* title_screen;
    } scenes;
};

const Resources* GetGlobalResources();

#endif
