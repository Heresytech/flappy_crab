#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<cmath>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


// координаты вершин прямоугольника
GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // нижний левый угол
		-0.5f, 0.5f, 0.0f,	// верхний левый угол
		0.5f, 0.5f, 0.0f,	// верхний правый угол
		0.5f, -0.5f, 0.0f	// нижний правый угол
    };

//индексный буфер(показывает, в каком порядке отрисовывать вершины из массива vertices)
GLuint indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

int main()
{
	// инициализация GLFW
	glfwInit();

	// говорим GLFW, какую версию GLFW мы используем
	// в этом случае мы используем OPENGl 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// говорим либе, что используем CORE profile
	// это значит, что мы используем современные ф-ции
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// создаем окно GLFW 800x800 пикселей
	GLFWwindow* window = glfwCreateWindow(800, 800, "flappy_crab", NULL, NULL);
	// проверка на ошибки в создании окна
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// загружаем окно в контекст
	glfwMakeContextCurrent(window);

	//загружаем GLAD, конфигурирующую OpenGL
	gladLoadGL();
	// указываем вид камеры
	// в это случае координаты камеры x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);
    
	Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");
    VAO VAO1;
    VAO1.Bind();
    
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
    EBO1.Unbind();
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}