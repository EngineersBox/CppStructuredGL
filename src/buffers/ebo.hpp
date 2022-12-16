#pragma once

#ifndef STRUCTURED_GL_EBO_HPP
#define STRUCTURED_GL_EBO_HPP

#include <string>
#include <glad/glad.h>

#include "dataBuffer.hpp"

namespace StructuredGL::Buffers {

    class EBO: public DataBuffer {
    public:
        EBO(const std::string& name);
        EBO();
        ~EBO() = default;

    };

}

#endif // STRUCTURED_GL_EBO_HPP
