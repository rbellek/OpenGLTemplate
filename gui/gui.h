#pragma once

class GUI {
public:
	void init(struct GLFWwindow* window);
	void render();
	void destroy();
private:
	struct GLFWwindow* m_window;
};