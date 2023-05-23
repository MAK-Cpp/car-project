#include "shader.h"

GLuint compileShader(GLenum shaderType, std::filesystem::path const& shader_source_path) {
    // create shader
    GLuint vertexShaderID = glCreateShader(shaderType);

    // get Shader code
    std::ifstream shader (shader_source_path);
    std::string shader_code((std::istreambuf_iterator<char>(shader)), std::istreambuf_iterator<char>());

    // link source file to our shader id
    char const* code = shader_code.c_str();
    glShaderSource(vertexShaderID, 1, &code, nullptr);
    // compile shader
    glCompileShader(vertexShaderID);

    // checking for success of shader compilation
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShaderID, 512, nullptr, infoLog);
        std::cout << "ERROR: " << shader_source_path.filename() << " COMPILATION FAILED\n" << infoLog << std::endl;
        throw std::exception();
    }

    return vertexShaderID;
}

GLuint getShaderProgram(std::filesystem::path const& vertex_shader_source_path,
                         std::filesystem::path const& fragment_shader_source_path) {
    // creating vertex shader
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertex_shader_source_path);
    // creating fragment shader
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragment_shader_source_path);

    // creating shader program
    GLuint shaderProgram = glCreateProgram();

    // link our shaders to program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // checking for success of program link
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR_SHADER_PROGRAM_COMPILATION_FAILED\n" << infoLog << std::endl;
        throw std::exception();
    }

    // delete shaders because we don't need them anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}