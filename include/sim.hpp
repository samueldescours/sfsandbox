#include <array>

#include "SandTypes.hpp"

#define SIM_WIDTH 540
#define SIM_HEIGHT 360

[[maybe_unused]]
static std::array<unsigned char, SIM_WIDTH * SIM_HEIGHT> sandbox{};

bool is_fluid(SandTypes type);
SandTypes get_particle_at(unsigned int x, unsigned int y);
void set_particle_at(unsigned int x, unsigned int y, SandTypes type);
void swap_particles(unsigned int x, unsigned int y, unsigned int new_x, unsigned int new_y);
