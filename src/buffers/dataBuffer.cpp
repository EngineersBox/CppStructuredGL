#include "dataBuffer.hpp"

#include <stdexcept>

namespace StructuredGL::Buffers {

    DataBuffer::DataBuffer(DataBufferType type):
        GPUResource(getDataBufferTypeName(type)) {
        GLuint name[1];
        glGenBuffers(1, name);
        if (!name[0]) {
            throw std::runtime_error(this->getPrefix() + "Unable to create buffer");
        }
        this->setId(name[0]);
    }

    DataBuffer::~DataBuffer() {
        if (this->isBound()) {
            glBindBuffer(
                getDataBufferTypeGLType(this->type),
                0
            );
            this->setBound(false);
        }
        const GLuint buffers[] = { this->getId() };
        glDeleteBuffers(1, buffers);
    }

    std::string DataBuffer::getPrefix() const {
        return "[Buffer: " + this->getName() + " Id: " + std::to_string(this->getId()) + "]";
    }

    void DataBuffer::setData(GLsizeiptr size,
                             const GLvoid* data,
                             GLenum usage) {
        if (!this->isBound()) {
            throw std::runtime_error(this->getPrefix() + " Cannot set data for unbound buffer");
        }
        glBufferData(
            getDataBufferTypeGLType(this->type),
            size,
            data,
            usage
        );
    }

    void DataBuffer::bind() {
        GPUResource::bind();
        glBindBuffer(
            getDataBufferTypeGLType(this->type),
            this->getId()
        );
    }

    void DataBuffer::unbind() {
        GPUResource::unbind();
        glBindBuffer(
            getDataBufferTypeGLType(this->type),
            0
        );
    }

}