#include "shader.hpp"

#include <stdexcept>
#include <algorithm>

#include "../utils/file_utils.hpp"

namespace StructuredGL::Shaders {

    Shader::Shader(const std::string& name, std::initializer_list<ShaderData> shaderData): GPUResource(name) {
        std::unordered_map<GLuint, GLuint> modules = std::unordered_map<GLuint, GLuint>();
        for (const ShaderData& data : shaderData) {
            if (modules.contains(data.type)) {
                throw std::runtime_error("[Shader: " + name + "] Duplicate shader module data, already bound for type " + std::to_string(data.type));
            }
            modules.insert(std::pair(
                data.type,
                this->createShader(data)
            ));
        }
        this->setId(glCreateProgram());
        if (this->getId() == 0) {
            throw std::runtime_error("[Shader: " + name + "] Unable to create new shader program");
        }
        this->link(modules);
    }

    Shader::~Shader() {
        if (this->isBound()) {
            glUseProgram(0);
            this->setBound(false);
        }
        glDeleteProgram(this->getId());
    }

    std::string Shader::getPrefix() const {
        return "[Shader: " + this->name + " Id: " + std::to_string(this->getId()) + "]";
    }

    GLuint Shader::createShader(const ShaderData& data) const {
        if (data.file.empty()) {
            throw std::runtime_error("Shader data file path cannot be empty");
        }
        std::string code = Utils::FileUtils::readFile(data.file);
        GLuint shaderId = glCreateShader(data.type);
        if (shaderId == 0) {
            throw std::runtime_error(this->getPrefix() + " Error while creating shader of type " + std::to_string(data.type));
        }
        const char* literalCode = code.c_str();
        glShaderSource(shaderId, 1, &literalCode, nullptr);
        glCompileShader(shaderId);
        GLint status;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
        if (!status) {
            GLchar log[1024];
            glGetShaderInfoLog(shaderId, 1024, nullptr, log);
            throw std::runtime_error(this->getPrefix() + " Error while compiling shader: " + std::string(log));
        }
        glAttachShader(this->getId(), shaderId);
        return shaderId;
    }

    void Shader::link(const std::unordered_map<GLuint, GLuint>& modules) const {
        glLinkProgram(this->getId());
        GLint status;
        glGetProgramiv(this->getId(), GL_LINK_STATUS, &status);
        if (!status) {
            GLchar log[1024];
            glGetProgramInfoLog(this->getId(), 1024, nullptr, log);
            throw std::runtime_error(this->getPrefix() + " Error while linking shader:" + std::string(log));
        }
        for (const auto& [_ignored, shaderId] : modules) {
            glDetachShader(this->getId(), shaderId);
            glDeleteShader(shaderId);
        }
    }

    ShaderValidationState Shader::validate() {
        glValidateProgram(this->getId());
        GLint status;
        glGetProgramiv(this->getId(), GL_VALIDATE_STATUS, &status);
        if (!status) {
            GLchar log[1024];
            glGetProgramInfoLog(this->getId(), 1024, nullptr, log);
            return ShaderValidationState {
                .valid =  false,
                .message = std::optional<std::string>(log)
            };
        }
        return ShaderValidationState {
            .valid = true,
            .message = std::nullopt
        };
    }

    void Shader::bind() {
        GPUResource::bind();
        glUseProgram(this->getId());
    }

    void Shader::unbind() {
        GPUResource::unbind();
        glUseProgram(0);
    }

}