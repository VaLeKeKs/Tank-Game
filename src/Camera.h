#ifndef SFMLTANKS_VIEW_H
#define SFMLTANKS_VIEW_H
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Tank.h"

class View {
private:
    sf::View m_view{};
    const Map& m_map;
public:
    explicit View(const Map& map);

    const sf::View& GetView() const noexcept;
    void UpdateCamera(Tank::Position position);
};


#endif //SFMLTANKS_VIEW_H

