#ifndef CARPROJECT_BUTTON_H
#define CARPROJECT_BUTTON_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

class Button {
private:
    std::string button_name_;
    GLuint length_, width_;
    GLdouble position_x_, position_y_;
    static constexpr GLfloat inside_vertices_[] = {-1.0f, -1.0f, 0.0f,

                                                   1.0f,  -1.0f, 0.0f,

                                                   -1.0f, 1.0f,  0.0f,

                                                   1.0f,  1.0f,  0.0f};

    static constexpr GLuint inside_vertices_index[] = {0, 1, 2, 1, 2, 3};
public:

};


#endif //CARPROJECT_BUTTON_H
