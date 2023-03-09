#include "Map.h"
#include <cmath>

using namespace std::literals;

Map::Map() {
    std::ifstream in{"../map.txt"};
    if(!in.is_open()) throw std::runtime_error{"Error : bad open map file"s};
    while(in) {
        std::string strBuf{};
        std::getline(in, strBuf);
        if(!in) break;
        m_map.push_back(strBuf);
    }
    in.close();


    for(std::size_t i{}; i < 2; ++i) {
        m_images[i].loadFromFile("../assets/MapObjects/"s + std::to_string(i) + ".png"s);
        m_textures[i].loadFromImage(m_images[i]);
    }
}

void Map::DrawMap(sf::RenderWindow &window) {
    for(std::size_t i{}; i < m_map.size(); ++i)
        for(std::size_t j{}; j < m_map[i].size(); ++j) {
            m_sprite.setTexture(m_textures[static_cast<std::size_t>(MapObject::road)]);
            m_sprite.setPosition(j * m_textures.back().getSize().x, i * m_textures.back().getSize().y);
            if(m_map[i][j] == '#') m_sprite.setTexture(m_textures[static_cast<std::size_t>(MapObject::barrier)]);
            window.draw(m_sprite);
        }
}

std::size_t Map::GetMapHeight() const noexcept {
    return m_textures.back().getSize().y * m_map.size();
}

std::size_t Map::GetMapWidth() const noexcept {
    return m_textures.back().getSize().x * m_map[0].size();
}

char Map::GetTile(Tank::Position position) const noexcept {
    std::size_t row{static_cast<std::size_t>(position.y / m_textures.back().getSize().y)};
    std::size_t col{static_cast<std::size_t>(position.x / m_textures.back().getSize().x)};

    if(row >= m_map.size()) return '#';
    if(col >= m_map[0].size()) return '#';

    return m_map[row][col];
}
