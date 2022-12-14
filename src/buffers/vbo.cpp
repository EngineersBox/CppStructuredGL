#include "vbo.hpp"

#include <stdexcept>

namespace StructuredGL::Buffers {

    VBO::VBO(std::string name):
        DataBuffer(std::move(name), DataBufferType::VAB) {}

    VBO::VBO(): VBO(getDataBufferTypeName(DataBufferType::VAB)) {}

    VBO::~VBO() {
        DataBuffer::~DataBuffer();
    }

    void VBO::enableAttributeAndPointer(GLuint index,
                                        GLint size,
                                        GLenum type,
                                        GLboolean normalized,
                                        GLsizei stride,
                                        const GLvoid * pointer,
                                        bool autoBindAndUnbind) {
        if (!autoBindAndUnbind && !this->isBound()) {
            throw std::runtime_error(this->getPrefix() + " Cannot enable vertex attribute on unbound resource");
        }
        if (autoBindAndUnbind) {
            this->bind();
        }
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            size,
            type,
            normalized,
            stride,
            pointer
        );
        if (autoBindAndUnbind) {
            this->unbind();
        }
    }

}