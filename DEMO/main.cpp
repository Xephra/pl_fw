#include <gl/glew.h>
#include <glfw3.h>
#include <iostream>

#include "graphics/Window.h"
#include "maths/vec2.h"


using namespace pl_fw;
using namespace graphics;
using namespace maths;

int main()
{

	Window window("pl_fw", 800, 600);
	glClearColor(0.2f, 1.0f, 0.5f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vec2 a(10.0f,20.0f);
	vec2 b(20.0f, 30.0f);
		
	a *= b;

	while (!window.closed()) 
	{
		//glClear(GL_COLOR_BUFFER_BIT);
		//std::cout << window.getWidth() << " ," << window.getHeight() << std::endl;
		window.clear();
		double x, y;

		std::cout << a << std::endl;

		if (window.isKeyPressed(GLFW_KEY_A)) 
		{
			std::cout << "A Pressed!" << std::endl;
		}
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			window.getMousePosition(x, y);
			std::cout << x << ", " << y << std::endl;
		}


#if 1
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
#else
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
#endif



		window.update();
	}

	return 0;
}