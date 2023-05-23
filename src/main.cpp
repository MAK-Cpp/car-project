#include <iostream>
#include <filesystem>
// glew need to include before glfw!
#include "GL/glew.h"
#include "GLFW/glfw3.h"

// for SQL
#include "sqlite3.h"

#include "include/button.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    // Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true,
    // и приложение после этого закроется
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char** argv) {
    // Инициализация GLFW
    glfwInit();
    // Настройка GLFW
    // Задается минимальная требуемая версия OpenGL.
    // Мажорная
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // Минорная
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Установка профайла для которого создается контекст
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Выключение возможности изменения размера окна
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // for MacOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "car project", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;  // need to use new functional + core-profile mode
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // set GL_COLOR_BUFFER_BIT
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // update GL_COLOR_BUFFER_BIT
        // need before all drawings
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
