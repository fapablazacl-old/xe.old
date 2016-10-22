
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

    MeshPtr Device::createMesh(const MeshFormat *format, BufferPtr buffer) {
        std::vector<BufferPtr> buffers;

        buffers.push_back(std::move(buffer));

        return this->createMesh(format, std::move(buffers));
    }

    MeshPtr Device::createMesh(const MeshFormat *format, std::vector<BufferCreateParams> createParams) {
        std::vector<BufferPtr> buffers;

        // vertex attribute buffers
        for (int i=0; i<format->getAttribCount(); i++) {
            const auto attrib = format->getAttrib(i);
            const auto params = createParams[attrib->bufferIndex];
            
            auto buffer = this->createBuffer(attrib->bufferType, params.size, params.data);
            
            buffers.push_back(std::move(buffer));
        }
        
        return this->createMesh(format, std::move(buffers));
    }
}}
