#ifndef SFMLTANKS_TANK_H
#define SFMLTANKS_TANK_H

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <chrono>
#include <unordered_set>
#include <vector>
#include "Bullet.h"

namespace fs = std::filesystem;

class Map;

class Tank {
public:
    struct Position {
        double x{};
        double y{};
    };

    struct Speed {
        double x{};
        double y{};
    };

    enum class Direction {
        left,
        right,
        up,
        down,
    };

private:
    Position m_position{};
    Speed m_speed{};
    Direction m_direction{ Direction::right };

    sf::Image m_image{};
    sf::Texture m_texture{};
    sf::Sprite m_sprite{};

    bool m_isPlayer{};

    const Map& m_map;

    std::vector<Bullet> m_bullets;

    std::chrono::time_point<std::chrono::steady_clock> m_lastShoot;

public:
    Tank(bool isPlayer,const fs::path& path, const Map& map);

    const sf::Sprite& GetSprite() const noexcept;

    void Update(double deltaTime);
    void SetSpeed(Speed speed);
    void SetDirection(Direction direction);
    const Position& GetPosition() const noexcept;
    void Shoot();
    void DrawBullets(sf::RenderWindow& window, double deltaTime);


private:
    void SetSpriteRotate();
    bool CheckCollision(Position newPosition) const noexcept;

};


#endif //SFMLTANKS_TANK_H