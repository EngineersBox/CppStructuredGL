#include "gpuResource.hpp"

#include <stdexcept>

namespace StructuredGL {

    GPUResource::GPUResource(const std::string& name): name(name) {}

    GPUResource::~GPUResource() {}

    void GPUResource::bind() {
        if (this->id == GPUResource::UNINITIALIZED_ID) {
            throw std::runtime_error("Cannot bind uninitialized resource \"" + this->name + "\"");
        } else if (this->bound) {
            throw std::runtime_error("Resource \"" + this->name + "\" is already bound");
        }
        this->bound = true;
    }

    void GPUResource::unbind() {
        if (this->id == GPUResource::UNINITIALIZED_ID) {
            throw std::runtime_error("Cannot unbind uninitialized resource \"" + this->name + "\"");
        } else if (!this->bound) {
            throw std::runtime_error("Resource \"" + this->name + "\" is not bound");
        }
        this->bound = false;
    }

}