#pragma once
#include <GL/glew.h>
#include <glfw3.h>

namespace pl_fw {
	namespace graphics {

#define MAX_KEYS		1024
#define MAX_BUTTONS		32

		class Window {


		private: //Private Members
			
			friend struct GLFWwindow;

			const char *m_title;
			int m_width, m_height;
			GLFWwindow *m_window;
			bool m_closed;

			static bool m_keys[MAX_KEYS];
			static bool m_mouseButtons[MAX_BUTTONS];
			static double mX, mY;

		public: //Public

			Window(const char *name, int width, int height);
			~Window();

			void clear() const;
			bool closed() const;
			void update();

			inline int getWidth() const { return m_width; };
			inline int getHeight() const { return m_height; };

			static bool isKeyPressed(unsigned int keycode);
			static bool isMouseButtonPressed(unsigned int button);
			static void getMousePosition(double& x, double& y);

		private: //Private Methods
			bool init();
			
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow* window, double Xpos, double Ypos);
		};
	} 
}