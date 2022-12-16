#pragma once

#ifndef STRUCTURED_GL_FBO_HPP
#define STRUCTURED_GL_FBO_HPP

#include <array>
#include <string>
#include <glad/glad.h>

#include "../gpuResource.hpp"

namespace StructuredGL::Buffers {

#define FBO_TYPES \
    X(DRAW_READ, "DRAW_READ", GL_FRAMEBUFFER) \
    X(DRAW, "DRAW", GL_DRAW_FRAMEBUFFER) \
    X(READ, "READ", GL_READ_FRAMEBUFFER)

#define X(type, name, glType) name,
    static constexpr std::array<const char*, 3> _fboTypeName = {
        FBO_TYPES
    };
#undef X

#define X(type, name, glType) glType,
    static constexpr std::array<GLuint, 3> _fboTypeGL = {
        FBO_TYPES
    };
#undef X

#define X(type, name, glType) type,
    enum class FBOType: size_t {
        FBO_TYPES
    };
#undef X

    [[nodiscard]]
    constexpr const char* getFBOTypeName(FBOType type) {
        return _fboTypeName[static_cast<size_t>(type)];
    }

    [[nodiscard]]
    constexpr GLuint getFBOTypeGLType(FBOType type) {
        return _fboTypeGL[static_cast<size_t>(type)];
    }

    class FBO: public GPUResource {
    public:
        FBO(const std::string& name, FBOType type);
        ~FBO() = default;

        void bind() override;
        void unbind() override;

        [[nodiscard]]
        ValidationState validate() const override;
        
//        void attach(const MemoryTexture& texture,
//                    GLuint textureTarget3D,
//                    GLuint attachment,
//                    GLuint level);

    private:
        FBOType type;
    };

}

#endif // STRUCTURED_GL_FBO_HPP
