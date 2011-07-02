#ifndef CLIENTGAME_H
#define CLIENTGAME_H
#include <vector>


class NetworkingClient;
class Fleet;
class Interfacing;
class Planet;
class Player;

class ClientGame {
    std::vector<Planet *> planets;

    std::vector<Player *> players;

    std::vector<Fleet *> fleets;

    NetworkingClient *net;
public:
    ClientGame(const char *ip, int port = 45672);
    
    ~ClientGame();
    
    /**
     * Send a fleet of the specified amount from the source planet, heading towards a destination planet.
     */
    void launch_fleet(Planet &src, Planet &dest, int timestamp);
    void remove_fleet(Fleet *f);
    void launch_fleet(int pid1, int pid2, int timestamp);

    void add_planet(Planet *p);
    
    /**
     * Find a planet based on id
     */
    Planet *planet_from_id(int id);
    
    /**
     * Find the closest planet to a specified location.
     * If limit is specified, do not return a Planet further away than the squareroot of this.
     */
    Planet *find_nearest_planet(int x, int y, int limit = 0);

    void logic(Interfacing &in);
};

#endif
