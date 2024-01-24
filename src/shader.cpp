#include "shader.hpp"

Shader::Shader(const std::filesystem::path& vertex, const std::filesystem::path& fragment) {
    this->prog = 0;
    std::string vert_source;
    std::string frag_source;
    std::ifstream vert_file;
    std::ifstream frag_file;
    vert_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    frag_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vert_file.open(vertex.generic_string());
        frag_file.open(fragment.generic_string());
        std::stringstream vert_stream;
        std::stringstream frag_stream;
        vert_stream << vert_file.rdbuf();
        frag_stream << frag_file.rdbuf();
        vert_file.close();
        frag_file.close();
        vert_source = vert_stream.str();
        frag_source = frag_stream.str();
    } catch (std::ifstream::failure e) {
        std::cerr << "Error: Failed to load shader pair: '" << vertex << "' & '" << fragment << "'!" << std::endl;
        return;
    }
    const char* vert_code = vert_source.c_str();
    const char* frag_code = frag_source.c_str();
    int vert_code_len = vert_source.length();
    int frag_code_len = frag_source.length();

    int is_compiled = 0;
    this->vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(this->vert, 1, &vert_code, &vert_code_len);
    glCompileShader(this->vert);
    glGetShaderiv(this->vert, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE) {
        int len = 0;
        glGetShaderiv(this->vert, GL_INFO_LOG_LENGTH, &len);
        char *log = new char[len];
        glGetShaderInfoLog(this->vert, len, &len, log);
        std::cerr << "Error: " << log << std::endl;
        glDeleteShader(this->vert);
        delete log;
        return;
    }
    this->frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(this->frag, 1, &frag_code, &frag_code_len);
    glCompileShader(this->frag);
    glGetShaderiv(this->frag, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled == GL_FALSE) {
        int len = 0;
        glGetShaderiv(this->frag, GL_INFO_LOG_LENGTH, &len);
        char *log = new char[len];
        glGetShaderInfoLog(this->frag, len, &len, log);
        std::cerr << "Error: " << log << std::endl;
        glDeleteShader(this->frag);
        glDeleteShader(this->vert);
        delete log;
        return;
    }

    this->prog = glCreateProgram();
    glAttachShader(this->prog, this->vert);
    glAttachShader(this->prog, this->frag);
    glLinkProgram(this->prog);

    int is_linked = 0;
    glGetProgramiv(this->prog, GL_LINK_STATUS, &is_linked);
    if (is_linked == GL_FALSE) {
        int len = 0;
        glGetProgramiv(this->prog, GL_INFO_LOG_LENGTH, &len);
        char *log = new char[len];
        glGetProgramInfoLog(this->prog, len, &len, log);
        std::cerr << "Error: " << log << std::endl;
        glDeleteProgram(this->prog);
        glDeleteShader(this->frag);
        glDeleteShader(this->vert);
        delete log;
        this->prog = 0;
    }
}

Shader::~Shader() {
    if (this->IsValid()) {
        glDeleteProgram(this->prog);
        glDeleteShader(this->frag);
        glDeleteShader(this->vert);
        this->prog = 0;
    }
}
