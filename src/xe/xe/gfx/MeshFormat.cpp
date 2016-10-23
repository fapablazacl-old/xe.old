
#include "MeshFormat.hpp"

#include <cassert>
#include <map>
#include <algorithm>

namespace xe { namespace gfx {

    struct MeshFormat::Private {
        std::vector<MeshAttrib> attribs;
        std::set<int> bufferIndices;
        std::map<int, std::vector<MeshAttrib>> indexedAttribs;
        //std::map<BufferType, std::vector<MeshAttrib>> typedAttribs;
    };

    MeshFormat::MeshFormat(std::initializer_list<MeshAttrib> attribs) 
        : m_impl(new MeshFormat::Private()) {

        for (auto &attrib : attribs) {
            m_impl->attribs.push_back(attrib);
            
            m_impl->bufferIndices.insert(attrib.bufferIndex);
            m_impl->indexedAttribs[attrib.bufferIndex].push_back(attrib);
        }
    }

    MeshFormat::~MeshFormat() {
        delete m_impl;
    }

    std::size_t MeshFormat::getAttribCount() const {
        assert(m_impl);

        return m_impl->attribs.size();
    }

    const MeshAttrib* MeshFormat::getAttrib(const std::size_t index) const {
        assert(m_impl);

        return &m_impl->attribs[index];
    }

    const std::set<int>& MeshFormat::getBufferIndices() const {
        assert(m_impl);

        return m_impl->bufferIndices;
    }

    const std::vector<MeshAttrib>& MeshFormat::getAttribs(const int bufferIndex) const {
        assert(m_impl);

        return m_impl->indexedAttribs[bufferIndex];
    }
}}
