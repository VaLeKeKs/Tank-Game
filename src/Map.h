
#ifndef SFMLTANKS_MAP_H
#define SFMLTANKS_MAP_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <array>
#include <unordered_map>
#include "Tank.h"

class Map {
private:
    std::vector<std::string> m_map{};

    std::array<sf::Image, 2> m_images{};
    std::array<sf::Texture, 2> m_textures{};

    sf::Sprite m_sprite{};

    enum class MapObject {
        barrier,
        road,
    };

public:
    Map();

    void DrawMap(sf::RenderWindow& window);
    std::size_t GetMapHeight() const noexcept;
    std::size_t GetMapWidth() const noexcept;

    char GetTile(Tank::Position position) const noexcept;
};

#endif //SFMLTANKS_MAP_H