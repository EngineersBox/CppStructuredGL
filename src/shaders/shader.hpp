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

#define SHADER_TYPES \
X(VERTEX, "VERTEX", GL_VERTEX_SHADER) \
X(FRAGMENT, "FRAGMENT", GL_FRAGMENT_SHADER) \
X(GEOMETRY, "GEOMETRY", GL_GEOMETRY_SHADER) \
X(TESSELLATION_EVALUATION, "TESSELLATION_EVALUATION", GL_TESS_EVALUATION_SHADER) \
X(TESSELLATION_CONTROL, "TESSELLATION_CONTROL", GL_TESS_CONTROL_SHADER)

#define X(type, name, glType) name,
    static constexpr std::array<const char*, 5> _shaderTypeName = {
        SHADER_TYPES
    };
#undef X

#define X(type, name, glType) glType,
    static constexpr std::array<GLuint, 5> _shaderTypeGL = {
        SHADER_TYPES
    };
#undef X

#define X(type, name, glType) type,
    enum class ShaderType: size_t {
        SHADER_TYPES
    };
#undef X

    [[nodiscard]]
    constexpr const char* getShaderTypeName(ShaderType type) {
        return _shaderTypeName[static_cast<size_t>(type)];
    }

    [[nodiscard]]
    constexpr GLuint getShaderTypeGLType(ShaderType type) {
        return _shaderTypeGL[static_cast<size_t>(type)];
    }

    struct ShaderData {
        ShaderType type;
        std::string file;
    };

    struct ShaderValidationState {
        bool valid = false;
        std::optional<std::string> message = std::nullopt;
    };

    class Shader: public GPUResource {
    public:
        Shader(std::string name, std::initializer_list<ShaderData> shaderData);
        ~Shader() override;

        void bind() override;
        void unbind() override;

        ShaderValidationState validate();

    private:
        [[nodiscard]]
        GLuint createShader(const ShaderData& data) const;

        void link(const std::unordered_map<ShaderType, GLuint>& modules) const;

        [[nodiscard]]
        inline std::string getPrefix() const;

        const std::string name;
    };

}

#endif // STRUCTURED_GL_SHADER_HPP
