#include "processing/processing.h"
#include "processing/app.h"
#include "pages/template-page.h"
using namespace std;


void keyPressed(const sf::Event::KeyPressed* event) {
    if (event->code == sf::Keyboard::Key::Escape) {
        std::cout << "Escape key pressed!" << std::endl;
        pde::activeWindow->close();
    } 
    else if (event->code == sf::Keyboard::Key::I && event->control && event->shift) {
        std::cout << "Ctrl + Shift + I pressed!" << std::endl;
        pde::isDeveloping = !pde::isDeveloping;
    }
}

int main()
{
    // Create the SFML window and assign it to pde::activeWindow
    pde::mainWindow.create(sf::VideoMode({800, 600}), "CMake SFML Project");
    pde::activeWindow = &pde::mainWindow;
    pde::activeWindow->setFramerateLimit(144);

    // Create app and template page
    App app;
    TemplatePage* page = new TemplatePage();
    app.addPage("template", page);

    pde::loadFonts();

    // Main loop
    while (pde::activeWindow->isOpen()){
        // Poll events
        std::optional<sf::Event> event;
        while (const optional event = pde::activeWindow->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                pde::activeWindow->close();
            }
            if (event->is<sf::Event::KeyPressed>()) {
                keyPressed(event->getIf<sf::Event::KeyPressed>());
            }
        }

        pde::activeWindow->clear(sf::Color::White);

        // Draw active page
        app.draw();

        pde::activeWindow->display();
    }

    return 0;
}