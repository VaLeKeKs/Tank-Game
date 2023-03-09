#include "Tank.h"
#include "Map.h"
#include "Bullet.h"

using namespace std::literals;

Tank::Tank(bool isPlayer, const fs::path &path, const Map &map) : m_isPlayer{isPlayer}, m_map{map} {
    m_image.loadFromFile(path);
    m_texture.loadFromImage(m_image);
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture.getSize().x / 2.0, m_texture.getSize().y / 2.0);
    m_sprite.setScale(m_sprite.getScale().x * 0.7, m_sprite.getScale().y * 0.7);
    m_position = {m_texture.getSize().x * 0.7 / 2.0 + 2560, m_texture.getSize().y * 0.7 / 2.0 + 768};
}

const sf::Sprite &Tank::GetSprite() const noexcept {
    return m_sprite;
}

void Tank::Update(double deltaTime) {
    Position newPosition{m_position.x + m_speed.x * deltaTime / 1000, m_position.y + m_speed.y * deltaTime / 1000};
    if(CheckCollision(newPosition)) m_position = newPosition;

    m_sprite.setPosition(static_cast<float>(m_position.x), static_cast<float>(m_position.y));
    SetSpriteRotate();
}

void Tank::SetSpeed(Tank::Speed speed) {
    m_speed = speed;
}

void Tank::SetSpriteRotate() {
    switch (m_direction) {
        case Direction::left:
            m_sprite.setRotation(90);
            break;
        case Direction::right:
            m_sprite.setRotation(-90);
            break;
        case Direction::up:
            m_sprite.setRotation(180);
            break;
        case Direction::down:
            m_sprite.setRotation(0);
            break;
    }
}

void Tank::SetDirection(Tank::Direction direction) {
    m_direction = direction;
}

const Tank::Position &Tank::GetPosition() const noexcept {
    return m_position;
}

bool Tank::CheckCollision(Position newPosition) const noexcept {
    if (m_map.GetTile(newPosition) == '#') return false;
    return true;
}


void Tank::Shoot() {
    if(std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - m_lastShoot) <= 2s) return;
    m_bullets.emplace_back(Bullet::Position{m_position.x, m_position.y}, static_cast<Bullet::Direction>(m_direction), m_map);
    m_lastShoot = std::chrono::steady_clock::now();
}

void Tank::DrawBullets(sf::RenderWindow& window, double deltaTime) {
    for(auto& bullet : m_bullets) bullet.Update(deltaTime);
    std::erase_if(m_bullets, [](Bullet& bullet){
        return !bullet.IsAlive();
    });

    for(auto& bullet : m_bullets) window.draw(bullet.GetSprite());

}