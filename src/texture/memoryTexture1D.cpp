#include "memoryTexture1D.hpp"

#include <stdexcept>

namespace StructuredGL::Texture {

    MemoryTexture1D::MemoryTexture1D(const std::string& name):
        MemoryTexture(std::move(name), TextureType::T1D) {}

    void MemoryTexture1D::createTexImage(GLint level,
                                         GLint internalFormat,
                                         std::vector<GLsizei> dimensions,
                                         GLint border,
                                         GLenum format,
                                         GLenum type,
                                         const GLvoid* data) {
        if (!this->isBound()) {
            throw std::runtime_error(this->getPrefix() + " Cannot create tex image for unbound texture");
        } else if (dimensions.size() != 1) {
            throw std::runtime_error(this->getPrefix() + " Expected 1 dimension, got " + std::to_string(dimensions.size()));
        }
        glTexImage1D(
            getTextureTypeGLType(this->type),
            level,
            internalFormat,
            dimensions[0],
            border,
            format,
            type,
            data
        );
    }

}