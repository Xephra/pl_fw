#include "graphics/window.h"

#include <iostream>

namespace pl_fw { namespace graphics {

	void window_resize(GLFWwindow *window, int width, int height);
	
	bool Window::m_keys[MAX_KEYS];
	bool Window::m_mouseButtons[MAX_BUTTONS];
	double Window::mX;
	double Window::mY;

		Window::Window(const char *title, int width, int height) {
		m_title = title;
		m_width = width;
		m_height = height;

		if (!init()) 
		{
			glfwTerminate();
		}	
		for (int i = 0; i < MAX_KEYS; i++)
		{
			m_keys[i] = false;
		}
		for (int j = 0; j < MAX_BUTTONS; j++)
		{
			m_mouseButtons[j] = false;
		}
		
	}
	Window::~Window() 
	{

	}

	bool Window::init()
	{
		if (!glfwInit())
		{
			std::cout << "Failed to init GLFW" << std::endl;
		}

		m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
		if (!m_window) 
		{
			glfwTerminate();
			std::cout << "failed to make window" << std::endl;
			return false;
		} 
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, this);
		glfwSetWindowSizeCallback(m_window, window_resize);
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);
		glfwSetCursorPosCallback(m_window, cursor_position_callback);

		std::cout << "OpenGL version" << glGetString(GL_VERSION) << std::endl;

		if (glewInit() != GLEW_OK) 
		{
			std::cout << "Could not initialize GLEW!" << std::endl;
			return false;
		}

		return true;
	}

	bool Window::isKeyPressed(unsigned int keycode)
	{
		if (keycode >= MAX_KEYS) 
		{
			return false;
		}

		return m_keys[keycode];
	}

	bool Window::isMouseButtonPressed(unsigned int button)
	{
		if (button >= MAX_BUTTONS)
		{
			return false;
		}

		return m_mouseButtons[button];
	}


	void Window::getMousePosition(double& x, double& y) 
	{
		x = mX;
		y = mY;
	}

	void Window::clear() const 
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update()  
	{
		glfwPollEvents();
		glfwGetFramebufferSize(m_window, &m_width, &m_height);
		//glViewport(0, 0, m_width, m_height);
		glfwSwapBuffers(m_window);
	}

	bool Window::closed() const
	{
		return glfwWindowShouldClose(m_window) == 1;

	}

	void window_resize(GLFWwindow *window, int width, int height) 
	{
		glViewport(0, 0, width, height);
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		

		win->m_keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) 
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);

		win->m_mouseButtons[button] = action != GLFW_RELEASE;
	}

	void cursor_position_callback(GLFWwindow* window, double Xpos, double Ypos) 
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->mX = Xpos;
		win->mY = Ypos;
		
	}
}}