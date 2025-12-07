#include "sim.hpp"
#include "SandTypes.hpp"

bool is_fluid(SandTypes type) {
    switch (type) {
        case Air:
        case Water:
            return true;
        default:
            return false;
    }
}

SandTypes get_particle_at(unsigned int x, unsigned int y) {
    if (x >= SIM_WIDTH || y >= SIM_HEIGHT)
        return SandTypes::Wall;
    return static_cast<SandTypes>(sandbox[y * SIM_WIDTH + x]);
}

void set_particle_at(unsigned int x, unsigned int y, SandTypes type) {
    if (x >= SIM_WIDTH || y >= SIM_HEIGHT)
        return;
    sandbox[y * SIM_WIDTH + x] = type;
}

void swap_particles(unsigned int x, unsigned int y, unsigned int new_x, unsigned int new_y) {
    SandTypes temp = get_particle_at(new_x, new_y);
    set_particle_at(new_x, new_y, get_particle_at(x, y));
    set_particle_at(x, y, temp);
}

