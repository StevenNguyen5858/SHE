#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

using namespace std;

namespace pde {
    sf::RenderWindow mainWindow;
    sf::RenderWindow* activeWindow = &mainWindow;  

    sf::Color currentFill = sf::Color(255, 255, 255, 255);
    sf::Color currentStroke = sf::Color(0, 0, 0, 255);
    int currentStrokeWeight = 1;

    bool isDeveloping = false;

    /// @brief Sets color to fill shapes. All subsequent shapes will be filled with the color.
    /// @param color sf::Color
    void fill(sf::Color color){
        currentFill = color;
    }

    /// @brief Sets color to fill shapes. All subsequent shapes will be filled with the color.
    /// @param color sf::Color
    /// @param alpha opacity of the fill
    void fill(sf::Color color, int alpha){
        currentFill = sf::Color(color.r, color.g, color.b, alpha);
    }

    /// @brief Sets color to fill shapes. All subsequent shapes will be filled with the color.
    /// @param r red value (0 - 255)
    /// @param g g value (0 - 255)
    /// @param b b value (0 - 255)
    /// @param alpha opacity of the fill
    void fill(int r, int g, int b, int alpha){
        currentFill = sf::Color(r, g, b, alpha);
    }

    /// @brief Sets fill color to transparent. All subsequent shapes will be filled with transparency.
    void noFill() {
        currentFill = sf::Color::Transparent;
    }

    /// @brief Sets color to stroke (outline) shapes. All subsequent shapes will be outlined with this color.
    /// @param color sf::Color
    void stroke(sf::Color color){
        currentStroke = color;
    }

    /// @brief Sets color to stroke (outline) shapes. All subsequent shapes will be outlined with this color.
    /// @param color sf::Color
    /// @param alpha opacity of the stroke
    void stroke(sf::Color color, int alpha){
        currentStroke = sf::Color(color.r, color.g, color.b, alpha);
    }

    /// @brief Sets color to stroke (outline) shapes. All subsequent shapes will be outlined with this color.
    /// @param r red value (0 - 255)
    /// @param g green value (0 - 255)
    /// @param b blue value (0 - 255)
    /// @param alpha opacity of the stroke
    void stroke(int r, int g, int b, int alpha){
        currentStroke = sf::Color(r, g, b, alpha);
    }

     /// @brief Sets stroke color to transparent. All subsequent shapes will have a transparency stroke color.
    void noStroke() {
        currentStroke = sf::Color::Transparent;
    }

    /// @brief Sets the stroke (outline) thickness for subsequent shapes.
    void strokeWeight(int strokeWeight) {
        currentStrokeWeight = -1 * strokeWeight;
    }
}