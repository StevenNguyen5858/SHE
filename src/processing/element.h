#pragma once
#include <vector>
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include "pde.h"
#include "page.h"

class Page; // Forward declaration

class Element {
public:
    Page* parentPage = nullptr;
    Element* parentElement = nullptr;
    std::vector<Element*> children;

    // Identification
    std::string name = "";

    // Positioning and size
    double transformX = 0;
    double transformY = 0;
    double width = 1;
    double height = 1;

    double absoluteX = 0;
    double absoluteY = 0;
    double pxWidth = 0;
    double pxHeight = 0;

    int gridW = 1;
    int gridH = 1;

    // Colors
    sf::Color fill = sf::Color::Transparent;
    sf::Color stroke = sf::Color::Black;
    int strokeWeight = 1;

    // Event flags
    bool hasClick = true;
    bool hasHover = true;
    bool hasKeyPress = true;

    // Function pointers for custom events
    std::function<void(Element*)> onClick = nullptr;
    std::function<void(Element*)> onHover = nullptr;
    std::function<void(Element*, const std::string&)> onKeyPress = nullptr;

    // Constructor
    Element(Page* page, Element* parent = nullptr)
        : parentPage(page), parentElement(parent)
    {
        computeAbsolute();
        if (parentElement)
            parentElement->children.push_back(this);
        else if (parentPage)
            parentPage->elements.push_back(this);
    }

    // Nested builder syntax
    template<typename T, typename... Args>
    T* createElement(Args&&... args) {
        T* e = new T(parentPage, this, std::forward<Args>(args)...);
        children.push_back(e);
        return e;
    }

    // Compute absolute positions/sizes
    void computeAbsolute() {
        double parentWidth = parentElement ? parentElement->pxWidth : pde::activeWindow->getSize().x;
        double parentHeight = parentElement ? parentElement->pxHeight : pde::activeWindow->getSize().y;
        int parentGridW = parentElement ? parentElement->gridW : 1;
        int parentGridH = parentElement ? parentElement->gridH : 1;

        absoluteX = parentWidth * (transformX / parentGridW);
        absoluteY = parentHeight * (transformY / parentGridH);
        pxWidth   = parentWidth * (width / parentGridW);
        pxHeight  = parentHeight * (height / parentGridH);
    }

    // Draw method
    virtual void draw() {
        // Draw the element itself
        pde::stroke(stroke);
        pde::strokeWeight(strokeWeight);
        pde::fill(fill);
        pde::rect(absoluteX, absoluteY, pxWidth, pxHeight);

        // Draw the grid if in development mode
        if (pde::isDeveloping && (gridW > 1 || gridH > 1 || width > 1 || height > 1)) {
            sf::Color gridColor(0, 0, 0, 128); // 50% transparent black
            double cellW = pxWidth / gridW;
            double cellH = pxHeight / gridH;

            pde::fill(gridColor);
            pde::strokeWeight(1);

            // Vertical lines
            for (int i = 1; i < gridW; ++i) {
                double x = absoluteX + i * cellW;
                pde::line(x, absoluteY, x, absoluteY + pxHeight);
            }

            // Horizontal lines
            for (int j = 1; j < gridH; ++j) {
                double y = absoluteY + j * cellH;
                pde::line(absoluteX, y, absoluteX + pxWidth, y);
            }

            pde::fill(sf::Color::Black); // text color
            pde::text(name, absoluteX, absoluteY, pxWidth, pxHeight, pde::Alignment::CenterXY);
        }


        // Draw child elements
        for (auto& child : children)
            child->draw();
    }

    // Default event handlers
    virtual void click(double x, double y) {
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            if ((*it)->hasClick) {
                (*it)->click(x, y);
                return;
            }
        }
        if (onClick) onClick(this);
    }

    virtual void hover(double x, double y) {
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            if ((*it)->hasHover) {
                (*it)->hover(x, y);
                return;
            }
        }
        if (onHover) onHover(this);
    }

    virtual void keyPress(const std::string& key) {
        for (auto& child : children) {
            if (child->hasKeyPress) {
                child->keyPress(key);
                return;
            }
        }
        if (onKeyPress) onKeyPress(this, key);
    }
};
