
#ifndef WINDOW_H
#define WINDOW_H

// base_window.h
#include <glad/glad.h>
#include<glfw3.h>



typedef struct {
    GLFWwindow* glfwWindow;
    int width;
    int height;
    const char* title;
} Window;

Window* Window_Create(int width, int height, const char* title);
void Window_Destroy(Window* window);
void Window_Update(Window* window);
void Window_Render(Window* window);
void framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height);
void window_close_callback(GLFWwindow* glfwWindow);
void key_callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
void mouse_position_callback(GLFWwindow* glfwWindow, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* glfwWindow, int button, int action, int mods);
void mouse_scroll_callback(GLFWwindow* glfwWindow, double xoffset, double yoffset);

#endif