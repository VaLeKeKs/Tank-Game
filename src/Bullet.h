#ifndef SFMLTANKS_BULLET_H
#define SFMLTANKS_BULLET_H

#include <SFML/Graphics.hpp>
#include <filesystem>

namespace fs = std::filesystem;
class Map;
class Bullet {
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
    sf::Image m_image{};
    sf::Texture m_texture{};
    sf::Sprite m_sprite{};

    Position m_position{};
    Speed m_speed{};
    Direction m_direction{};

    bool m_isAlive{ true };

    const Map& m_map;

public:
    Bullet(Position position, Direction direction, const Map& map);
    const sf::Sprite& GetSprite() const noexcept;

    void Update(double deltaTime);
    bool IsAlive() const noexcept;

    Bullet(const Bullet& bullet);
    Bullet& operator=(const Bullet& bullet);

private:
    void SetSpriteRotate();
    bool CheckCollision(Position newPosition) const noexcept;
    void SetSpeed();
};


#endif //SFMLTANKS_BULLET_H
