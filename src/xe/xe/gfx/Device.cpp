
#include "Device.hpp"

namespace xe { namespace gfx {
    void Device::setUniform(const UniformFormat* format, const void *uniforms) {
        assert(uniforms);
        assert(format->attribs.size() > 0);

        auto uniform = static_cast<const std::uint8_t*>(uniforms);

        for (const UniformDescriptor &desc : format->attribs) {
            this->setUniform(desc, uniform);

            const size_t size = desc.getSize();

            uniform += size;
        }
    }

    MeshPtr Device::createMesh(const MeshFormat &format, BufferPtr buffer) {
        std::vector<BufferPtr> buffers;

        buffers.push_back(std::move(buffer));

        return this->createMesh(format, std::move(buffers));
    }

    MeshPtr Device::createMesh(const MeshFormat &format, std::vector<BufferCreateParams> createParams) {
        std::vector<BufferPtr> buffers;

        // vertex attribute buffers
        for (const MeshAttrib &attrib : format.attribs) {
            BufferCreateParams params = createParams[attrib.bufferIndex];
            buffers.push_back(this->createBuffer(BufferType::Vertex, params.size, params.data));
        }

        // index buffer
        if (format.indexAttrib.isValid()) {
            BufferCreateParams params = createParams[format.indexAttrib.bufferIndex];
            buffers.push_back(this->createBuffer(BufferType::Index, params.size, params.data));
        }

        return this->createMesh(format, std::move(buffers));
    }
}}
