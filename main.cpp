#include <SFML/Config.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include <array>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <utility>

#include "SandTypes.hpp"
#include "sim.hpp"
#include "updates.hpp"

static sf::Texture sandbox_texture;

static const std::array<std::function<void(int, int)>, 256> updates = []{   // replaces a hashmap, a 256 entries table is not memory heavy enough for me to consider an unordered_map
    std::array<std::function<void(int, int)>, 256> ret;

    ret.fill([](int, int){return;});
    ret[Sand] = update_sand_at;
    ret[Water] = update_water_at;
    return ret;
}();

static void update_sandbox() {
    for (int y = SIM_HEIGHT - 1; y >= 0; y--) {
        // Makes the update left to right of right to left in function of the line to prevent on side bias
        for (int x = (y % 2) * (SIM_WIDTH - 1); x != !(y % 2) * (SIM_WIDTH + 1) - 1; x += !(y % 2) * 2 - 1) {
            if (get_particle_at(x, y)) {
                updates[get_particle_at(x, y)](x, y);
            }
        }
    }
}

static uint32_t get_sand_color(unsigned char type) {    // ABGR ordered
    switch (type) { 
        case SandTypes::Air: return     0;              // 100% transparent black
        case SandTypes::Sand: return    0xff00fafa;
        case SandTypes::Water: return   0xff772200;
        case SandTypes::Wall: return    0xff000000;
        default: return                 0xfffa00fa;     // Unknown (magenta)
    }
}

static void update_texture() {
    static std::array<uint32_t, SIM_WIDTH * SIM_HEIGHT> pixels;
    for (unsigned int index = 0; index < sandbox.size(); index++) {
        pixels[index] = get_sand_color(get_particle_at(index % SIM_WIDTH, index / SIM_WIDTH));
    }
    sandbox_texture.update(reinterpret_cast<sf::Uint8 *>(pixels.data()));
}

static std::array<SandTypes, 9> primitives = {Air, Sand, Water, Wall, Air, Air, Air, Air, Air};
static SandTypes drawing_type = SandTypes::Air;
static bool drawing = false;

static void handle_events(sf::RenderWindow &window) {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            drawing = true;
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            drawing = false;
        if (event.type == sf::Event::KeyPressed && sf::Keyboard::Key::Num0 <= event.key.code && sf::Keyboard::Key::Num9 >= event.key.code)
            drawing_type = primitives[event.key.code - sf::Keyboard::Key::Num0];
    }
}

static std::pair<int, int> get_sim_coords(int x, int y, sf::RenderWindow &window) {
    return {(float)x / (float)window.getSize().x * SIM_WIDTH, (float)y / (float)window.getSize().y * SIM_HEIGHT};
}

static void draw(sf::RenderWindow &window) {
    const int radius = 8;
    std::pair<int, int> pos;

    for (int x = -radius / 2; x < radius / 2; x++)
        for (int y = -radius / 2; y < radius / 2; y++)
            if (x * x + y * y <= radius * radius) {
                pos = get_sim_coords(sf::Mouse::getPosition(window).x + x, sf::Mouse::getPosition(window).y + y, window);
                set_particle_at(pos.first, pos.second, drawing_type);
            }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1080, 720, sizeof(uint32_t) * 8), "Sandbox", sf::Style::Resize | sf::Style::Close);
    sf::Sprite sprite;

    sandbox_texture.create(SIM_WIDTH, SIM_HEIGHT);
    sprite.setTexture(sandbox_texture);
    sprite.setScale(2.0, 2.0);
    window.setFramerateLimit(120);
    while (window.isOpen()) {
        handle_events(window);
        if (drawing)
            draw(window);
        window.clear(sf::Color(0x777777FF));
        update_sandbox();
        update_texture();
        window.draw(sprite);
        window.display();
    }
}
