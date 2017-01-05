
#include "Device.hpp"

namespace xe {
    void GraphicsDevice::setUniform(const UniformFormat* format, const void *uniforms) {
        assert(format && format->attribs.size() > 0);
        assert(uniforms);
        
        auto uniform = static_cast<const std::uint8_t*>(uniforms);

        for (const UniformDescriptor &desc : format->attribs) {
            this->setUniform(desc, uniform);

            const size_t size = desc.getSize();

            uniform += size;
        }
    }

    SubsetPtr GraphicsDevice::createSubset(const SubsetDesc &subsetDesc) {

        std::vector<BufferPtr> buffers;

        for (int i=0; i<subsetDesc.buffersDescs.size(); i++) {
            auto &desc = subsetDesc.buffersDescs[i];
            auto buffer = this->createBuffer(xe::BufferType::Vertex, desc.size, desc.data);
            
            buffers.push_back(std::move(buffer));
        }
        
        BufferPtr indexBuffer;
        
        if (subsetDesc.indexBufferDesc) {
            indexBuffer = this->createBuffer(xe::BufferType::Index, subsetDesc.indexBufferDesc.size, subsetDesc.indexBufferDesc.data);
        }
        
        return this->createSubset(subsetDesc.format, std::move(buffers), subsetDesc.indexType, std::move(indexBuffer));
    }
}
