#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include <cstdlib>
#include <ctime>
#include <functional>

#include "SandTypes.hpp"
#include "sim.hpp"
#include "updates.hpp"

static sf::Texture sandbox_texture;

static const std::array<std::function<void(int, int)>, 256> updates = []{
    std::array<std::function<void(int, int)>, 256> ret;

    ret.fill([](int, int){return;});
    ret[Sand] = update_sand_at;
    ret[Water] = update_water_at;
    return ret;
}();



static void update_sandbox() {
    for (int y = SIM_HEIGHT - 1; y >= 0; y--) {
        for (int x = (y % 2) * (SIM_WIDTH - 1); x != !(y % 2) * (SIM_WIDTH + 1) - 1; x += !(y % 2) * 2 - 1) {
            if (get_particle_at(x, y)) {
                updates[get_particle_at(x, y)](x, y);
            }
        }
    }
}

static uint32_t get_sand_color(unsigned char type) {
    switch (type) {
        case SandTypes::Air: return     0;
        case SandTypes::Sand: return    0xff00fafa;
        case SandTypes::Water: return   0xff772200;
        case SandTypes::Wall: return    0xff000000;
        default: return                 0xfffa00fa;
    }
}

static void update_texture() {
    static std::array<uint32_t, SIM_WIDTH * SIM_HEIGHT> pixels;
    for (unsigned int index = 0; index < sandbox.size(); index++) {
        pixels[index] = get_sand_color(get_particle_at(index % SIM_WIDTH, index / SIM_WIDTH));
    }
    sandbox_texture.update(reinterpret_cast<sf::Uint8 *>(pixels.data()));
}

static void handle_events(sf::RenderWindow &window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1080, 720, sizeof(uint32_t) * 8), "Sandbox", sf::Style::Resize | sf::Style::Close);
    sf::Sprite sprite;

    std::srand(std::time(nullptr));
    for (unsigned int index = 0; index < 2500; index ++) {
        set_particle_at(150 + index % 50, index / 50, (std::rand() % 2 == 1) ? SandTypes::Water : SandTypes::Sand);
    }
    for (unsigned int index = 0; index < 50; index ++) {
        set_particle_at(index, 100, SandTypes::Wall);
    }
    sandbox_texture.create(SIM_WIDTH, SIM_HEIGHT);
    sprite.setTexture(sandbox_texture);
    sprite.setScale(2.0, 2.0);
    window.setFramerateLimit(120);
    while (window.isOpen()) {
        handle_events(window);
        window.clear(sf::Color(0x777777FF));
        update_sandbox();
        update_texture();
        window.draw(sprite);
        window.display();
    }
}
