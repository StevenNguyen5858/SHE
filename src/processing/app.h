#pragma once
#include "page.h"
#include <stack>

class App {
    // Access specifier:
    public:
    map<string, Page*> pages = {};
    stack<Page*> pageHistory = {};
    Page* activePage = NULL;
    string title = "myapp";

    App() {}

    void draw() {
        if (activePage != NULL) {
            activePage->draw();
        }
    }

    void addPage(string pathName, Page* page) {
        if (pages.size() == 0) { // Open first page added to application
            openPage(page);
        }
        page->onInit(); // Run one time settings setup for page
        pages[pathName] = page;
    }

    void openPage(Page* page) {
        pde::activeWindow->setTitle(title + "/" + page->name);
		pageHistory.push(activePage);
		activePage = page;

		page->setup();
    }
};