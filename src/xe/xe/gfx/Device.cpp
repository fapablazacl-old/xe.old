
#include "Device.hpp"

namespace xe { namespace gfx {
    void Device::setUniform(const UniformFormat* format, const void *uniforms) {
        assert(format && format->attribs.size() > 0);
        assert(uniforms);
        
        auto uniform = static_cast<const std::uint8_t*>(uniforms);

        for (const UniformDescriptor &desc : format->attribs) {
            this->setUniform(desc, uniform);

            const size_t size = desc.getSize();

            uniform += size;
        }
    }

    SubsetPtr Device::createSubset(const SubsetFormat *format, BufferPtr buffer) {
        assert(format);
        
        std::vector<BufferPtr> buffers;

        buffers.push_back(std::move(buffer));

        return this->createSubset(format, std::move(buffers));
    }

    SubsetPtr Device::createSubset(const SubsetFormat *format, std::vector<BufferCreateParams> createParams) {
        assert(format);
        
        std::vector<BufferPtr> buffers;

        for (int i=0; i<createParams.size(); i++) {
            auto &params = createParams[i];
            auto buffer = this->createBuffer(params.type, params.size, params.data);
            
            buffers.push_back(std::move(buffer));
        }
        
        return this->createSubset(format, std::move(buffers));
    }
}}
