#pragma once

#include <string>
#include <stdint.h>
#include "gui/gui.h"

struct GLFWwindow;

class App
{
public:
	App(std::string title, uint32_t width, uint32_t height);
	bool Run();
protected:
	bool init();
	virtual void render();
private:
	std::string m_title;
	uint32_t m_width;
	uint32_t m_height;
	GLFWwindow* m_window;
	GUI m_gui;
};

