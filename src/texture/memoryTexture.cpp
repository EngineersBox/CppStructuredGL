#include "memoryTexture.hpp"

#include <stdexcept>

namespace StructuredGL::Texture {

    MemoryTexture::MemoryTexture(const std::string &name, StructuredGL::Texture::TextureType type):
    type(type),
    dimensions(),
    GPUResource(std::move(name)) {
        GLuint target[0];
        glGenTextures(1, target);
        this->setId(target[0]);
    }

    MemoryTexture::~MemoryTexture() noexcept {
        if (this->isBound()) {
            glBindTexture(
                getTextureTypeGLType(this->type),
                0
            );
            this->setBound(false);
        }
        GLuint target[] = { this->getId() };
        glDeleteTextures(1, target);
    }

    ValidationState MemoryTexture::validate() const {
        if (!this->getId()) {
            return ValidationState {
                .valid = false,
                .message = std::optional<std::string>(std::string("Unable to create texture of type ") + getTextureTypeName(this->type))
            };
        }
        return GPUResource::validate();
    }

    void MemoryTexture::bind() {
        GPUResource::bind();
        glBindTexture(
            getTextureTypeGLType(this->type),
            this->getId()
        );
    }

    void MemoryTexture::unbind() {
        GPUResource::unbind();
        glBindTexture(
            getTextureTypeGLType(this->type),
            0
        );
    }

    std::string MemoryTexture::getPrefix() const {
        return "[Texture: " + this->getName()
            + " Type: " + getTextureTypeName(this->type)
            + " Id: " + std::to_string(this->getId())
            + "]";
    }

    void MemoryTexture::setTexParameterf(GLuint paramName,
                                         GLfloat value) {
        if (!this->isBound()) {
            throw std::runtime_error(this->getPrefix() + " Cannot set parameter on unbound texture");
        }
        glTexParameterf(
            getTextureTypeGLType(this->type),
            paramName,
            value
        );
    }

    void MemoryTexture::setTexParameteri(GLuint paramName,
                                         GLint value) {
        if (!this->isBound()) {
            throw std::runtime_error(this->getPrefix() + " Cannot set parameter on unbound texture");
        }
        glTexParameteri(
            getTextureTypeGLType(this->type),
            paramName,
            value
        );
    }

    void MemoryTexture::createTexImage(GLint level,
                                       GLint internalFormat,
                                       std::vector<GLsizei> dimensions,
                                       GLint border,
                                       GLenum format,
                                       GLenum type,
                                       const GLvoid* data) {
        throw std::runtime_error(this->getPrefix() + " Unimplemented method: createTexImage");
    }
}