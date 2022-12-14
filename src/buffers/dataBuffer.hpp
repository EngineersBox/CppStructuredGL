#pragma once

#ifndef STRUCTUREDGL_DATABUFFER_HPP
#define STRUCTUREDGL_DATABUFFER_HPP

#include <array>
#include <glad/glad.h>

#include "../gpuResource.hpp"

namespace StructuredGL::Buffers {

#define BUFFER_TYPES \
X(VAB, "VERTEX_ARRAY_BUFFER", GL_ARRAY_BUFFER) \
X(ACB, "ATOMIC_COUNTER_BUFFER", GL_ATOMIC_COUNTER_BUFFER) \
X(CRB, "COPY_READ_BUFFER", GL_COPY_READ_BUFFER) \
X(CWB, "COPY_WRITE_BUFFER", GL_COPY_WRITE_BUFFER) \
X(DIIB, "DISPATCH_INDIRECT_BUFFER", GL_DISPATCH_INDIRECT_BUFFER) \
X(DRIB, "DRAW_INDIRECT_BUFFER", GL_DRAW_INDIRECT_BUFFER) \
X(EAB, "ELEMENT_ARRAY_BUFFER", GL_ELEMENT_ARRAY_BUFFER) \
X(PPB, "PIXEL_PACK_BUFFER", GL_PIXEL_PACK_BUFFER) \
X(PUB, "PIXEL_UNPACK_BUFFER", GL_PIXEL_UNPACK_BUFFER) \
X(QUB, "QUERY_BUFFER", GL_QUERY_BUFFER) \
X(SSB, "SHADER_STORAGE_BUFFER", GL_SHADER_STORAGE_BUFFER) \
X(TEB, "TEXTURE_BUFFER", GL_TEXTURE_BUFFER) \
X(TFB, "TRANSFORM_FEEDBACK_BUFFER", GL_TRANSFORM_FEEDBACK_BUFFER) \
X(UNB, "UNIFORM_BUFFER", GL_UNIFORM_BUFFER)

#define X(type, name, glType) name,
    static constexpr std::array<const char*, 14> _bufferTypeName = {
        BUFFER_TYPES
    };
#undef X

#define X(type, name, glType) glType,
    static constexpr std::array<GLuint, 14> _bufferTypeGL = {
        BUFFER_TYPES
    };
#undef X

#define X(type, name, glType) type,
    enum class DataBufferType: size_t {
        SHADER_TYPES
    };
#undef X

    [[nodiscard]]
    constexpr const char* getDataBufferTypeName(DataBufferType type) {
        return _bufferTypeName[static_cast<size_t>(type)];
    }

    [[nodiscard]]
    constexpr GLuint getDataBufferTypeGLType(DataBufferType type) {
        return _bufferTypeGL[static_cast<size_t>(type)];
    }

    class DataBuffer: public GPUResource {
    public:
        DataBuffer(DataBufferType type);
        ~DataBuffer() override;

        void bind() override;
        void unbind() override;

        void setData(GLsizeiptr size, const GLvoid* data, GLenum usage);

        [[nodiscard]]
        constexpr DataBufferType getType() const {
            return this->type;
        }
    private:
        [[nodiscard]]
        inline std::string getPrefix() const;

        DataBufferType type;
    };

}


#endif //STRUCTUREDGL_DATABUFFER_HPP
