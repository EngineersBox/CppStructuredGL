#pragma once

#ifndef STRUCTURED_GL_SHADER_HPP
#define STRUCTURED_GL_SHADER_HPP

#include <initializer_list>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <unordered_map>

#include "../gpuResource.hpp"

namespace StructuredGL::Shaders {

    struct ShaderData {
        GLuint type;
        std::string file;
    };

    struct ShaderValidationState {
        bool valid = false;
        std::optional<std::string> message = std::nullopt;
    };

    class Shader: public GPUResource {
    public:
        Shader(const std::string& name, std::initializer_list<ShaderData> shaderData);
        ~Shader() override;

        void bind() override;
        void unbind() override;

        ShaderValidationState validate();

    private:
        [[nodiscard]]
        GLuint createShader(const ShaderData& data) const;

        void link(const std::unordered_map<GLuint, GLuint>& modules) const;

        [[nodiscard]]
        inline std::string getPrefix() const;

        const std::string name;
    };

}

#endif // STRUCTURED_GL_SHADER_HPP
