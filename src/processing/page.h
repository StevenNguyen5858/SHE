#pragma once
#include "processing.h"

class Element;


class Page {
	// Access specifier:
public:
	string name;
    vector<Element*> elements;


	void (*settingsF)() = NULL;
	void (*setupF)() = NULL;
	void (*drawF)() = NULL;

	// Default Constructor:
	Page(){}

	// Basic processing page:
	Page(string name = "page") : name(name) {}

    // Builder syntax for automatically adding elements to the page
    template <typename T, typename... Args>
    T* createElement(Args&&... args) {
        T* e = new T(this, std::forward<Args>(args)...);
        elements.push_back(e);
        return e;
    }
	
    template <typename T>
    T* getAsType() { return dynamic_cast<T*>(this); }

	// Lifecycle methods
    virtual void onInit() {}
    virtual void setup() {};
    virtual void draw() = 0;
};
