
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
        assert(buffer);
        
        std::vector<BufferPtr> buffers;
        
        buffers.push_back(std::move(buffer));
        
        return this->createSubset(format, std::move(buffers), BufferPtr());
    }
    
    SubsetPtr Device::createSubset(const SubsetFormat *format, const BufferDesc &desc) {
        assert(format);
        assert(desc);
        
        std::vector<BufferDesc> descs = {desc};
        
        return this->createSubset(format, std::move(descs));
    }
    
    SubsetPtr Device::createSubset(const SubsetFormat *format, const std::vector<BufferDesc> &descs, const BufferDesc &indexDesc) {
        assert(format);
        assert(descs.size() > 0);
        
        std::vector<BufferPtr> buffers;

        for (int i=0; i<descs.size(); i++) {
            auto &desc = descs[i];
            auto buffer = this->createBuffer(xe::gfx::BufferType::Vertex, desc.size, desc.data);
            
            buffers.push_back(std::move(buffer));
        }
        
        BufferPtr indexBuffer;
        
        if (indexDesc) {
            indexBuffer = this->createBuffer(xe::gfx::BufferType::Index, indexDesc.size, indexDesc.data);
        }
        
        return this->createSubset(format, std::move(buffers), std::move(indexBuffer));
    }
}}
