#pragma once

#ifndef STRUCTURED_GL_VAO_HPP
#define STRUCTURED_GL_VAO_HPP

#include <array>
#include <glad/glad.h>
#include "../gpuResource.hpp"

namespace StructuredGL::Buffers {

    class VAO: public GPUResource {
    public:
        VAO(const std::string& name);
        ~VAO();

        void bind() override;
        void unbind() override;

        [[nodiscard]]
        ValidationState validate() const override;
    };

}

#endif // STRUCTURED_GL_VAO_HPP
