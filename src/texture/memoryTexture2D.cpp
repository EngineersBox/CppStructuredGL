#include "memoryTexture2D.hpp"

#include <stdexcept>

namespace StructuredGL::Texture {

    MemoryTexture2D::MemoryTexture2D(const std::string& name):
        MemoryTexture(std::move(name), TextureType::T2D) {}

    void MemoryTexture2D::createTexImage(GLint level,
                                         GLint internalFormat,
                                         std::vector<GLsizei> dimensions,
                                         GLint border,
                                         GLenum format,
                                         GLenum type,
                                         const GLvoid* data) {
        if (!this->isBound()) {
            throw std::runtime_error(this->getPrefix() + " Cannot create tex image for unbound texture");
        } else if (dimensions.size() != 2) {
            throw std::runtime_error(this->getPrefix() + " Expected 2 dimension, got " + std::to_string(dimensions.size()));
        }
        glTexImage2D(
            getTextureTypeGLType(this->type),
            level,
            internalFormat,
            dimensions[0],
            dimensions[1],
            border,
            format,
            type,
            data
        );
    }

}