#include "processing/pde.h"
using namespace std;

int main()
{
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({400, 400}), "CMake SFML Project");
    window.setFramerateLimit(144);

    while (window.isOpen()){
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear();
        window.display();
    }
}