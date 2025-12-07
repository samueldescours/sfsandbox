#include <cstdlib>

#include "updates.hpp"
#include "SandTypes.hpp"
#include "sim.hpp"

static char get_random_direction() {
    return ((std::rand() >> 7) & 1) * 2 - 1;
}

void update_sand_at(int x, int y) {
    int direction = get_random_direction();

    if (is_fluid(get_particle_at(x, y + 1))) {
        swap_particles(x, y, x, y + 1);
        return;
    }
    if (is_fluid(get_particle_at(x + direction, y + 1))) {
        swap_particles(x, y, x + direction, y + 1);
        return;
    }
    if (is_fluid(get_particle_at(x - direction, y + 1))) {
        swap_particles(x, y, x - direction, y + 1);
        return;
    }
}

void update_water_at(int x, int y) {
    int direction = get_random_direction();

    if (get_particle_at(x, y + 1) < SandTypes::Water) {
        swap_particles(x, y, x, y + 1);
        return;
    }
    if (get_particle_at(x + direction, y + 1) < SandTypes::Water) {
        swap_particles(x, y, x + direction, y + 1);
        return;
    }
    if (get_particle_at(x - direction, y + 1) < SandTypes::Water) {
        swap_particles(x, y, x - direction, y + 1);
        return;
    }
    if (get_particle_at(x + direction, y) < SandTypes::Water) {
        swap_particles(x, y, x + direction, y);
        return;
    }
    if (get_particle_at(x - direction, y) < SandTypes::Water) {
        swap_particles(x, y, x - direction, y);
        return;
    }
}


