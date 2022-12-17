#pragma once

#ifndef STRUCTURED_GL_GPU_RESOURCE_HPP
#define STRUCTURED_GL_GPU_RESOURCE_HPP

#include <glad/glad.h>
#include <string>
#include <optional>

#ifndef STRUCTURED_GL_BIND_CHECK
#define STRUCTURED_GL_BIND_CHECK true
#endif

namespace StructuredGL {

    struct ValidationState {
        bool valid = true;
        std::optional<std::string> message = std::nullopt;
    };

    class GPUResource {
    public:
        explicit GPUResource(std::string name);
        virtual ~GPUResource() = default;

        virtual void bind();
        virtual void unbind();

        [[nodiscard]]
        virtual ValidationState validate() const;

        [[nodiscard]]
        constexpr GLuint getId() const {
            return this->id;
        }

        [[nodiscard]]
        constexpr bool isBound() const {
            return this->bound;
        }

        [[nodiscard]]
        std::string getName() const& {
            return this->name;
        }

    protected:
        void setBound(bool boundState) {
            this->bound = boundState;
        }

        void setId(GLuint newId) {
            this->id = newId;
        }

        static constexpr GLuint UNINITIALIZED_ID = 0;

    private:
        const std::string name;
        GLuint id = UNINITIALIZED_ID;
        bool bound = false;
    };

}


#endif // STRUCTURED_GL_GPU_RESOURCE_HPP
