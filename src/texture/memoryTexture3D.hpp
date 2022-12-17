#pragma once

#ifndef STRUCTURED_GL_MEMORY_TEXTURE_3D_HPP
#define STRUCTURED_GL_MEMORY_TEXTURE_3D_HPP

#include <string>
#include <glad/glad.h>
#include <vector>

#include "memoryTexture.hpp"

namespace StructuredGL::Texture {

    class MemoryTexture3D: public MemoryTexture {
    public:
        MemoryTexture3D(const std::string& name);
        ~MemoryTexture3D() noexcept override = default;

        void createTexImage(GLint level,
                            GLint internalFormat,
                            std::vector<GLsizei> dimensions,
                            GLint border,
                            GLenum format,
                            GLenum type,
                            const GLvoid* data) override;
    };

}

#endif // STRUCTURED_GL_MEMORY_TEXTURE_3D_HPP
