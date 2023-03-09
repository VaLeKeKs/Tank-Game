#include "Tank.h"
#include "Map.h"
#include "Camera.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

using namespace std::literals;

int main() {
    try {
        sf::RenderWindow window{sf::VideoMode{800, 600}, "TankGame"};
        window.setFramerateLimit(60);

        Map map{};
        Tank tank{true, "../assets/Tank/YellowTank.png", map};
        View view{ map };
        auto timeNow{ std::chrono::steady_clock::now() };
        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                tank.SetSpeed({100, 0});
                tank.SetDirection(Tank::Direction::right);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                tank.SetSpeed({0, -100});
                tank.SetDirection(Tank::Direction::up);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                tank.SetSpeed({0, 100});
                tank.SetDirection(Tank::Direction::down);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                tank.SetSpeed({-100, 0});
                tank.SetDirection(Tank::Direction::left);
            }
            else tank.SetSpeed({0, 0});

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                tank.Shoot();
            }

            auto now{std::chrono::steady_clock::now()};
            auto deltaTime{std::chrono::duration<double, std::milli>(now - timeNow).count()};
            tank.Update(deltaTime);
            timeNow = now;
            window.clear();
            view.UpdateCamera(tank.GetPosition());
            window.setView(view.GetView());
            map.DrawMap(window);
            window.draw(tank.GetSprite());
            tank.DrawBullets(window, deltaTime);
            window.display();
        }

        return EXIT_SUCCESS;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    catch (...) {
        std::cerr << "Unknown error"sv;
    }

    return EXIT_FAILURE;
}