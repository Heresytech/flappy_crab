#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream> 

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_CAPTION "flappy crab the beginning"

// Функция-callback для изменения размеров буфера кадра в случае изменения размеров поверхности окна
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main(void)
{
    GLFWwindow* window; // Указатель на окно GLFW3
    
    // Инициализация GLFW3
    if (!glfwInit())
    {
        std::cout << "GLFW init error\n";
        return -1;
    }

    // Завершение работы с GLFW3 перед выходом
    atexit(glfwTerminate);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Мажорная версия спецификаций OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // Минорная версия спецификаций OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Контекст OpenGL, который поддерживает только основные функции
 
    // Создание окна GLFW3 с заданными шириной, высотой и заголовком окна
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_CAPTION, NULL, NULL);
    if (!window)
    {
        std::cout << "GLFW create window error\n";
        return -1;
    }

    // Установка основного контекста окна
    glfwMakeContextCurrent(window);
    // Установка callback-функции для изменения размеров окна и буфера кадра
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Загрузка функций OpenGL с помощью GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD load GL error\n";
        return -1;
    }

    // Установка цвета очистки буфера цвета
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Пока не произойдет событие запроса закрытия окна
    while(!glfwWindowShouldClose(window))
    {
        // Очистка буфера цвета
        glClear(GL_COLOR_BUFFER_BIT);


        // Тут производится рендер
        // ...

        // Представление содержимого буфера цепочки показа на окно
        glfwSwapBuffers(window);
        // Обработка системных событий
        glfwPollEvents();
    }
    return 0;
}