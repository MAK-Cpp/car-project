#ifndef CARPROJECT_BUTTON_H
#define CARPROJECT_BUTTON_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <utility>

#include "shader.h"

class Button {
private:
    std::string button_name_;
    GLuint height_, width_;
    GLdouble position_x_, position_y_;
    static constexpr GLfloat inside_vertices_[] = {-1.0f, -1.0f, 0.0f,

                                                   1.0f,  -1.0f, 0.0f,

                                                   -1.0f, 1.0f,  0.0f,

                                                   1.0f,  1.0f,  0.0f};

    static constexpr GLuint inside_vertices_index[] = {0, 1, 2, 1, 2, 3};

    const std::filesystem::path button_vertex_shader (PROJECT_SOURCE_DIR "/lib/shaders/button-vertex.glsl");


    GLuint VBO_;  // vertex buffer object
    GLuint IBO_;  // index buffer object
    GLuint shader_programm_;
public:
    Button(std::string   text, GLuint width = 100, GLuint height = 50, GLdouble pos_x = 0, GLdouble pos_y = 0):
        button_name_{std::move(text)},
        width_{width},
        height_{height},
        position_x_{pos_x},
        position_y_{pos_y} {
        shader_programm_ = getShaderProgram(PROJECT_SOURCE_DIR "/lib/shaders/button-vertex.glsl",
                                            PROJECT_SOURCE_DIR "/lib/shaders/button-fragment.glsl");
        glGenBuffers(1, &VBO_);
        glGenBuffers(1, &IBO_);

    }

    void draw(GLuint* window) {
        glUseProgram(shader_programm_);

    }
};


#endif //CARPROJECT_BUTTON_H
