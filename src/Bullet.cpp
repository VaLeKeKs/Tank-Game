#include "Bullet.h"
#include "Tank.h"
#include "Map.h"

Bullet::Bullet(Position position, Direction direction, const Map& map) : m_position{position}, m_direction{direction}, m_map{map} {
    m_image.loadFromFile("../assets/Bullets/YellowBullet.png");
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture.getSize().x / 2.0, m_texture.getSize().y / 2.0);
    m_sprite.setPosition(position.x, position.y);
    SetSpriteRotate();
    SetSpeed();
}

const sf::Sprite &Bullet::GetSprite() const noexcept {
    return m_sprite;
}

void Bullet::Update(double deltaTime) {
    Position newPosition{m_position.x + m_speed.x * deltaTime / 1000, m_position.y + m_speed.y * deltaTime / 1000};
    if(CheckCollision(newPosition)) m_position = newPosition;
    else {
        m_isAlive = false;
        return;
    }
    m_sprite.setPosition(static_cast<float>(m_position.x), static_cast<float>(m_position.y));
}

void Bullet::SetSpriteRotate() {
    switch (m_direction) {
        case Direction::left:
            m_sprite.setRotation(-90);
            break;
        case Direction::right:
            m_sprite.setRotation(90);
            break;
        case Direction::up:
            m_sprite.setRotation(0);
            break;
        case Direction::down:
            m_sprite.setRotation(180);
            break;
    }
}

bool Bullet::CheckCollision(Bullet::Position newPosition) const noexcept {
    if (m_map.GetTile(Tank::Position{newPosition.x, newPosition.y}) == '#') return false;
    return true;
}

bool Bullet::IsAlive() const noexcept {
    return m_isAlive;
}

void Bullet::SetSpeed() {
    switch (m_direction) {
        case Direction::left:
            m_speed = {-600, 0};
            break;
        case Direction::right:
            m_speed = {600, 0};
            break;
        case Direction::up:
            m_speed = {0, -600};
            break;
        case Direction::down:
            m_speed = {0, 600};
            break;
    }
}

Bullet &Bullet::operator=(const Bullet &bullet) {
    this->m_image = bullet.m_image;
    this->m_texture = bullet.m_texture;
    this->m_sprite = bullet.m_sprite;
    m_sprite.setTexture(m_texture);
    this->m_position = bullet.m_position;
    this->m_speed = bullet.m_speed;
    this->m_direction = bullet.m_direction;
    this->m_isAlive = bullet.m_isAlive;

    return *this;
}

Bullet::Bullet(const Bullet &bullet) : m_image{bullet.m_image}, m_texture{bullet.m_texture}, m_sprite{bullet.m_sprite},
                                       m_position{bullet.m_position}, m_speed{bullet.m_speed}, m_direction{bullet.m_direction}, m_isAlive{bullet.m_isAlive}, m_map{bullet.m_map} {
    m_sprite.setTexture(m_texture);
}