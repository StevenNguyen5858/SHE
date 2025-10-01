#pragma once
#include "pde.h"

namespace pde {
    inline sf::Vector2f vf(double x, double y);
    
    inline sf::Vector2f vf(const double x, const double y) {
        return sf::Vector2f(x, y);
    }

    sf::RectangleShape r;
    void rect(double x, double y, double w, double h) {
        r.setSize(sf::Vector2f(w, h));
        r.setPosition(vf(x, y));
        r.setFillColor(currentFill);
        r.setOutlineThickness(currentStrokeWeight);
        r.setOutlineColor(currentStroke);
        activeWindow->draw(r);
    }

    void rect(double x, double y, double w, double h, int alpha) {
        r.setSize(sf::Vector2f(w, h));
        r.setPosition(vf(x, y));
        r.setFillColor(sf::Color(currentFill.r, currentFill.g, currentFill.b, alpha));
        r.setOutlineThickness(currentStrokeWeight);
        r.setOutlineColor(currentStroke);
        activeWindow->draw(r);
    }


    sf::CircleShape c;
    void circle(double x, double y, double d) {
        c.setRadius(d / 2);
        c.setPointCount(50);
        c.setPosition(vf(x, y));
        c.setFillColor(currentFill);
        c.setOutlineColor(currentStroke);
        c.setOutlineThickness(currentStrokeWeight);
        activeWindow->draw(c);
    }

    void circle(double x, double y, double d, int alpha) {
        c.setRadius(d / 2);
        c.setPointCount(50);
        c.setPosition(vf(x, y));
        c.setFillColor(sf::Color(currentFill.r, currentFill.g, currentFill.b, alpha));
        c.setOutlineColor(currentStroke);
        c.setOutlineThickness(currentStrokeWeight);
        activeWindow->draw(c);
    }


    vector<sf::Vertex> vertices;
    vector<sf::Vertex> vertices2;
    sf::Vertex v;


    void addVertex(double x, double y) {
        v.position = vf(int(x), int(y));
        vertices.push_back(v);
    }

    void triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
        vertices.clear();
        v.color = currentFill;

        v.position = sf::Vector2f(x1, y1);
        vertices.push_back(v);
        v.position = sf::Vector2f(x2, y2);
        vertices.push_back(v);
        v.position = sf::Vector2f(x3, y3);
        vertices.push_back(v);

