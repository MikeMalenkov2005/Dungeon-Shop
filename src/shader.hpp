#ifndef SHADER_HPP
#define SHADER_HPP

#include "framework.hpp"

class Shader {
    public:
    Shader(const std::filesystem::path& vertex, const std::filesystem::path& fragment);
    ~Shader();
    inline bool IsValid() { return this->prog != 0; }
    inline void Use() { glUseProgram(this->prog); }
    inline void SetFloat(const std::string& name, float value) { glProgramUniform1f(this->prog, glGetUniformLocation(this->prog, name.c_str()), value); }
    inline void SetVec2(const std::string& name, float* value) { glProgramUniform2fv(this->prog, glGetUniformLocation(this->prog, name.c_str()), 1, value); }
    inline void SetVec3(const std::string& name, float* value) { glProgramUniform3fv(this->prog, glGetUniformLocation(this->prog, name.c_str()), 1, value); }
    inline void SetVec4(const std::string& name, float* value) { glProgramUniform4fv(this->prog, glGetUniformLocation(this->prog, name.c_str()), 1, value); }
    inline void SetInt(const std::string& name, int value) { glProgramUniform1i(this->prog, glGetUniformLocation(this->prog, name.c_str()), value); }
    inline void SetIVec2(const std::string& name, int* value) { glProgramUniform2iv(this->prog, glGetUniformLocation(this->prog, name.c_str()), 1, value); }
    inline void SetIVec3(const std::string& name, int* value) { glProgramUniform3iv(this->prog, glGetUniformLocation(this->prog, name.c_str()), 1, value); }
    inline void SetIVec4(const std::string& name, int* value) { glProgramUniform4iv(this->prog, glGetUniformLocation(this->prog, name.c_str()), 1, value); }
    private:
    GLuint frag, vert, prog;
};

#endif
