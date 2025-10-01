#pragma once
#include "../processing/page.h"
#include "../processing/element.h"

class TemplatePage : public Page {
public:
    Element* header;
    Element* content;
    Element* footer;

    TemplatePage() : Page("Template Page") {
        // Root-most element defines grid (local only)
        Element* root = createElement<Element>();
        root->name = "root";
        root->transformX = 0;
        root->transformY = 0;
        root->width = 1;   // full width
        root->height = 1;  // full height
        root->gridW = 10;  // 10 columns
        root->gridH = 10;  // 10 rows
        root->computeAbsolute();

        // Header (persistent member)
        header = root->createElement<Element>();
        header->name = "header";
        header->transformX = 0;
        header->transformY = 0;
        header->width = 10;    // 10/10 = full width
        header->height = 1;    // 1/10 = 10% height
        header->fill = sf::Color(100, 100, 250);
        header->computeAbsolute();

        // Content (persistent member)
        content = root->createElement<Element>();
        content->name = "content";
        content->transformX = 0;
        content->transformY = 1; // below header
        content->width = 10;
        content->height = 8;
        content->gridW = 10;     // grid for nested children
        content->gridH = 8;
        content->fill = sf::Color(200, 200, 200);
        content->computeAbsolute();

        // Nested element inside content (local only)
        Element* nestedBox = content->createElement<Element>();
        nestedBox->name = "nestedBox";
        nestedBox->transformX = 1;  // 1/10 of content width
        nestedBox->transformY = 1;  // 1/8 of content height
        nestedBox->width = 8;       // 8/10 of content width
        nestedBox->height = 2;      // 2/8 of content height
        nestedBox->fill = sf::Color(250, 150, 150);
        nestedBox->computeAbsolute();

        // Footer (persistent member)
        footer = root->createElement<Element>();
        footer->name = "footer";
        footer->transformX = 0;
        footer->transformY = 9;  // after header + content
        footer->width = 10;
        footer->height = 1;
        footer->fill = sf::Color(100, 250, 100);
        footer->computeAbsolute();
    }

    void draw() override {
        for (auto& e : elements)
            e->draw();
    }
};