        activeWindow->draw(&vertices[0], vertices.size(), sf::PrimitiveType::Triangles);
        vertices.clear();
    }

    void triangle(double x1, double y1, double x2, double y2, double x3, double y3, int alpha) {
        vertices.clear();
        fill(currentFill.r, currentFill.g, currentFill.b, alpha);
        v.color = currentFill;

        v.position = sf::Vector2f(x1, y1);
        vertices.push_back(v);
        v.position = sf::Vector2f(x2, y2);
        vertices.push_back(v);
        v.position = sf::Vector2f(x3, y3);
        vertices.push_back(v);

        activeWindow->draw(&vertices[0], vertices.size(), sf::PrimitiveType::Triangles);
        vertices.clear();
    }

    void line(double x1, double y1, double x2, double y2) {
        vertices.clear();
        v.color = currentFill;

        v.position = sf::Vector2f(x1, y1);
        vertices.push_back(v);
        v.position = sf::Vector2f(x2, y2);
        vertices.push_back(v);

        activeWindow->draw(&vertices[0], vertices.size(), sf::PrimitiveType::Lines);
        vertices.clear();
    }

    void line(double x1, double y1, double x2, double y2, int alpha) {
        vertices.clear();
        fill(currentFill.r, currentFill.g, currentFill.b, alpha);
        v.color = currentFill;

        v.position = sf::Vector2f(x1, y1);
        vertices.push_back(v);
        v.position = sf::Vector2f(x2, y2);
        vertices.push_back(v);

        activeWindow->draw(&vertices[0], vertices.size(), sf::PrimitiveType::Lines);
        vertices.clear();
    }

    void roundedRectangleHelper(double x, double y, double w, double h, int r, int strokeWeight, int pointCount = 0) {
        strokeWeight = abs(strokeWeight);
        vertices.clear();
        v.color = (strokeWeight != 0)? currentFill : currentStroke;
        int cornerPointCount = (pointCount == 0)? 190 : pointCount;
        double degreesShort = 0.18;
        double pi = 2 * acos(0.0);

        int xPos;
        int yPos;
        int cornerCenterX;
        int cornerCenterY;
        int centerX = int(x + (w / 2));
        int centerY = int(y + (h / 2));
        
        // Center
        addVertex(centerX, centerY);

        // Top Right Corner
        cornerCenterX = (x + w) - r;
        cornerCenterY = (y + r);
        for (double i = pi / 2 - degreesShort; i > degreesShort; i = i - (pi / 2) / cornerPointCount) {
            xPos = cornerCenterX + abs(cos(i) * r);
            yPos = cornerCenterY - abs(sin(i) * r);
            addVertex(xPos - strokeWeight, yPos + strokeWeight);
        }

        // Bottom Right Corner
        cornerCenterX = (x + w) - r;
        cornerCenterY = (y + h) - r;
        for (double i = 2 * pi - degreesShort; i > (3.0 / 2.0 * pi) + degreesShort; i = i - (pi / 2) / cornerPointCount) {
            xPos = cornerCenterX + abs(cos(i) * r);
            yPos = cornerCenterY + abs(sin(i) * r);
            addVertex(xPos - strokeWeight, yPos - strokeWeight);
        }

        // Bottom Left Corner
        cornerCenterX = x + r;
        cornerCenterY = (y + h) - r;
        for (double i = (3.0 / 2.0 * pi) - degreesShort; i > pi + degreesShort; i = i - (pi / 2) / cornerPointCount) {
            xPos = cornerCenterX - abs(cos(i) * r);
            yPos = cornerCenterY + abs(sin(i) * r);
            addVertex(xPos + strokeWeight, yPos - strokeWeight);
        }

        // Top Left Corner
        cornerCenterX = x + r;
        cornerCenterY = y + r;
        for (double i = pi - degreesShort; i > pi / 2 + degreesShort; i = i - (pi / 2) / cornerPointCount) {
            xPos = cornerCenterX - abs(cos(i) * r);
            yPos = cornerCenterY - abs(sin(i) * r);
            addVertex(xPos + strokeWeight, yPos + strokeWeight);
        }

        // Top Right Corner
        cornerCenterX = (x + w) - r;
        cornerCenterY = (y + r);
        xPos = cornerCenterX + abs(cos(pi / 2 - degreesShort) * r);
        yPos = cornerCenterY - abs(sin(pi / 2 - degreesShort) * r);
        addVertex(xPos - strokeWeight, yPos + strokeWeight);
    }

    void roundedRectangle(double x, double y, double w, double h, int r, int pointCount = 0) {
        int shortestSide = (w < h) ? w : h;
        r = (r * 2 < shortestSide) ? r : shortestSide / 2;

        // Stroke outline
        roundedRectangleHelper(x, y, w, h, r, 0, pointCount);
        activeWindow->draw(&vertices[0], vertices.size(), sf::PrimitiveType::TriangleFan);

        if (currentStroke == currentFill) {
            vertices.clear();
            return;
        }

        // Inner rounded rectangle
        roundedRectangleHelper(x, y, w, h, r - abs(currentStrokeWeight), currentStrokeWeight, pointCount);
        activeWindow->draw(&vertices[0], vertices.size(), sf::PrimitiveType::TriangleFan);

        vertices.clear();
    }

     enum class Alignment { CenterX = 0, CenterY = 1, CenterXY = 3 };

    sf::Font currentFont;
    sf::Font defaultFont;
    sf::Font fontBold;
    std::uint32_t textStyle = sf::Text::Bold;
    double currentTextSize = 10.0;
    sf::Font gotham;
    sf::Font gothamBold;
    sf::Font gothamBoldItalic;
    sf::Font gothamItalic;
    sf::Font gothamLight;

    void loadFonts() {
        gotham.openFromFile("assets/Gotham.ttf");
        gothamBold.openFromFile("assets/GothamBold.ttf");
        gothamBoldItalic.openFromFile("assets/GothamBoldItalic.ttf");
        gothamItalic.openFromFile("assets/GothamItalic.ttf");
        gothamLight.openFromFile("assets/GothamLight.ttf");
        defaultFont = gothamLight;
        currentFont = defaultFont;
    }

    void textSize(double textH) {
        currentTextSize = textH;
    }

    void textFont(const sf::Font& f) {
        currentFont = f;
    }

    double textWidth(const std::string str) {
        sf::Text text(currentFont, str);
        text.setStyle(textStyle);
        text.setCharacterSize(static_cast<unsigned int>(currentTextSize));
        return text.getGlobalBounds().size.x;
    }

    double textWidth(sf::Text* text, const std::string& str) {
        auto oldText = text->getString();
        text->setString(str);
        double width = text->getGlobalBounds().size.x;
        text->setString(oldText);
        return width;
    }

    void text(const std::string str, double x, double y, double h) {
        sf::Text text(currentFont, str);
        text.setStyle(textStyle);
        text.setFillColor(currentFill);
        text.setCharacterSize(static_cast<unsigned int>(h));
        text.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
        pde::activeWindow->draw(text);
        currentFont = defaultFont;
    }

    void text(const std::string str, double x, double y, double w, double h, Alignment a) {
        sf::Text text(currentFont, str);
        text.setStyle(textStyle);
        text.setFillColor(currentFill);
        text.setCharacterSize(static_cast<unsigned int>(currentTextSize));

        if (a == Alignment::CenterY || a == Alignment::CenterXY) {
            text.setString("A");
            sf::FloatRect bounds = text.getGlobalBounds();
            sf::Vector2f position = text.getPosition();

            double yOffset = bounds.position.y - position.y;
            double centeredY = y + ((h - bounds.size.y) / 2.0);
            double centeredYCorrected = centeredY - yOffset;

            if (a == Alignment::CenterXY) {
                text.setString(str);
                double centeredOffsetX = (w - text.getGlobalBounds().size.x) / 2.0;
                double centeredX = x + centeredOffsetX;
                text.setPosition(sf::Vector2f(static_cast<float>(centeredX),
                                            static_cast<float>(centeredYCorrected)));
            }
            else {
                text.setPosition(sf::Vector2f(static_cast<float>(x),
                                            static_cast<float>(centeredYCorrected)));
                text.setString(str);
            }
        }
        else {
            // Default: top-left placement
            text.setString(str);
            text.setPosition(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
        }

        pde::activeWindow->draw(text);
        currentFont = defaultFont;
    }

}