#include "gpuResource.hpp"

#include <stdexcept>
#include <utility>

namespace StructuredGL {

    GPUResource::GPUResource(std::string name): name(std::move(name)) {}

    ValidationState GPUResource::validate() const {
        return ValidationState{
            .valid = true,
            .message = std::nullopt
        };
    }

    void GPUResource::bind() {
        if (STRUCTURED_GL_BIND_CHECK && this->id == GPUResource::UNINITIALIZED_ID) {
            throw std::runtime_error("Cannot bind uninitialized resource \"" + this->name + "\"");
        } else if (STRUCTURED_GL_BIND_CHECK && this->bound) {
            throw std::runtime_error("Resource \"" + this->name + "\" is already bound");
        }
        this->bound = true;
    }

    void GPUResource::unbind() {
        if (STRUCTURED_GL_BIND_CHECK && this->id == GPUResource::UNINITIALIZED_ID) {
            throw std::runtime_error("Cannot unbind uninitialized resource \"" + this->name + "\"");
        } else if (STRUCTURED_GL_BIND_CHECK && !this->bound) {
            throw std::runtime_error("Resource \"" + this->name + "\" is not bound");
        }
        this->bound = false;
    }

}