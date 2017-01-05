
#include "SubsetFormat.hpp"

#include <cassert>
#include <map>
#include <algorithm>

namespace xe {

    struct SubsetFormat::Private {
        std::vector<MeshAttrib> attribs;
        std::set<int> bufferIndices;
        std::map<int, std::vector<MeshAttrib>> indexedAttribs;
    };

    SubsetFormat::SubsetFormat(std::initializer_list<MeshAttrib> attribs) 
        : m_impl(new SubsetFormat::Private()) {

        for (auto &attrib : attribs) {
            m_impl->attribs.push_back(attrib);
            
            m_impl->bufferIndices.insert(attrib.bufferIndex);
            m_impl->indexedAttribs[attrib.bufferIndex].push_back(attrib);
        }
    }

    SubsetFormat::~SubsetFormat() {
        delete m_impl;
    }

    std::size_t SubsetFormat::getAttribCount() const {
        assert(m_impl);

        return m_impl->attribs.size();
    }

    const MeshAttrib* SubsetFormat::getAttrib(const std::size_t index) const {
        assert(m_impl);

        return &m_impl->attribs[index];
    }

    const std::set<int>& SubsetFormat::getBufferIndices() const {
        assert(m_impl);

        return m_impl->bufferIndices;
    }

    const std::vector<MeshAttrib>& SubsetFormat::getAttribs(const int bufferIndex) const {
        assert(m_impl);

        return m_impl->indexedAttribs[bufferIndex];
    }
}
