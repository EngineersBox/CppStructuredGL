#pragma once

#ifndef STRUCTUREDGL_VBO_HPP
#define STRUCTUREDGL_VBO_HPP

#include <string>
#include <glad/glad.h>

#include "dataBuffer.hpp"

namespace StructuredGL::Buffers {

    class VBO: protected DataBuffer {
    public:
        VBO(std::string name);
        VBO();
        ~VBO() override;

        void enableAttributeAndPointer(GLuint index,
                                       GLint size,
                                       GLenum type,
                                       GLboolean normalized,
                                       GLsizei stride,
                                       const GLvoid * pointer,
                                       bool autoBindAndUnbind = false);
    };

}

#endif //STRUCTUREDGL_VBO_HPP
