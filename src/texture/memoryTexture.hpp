#pragma once

#ifndef STRUCTURED_GL_MEMORY_TEXTURE_HPP
#define STRUCTURED_GL_MEMORY_TEXTURE_HPP

#include <string>
#include <array>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "../gpuResource.hpp"
#include "../utils/preprocessor.hpp"

namespace StructuredGL::Texture {

#define TEXTURE_TYPES \
    X(T1D, "TEXTURE_1D", GL_TEXTURE_1D) \
    X(T2D, "TEXTURE_2D", GL_TEXTURE_2D) \
    X(T3D, "TEXTURE_3D", GL_TEXTURE_3D)

#define X(type, name, glType) name,
    static constexpr std::array<const char*, NUM_ARGS(TEXTURE_TYPES)> _textureTypeName = {
        TEXTURE_TYPES
    };
#undef X

#define X(type, name, glType) glType,
    static constexpr std::array<GLenum, NUM_ARGS(TEXTURE_TYPES)> _textureTypeGL = {
        TEXTURE_TYPES
    };
#undef X

#define X(type, name, glType) type,
    enum class TextureType: size_t {
        TEXTURE_TYPES
    };
#undef X

    [[nodiscard]]
    constexpr const char* getTextureTypeName(TextureType type) {
        return _textureTypeName[static_cast<size_t>(type)];
    }

    [[nodiscard]]
    constexpr GLenum getTextureTypeGLType(TextureType type) {
        return _textureTypeGL[static_cast<size_t>(type)];
    }

    class MemoryTexture: public GPUResource {
    public:
        MemoryTexture(const std::string& name, TextureType type);
        ~MemoryTexture() noexcept override;

        void bind() override;
        void unbind() override;

        [[nodiscard]]
        ValidationState validate() const override;

        [[nodiscard]]
        TextureType getType() const {
            return this->type;
        }

        void setTexParameterf(GLuint paramName,
                              GLfloat value);

        void setTexParameteri(GLuint paramName,
                              GLint value);

    protected:
        virtual void createTexImage(GLint level,
                                    GLint internalFormat,
                                    std::vector<GLsizei> dimensions,
                                    GLint border,
                                    GLenum format,
                                    GLenum type,
                                    const GLvoid* data);

        void setDimensions(glm::vec3 newDimensions) {
            this->dimensions = newDimensions;
        }

        [[nodiscard]]
        std::string getPrefix() const;

        TextureType type;
        glm::vec3 dimensions;
    };

}

#endif //STRUCTURED_GL_MEMORY_TEXTURE_HPP
