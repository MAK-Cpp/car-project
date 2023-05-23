#ifndef CARPROJECT_SHADER_H
#define CARPROJECT_SHADER_H

#include <iostream>
#include <filesystem>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLuint compileShader(GLenum shaderType, std::filesystem::path const& shader_source_path);

GLuint getShaderProgram(std::filesystem::path const& vertex_shader_source_path, std::filesystem::path const& fragment_shader_source_path);




#endif //CARPROJECT_SHADER_H
