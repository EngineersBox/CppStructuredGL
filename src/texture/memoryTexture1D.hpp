#pragma once

#ifndef STRUCTURED_GL_MEMORY_TEXTURE_1D_HPP
#define STRUCTURED_GL_MEMORY_TEXTURE_1D_HPP

#include <string>
#include <glad/glad.h>
#include <vector>

#include "memoryTexture.hpp"

namespace StructuredGL::Texture {

    class MemoryTexture1D: public MemoryTexture {
    public:
        MemoryTexture1D(const std::string& name);
        ~MemoryTexture1D() noexcept override = default;

        void createTexImage(GLint level,
                            GLint internalFormat,
                            std::vector<GLsizei> dimensions,
                            GLint border,
                            GLenum format,
                            GLenum type,
                            const GLvoid* data) override;
    };

}

#endif // STRUCTURED_GL_MEMORY_TEXTURE_1D_HPP
