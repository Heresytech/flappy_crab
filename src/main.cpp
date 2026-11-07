#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<cmath>

// исходный код вершинного шейдера
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec4 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//фрагментный шейдер(отвечает за цвета)
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.2f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";



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



	// создаем объект вершинного шейдера
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// соединение  объекта вершинного шейдера с исходным кодом вершинного шейдера
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// компиляция вершинного шейдера
	glCompileShader(vertexShader);

	// создание фрагментного шейдера
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// соединение фрагментного шейдера  с исходным кодом фрагментного шейдера
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// компиляция фрагментного шейдера
	glCompileShader(fragmentShader);

	// создание шейдерной программы
	GLuint shaderProgram = glCreateProgram();
	// соединение фргаментного и вершинного шейдера с шйедерной программой
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// линковка всех шейдеров в одну шейдерную программу
	glLinkProgram(shaderProgram);

	// удаление ненужных теперь шейдеров из памяти
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	// координаты вершин прямоугольника
	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f, // нижний левый угол
		-0.5f, 0.5f, 0.0f, // верхний левый угол
		0.5f, 0.5f, 0.0f, // верхний правый угол
		0.5f, -0.5f, 0.0f // нижний правый угол
	};
    
	//индексный буфер(показывает, в каком порядке отрисовывать вершины из массива vertices)
    GLuint indices[] = 
	{
		0, 1, 3,
		1, 2, 3
	};

	// создание контейнеров ссылок(?) для объекта вершинного массива, объекта вершинного буфера и индексного буфера
	GLuint VAO, VBO, EBO;

	// генерация объектов для вершинного массива и вершинного буфера
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
     

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}