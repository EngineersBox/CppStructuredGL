#include "ebo.hpp"

namespace StructuredGL::Buffers {

    EBO::EBO(const std::string& name):
        DataBuffer(std::move(name), DataBufferType::EAB) {}

    EBO::EBO(): EBO(getDataBufferTypeName(DataBufferType::EAB)) {}

}