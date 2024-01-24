#include "resources.hpp"

Resources::Resources(std::filesystem::path& path) {
    this->shaders.sprite = new Shader(path / "sprite.vert", path / "sprite.frag");
    this->scenes.title_screen = new TitleScreen();
}

Resources::~Resources() {
    delete this->shaders.sprite;
    delete this->scenes.title_screen;
}
