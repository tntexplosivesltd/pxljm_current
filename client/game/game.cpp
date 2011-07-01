#include <algorithm>
#include <functional>

#include "game.hpp"

#include "fleet.hpp"
#include "planet.hpp"


ClientGame::ClientGame() {}

ClientGame::~ClientGame() {}

void ClientGame::launch_fleet(Planet &src, Planet &dest) {
    Fleet *f = src.launch_fleet(dest);
    // TODO Inform networking of fleet dispatch
}

struct pid : std::binary_function <Planet *, int, bool> {
    bool operator () (const Planet * const p, int id) const {
        return p->get_id() == id;
    }
};

Planet *ClientGame::planet_from_id(int id) {
    std::vector<Planet *>::iterator p = std::find_if(planets.begin(), planets.end(), std::bind2nd(pid(), id));
    return p == planets.end() ? 0 : *p;
}

struct SData {
    int x, y, limit;
    SData(int vx, int vy, int vlimit) : x(vx), y(vy), limit(vlimit) {}
};

Planet *ClientGame::find_nearest_planet(int x, int y, int limit) {
    int min_d2, d2, dx, dy;
    Planet *p = 0;
    for (std::vector<Planet *>::iterator it = planets.begin(), it_end = planets.end(); it != it_end; ++it) {
        dx = std::abs((*it)->get_x() - x);
        dy = std::abs((*it)->get_y() - y);
        d2 = dx*dx + dy*dy;
        if ((!p || d2 < min_d2) && d2 < limit)
            p = *it;
    }
    return p;
}
