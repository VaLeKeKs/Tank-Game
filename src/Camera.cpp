#include "Camera.h"

View::View(const Map &map) : m_map{map}, m_view{sf::FloatRect{0,0, 800,600} } {}

const sf::View &View::GetView() const noexcept { return m_view; }

void View::UpdateCamera(Tank::Position position) {
    double xView{position.x};
    double yView{position.y};

    if(position.y < m_view.getSize().y / 2) yView = m_view.getSize().y / 2;
    else if(position.y > m_map.GetMapHeight() - m_view.getSize().y / 2) yView = m_map.GetMapHeight() - m_view.getSize().y / 2;

    if(position.x < m_view.getSize().x / 2) xView = m_view.getSize().x / 2;
    else if (position.x > m_map.GetMapWidth() - m_view.getSize().x / 2) xView = m_map.GetMapWidth() - m_view.getSize().x / 2;

    m_view.setCenter(xView, yView);
}