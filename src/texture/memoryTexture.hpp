#pragma once

#ifndef STRUCTURED_GL_MEMORY_TEXTURE_HPP
#define STRUCTURED_GL_MEMORY_TEXTURE_HPP

#include <string>
#include <array>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../gpuResource.hpp"

namespace StructuredGL::Texture {

#define TEXTURE_TYPES \
    X(T1D, "TEXTURE_1D", GL_TEXTURE_1D) \
    X(T2D, "TEXTURE_2D", GL_TEXTURE_2D) \
    X(T3D, "TEXTURE_3D", GL_TEXTURE_3D)

#define X(type, name, glType) name,
    static constexpr std::array<const char*, 3> _textureTypeName = {
        TEXTURE_TYPES
    };
#undef X

#define X(type, name, glType) glType,
    static constexpr std::array<GLuint, 3> _textureTypeGL = {
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
    constexpr GLuint getTextureTypeGLType(TextureType type) {
        return _textureTypeGL[static_cast<size_t>(type)];
    }

    class MemoryTexture: public GPUResource {
    public:
        MemoryTexture(const std::string& name, TextureType type);
        ~MemoryTexture() noexcept;

        void bind() override;
        void unbind() override;

        ValidationState validate() const override;

        TextureType getType() const {
            return this->type;
        }

        void setTexParameterf(GLuint paramName,
                              GLfloat value);
        
        void setTexParameteri(GLuint paramName,
                              GLint value);

    protected:
        virtual void createTexImage(GLuint level,
                            GLuint internalFormat,
                            GLuint dimensions[],
                            GLuint border,
                            GLuint format,
                            GLuint type,
                            GLbyte pixels[]);

        void setDimensions(glm::vec3 newDimensions) {
            this->dimensions = newDimensions;
        }

        [[nodiscard]]
        inline std::string getPrefix() const;

    private:
        TextureType type;
        glm::vec3 dimensions;
    };

}

#endif //STRUCTURED_GL_MEMORY_TEXTURE_HPP
