#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "stb_image.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

// координаты вершин прямоугольника(два треугольника)
GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // нижний левый угол
		-0.5f, 0.5f, 0.0f,	// верхний левый угол
		0.5f, 0.5f, 0.0f,	// верхний правый угол
		0.5f, -0.5f, 0.0f	// нижний правый угол
};

// индексный буфер(показывает, в каком порядке отрисовывать вершины из массива vertices)
GLuint indices[] =
	{
		0, 1, 3,
		1, 2, 3};

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
	GLFWwindow *window = glfwCreateWindow(800, 800, "flappy_crab", NULL, NULL);
	// проверка на ошибки в создании окна
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// загружаем окно в контекст
	glfwMakeContextCurrent(window);

	// загружаем GLAD, конфигурирующую OpenGL
	gladLoadGL();
	// указываем вид камеры
	// в это случае координаты камеры x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);
    
	//класс шейдерной программы
	Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");

	// генерация объекта вершинного массива
	VAO VAO1;
	VAO1.Bind();

	//  генерация объекта вершинного буфера и соединение его с вершинами
	VBO VBO1(vertices, sizeof(vertices));
	// генерация объекта буфера элементов и соединение его с масивом индексов
	EBO EBO1(indices, sizeof(indices));

	
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();
    
	//нахождение индекса формы(переменной в шейдере) gScale
    GLint gScaleLocation = glGetUniformLocation(shaderProgram.ID, "gScale");
    
    //Текстура
    int widthImg, heightImg, numColCh;
	unsigned char* bytes = stbi_load("Textures/pop_cat.png", &widthImg, &heightImg, &numColCh, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);

		//gScaleLocation = glGetUniformLocation(shaderProgram.ID, "gScale");

		static float Scale = 0.0f;
		static float Delta = 0.001f;

		Scale += Delta;
		if ((Scale >= 1.0f) || (Scale <= -1.0f))
		{
			Delta *= -1.0f;
		}
        
		glUniform1f(gScaleLocation, Scale);

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

		// Specify the color of the background
	}

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