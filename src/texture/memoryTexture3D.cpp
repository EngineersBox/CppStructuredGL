#include "memoryTexture3D.hpp"

#include <stdexcept>

namespace StructuredGL::Texture {

    MemoryTexture3D::MemoryTexture3D(const std::string& name):
        MemoryTexture(std::move(name), TextureType::T2D) {}

    void MemoryTexture3D::createTexImage(GLint level,
                                         GLint internalFormat,
                                         std::vector<GLsizei> dimensions,
                                         GLint border,
                                         GLenum format,
                                         GLenum type,
                                         const GLvoid* data) {
        if (!this->isBound()) {
            throw std::runtime_error(this->getPrefix() + " Cannot create tex image for unbound texture");
        } else if (dimensions.size() != 3) {
            throw std::runtime_error(this->getPrefix() + " Expected 3 dimension, got " + std::to_string(dimensions.size()));
        }
        glTexImage3D(
            getTextureTypeGLType(this->type),
            level,
            internalFormat,
            dimensions[0],
            dimensions[1],
            dimensions[2],
            border,
            format,
            type,
            data
        );
    }

}