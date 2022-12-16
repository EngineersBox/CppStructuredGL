#include "fbo.hpp"

#include <stdexcept>

namespace StructuredGL::Buffers {


    FBO::FBO(const std::string &name, StructuredGL::Buffers::FBOType type):
        type(type),
        GPUResource(std::move(name)) {
        GLuint target[1];
        glGenFramebuffers(1, target);
        this->setId(target[0]);
    }

    ValidationState FBO::validate() const {
        if (this->getId() != GL_FRAMEBUFFER_COMPLETE) {
            return ValidationState{
                .valid = false,
                .message = std::optional<std::string>("Cannot complete framebuffer generation")
            };
        }
        return GPUResource::validate();
    }

    void FBO::bind() {
        GPUResource::bind();
        glBindFramebuffer(
            getFBOTypeGLType(this->type),
            this->getId()
        );
    }

    void FBO::unbind() {
        GPUResource::unbind();
        glBindFramebuffer(
            getFBOTypeGLType(this->type),
            0
        );
    }

}