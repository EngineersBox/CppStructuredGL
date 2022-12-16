#include "vao.hpp"

#include <stdexcept>

namespace StructuredGL::Buffers {

    VAO::VAO(const std::string& name):
        GPUResource(name) {
        GLuint target[1];
        glGenVertexArrays(1, target);
        this->setId(target[0]);
    }

    VAO::~VAO() {
        if (this->isBound()) {
            glBindVertexArray(0);
            this->setBound(false);
        }
        GLuint target[] = { this->getId() };
        glDeleteVertexArrays(1, target);
    }

    ValidationState VAO::validate() const {
        if (!this->getId()) {
            return ValidationState{
                .valid = false,
                .message = std::optional<std::string>("[Buffer: " + this->getName() + "] Unable to create buffer")
            };
        }
        return GPUResource::validate();
    }

    void VAO::bind() {
        GPUResource::bind();
        glBindVertexArray(this->getId());
    }

    void VAO::unbind() {
        GPUResource::unbind();
        glBindVertexArray(0);
    }

}