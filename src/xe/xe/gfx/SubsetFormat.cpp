
#include "SubsetFormat.hpp"

#include <cassert>
#include <map>
#include <algorithm>

namespace xe {

    struct SubsetFormat::Private {
        std::vector<SubsetAttrib> fields;
        std::set<int> bufferIndices;
        std::map<int, std::vector<SubsetAttrib>> indexedAttribs;
    };

    SubsetFormat::SubsetFormat() : m_impl(new SubsetFormat::Private()) {}

    SubsetFormat::SubsetFormat(std::initializer_list<SubsetAttrib> fields) 
        : m_impl(new SubsetFormat::Private()) {

        for (auto &attrib : fields) {
            m_impl->fields.push_back(attrib);
            
            m_impl->bufferIndices.insert(attrib.bufferIndex);
            m_impl->indexedAttribs[attrib.bufferIndex].push_back(attrib);
        }
    }

    SubsetFormat::SubsetFormat(const SubsetFormat &other) {
        *this = other;
    }

    SubsetFormat::~SubsetFormat() {
        delete m_impl;
    }

    std::size_t SubsetFormat::getAttribCount() const {
        assert(m_impl);

        return m_impl->fields.size();
    }

    const SubsetAttrib& SubsetFormat::getAttrib(const std::size_t index) const {
        assert(m_impl);
        assert(index >= 0);
        assert(index < this->getAttribCount());

        return m_impl->fields[index];
    }

    const std::set<int>& SubsetFormat::getBufferIndices() const {
        assert(m_impl);

        return m_impl->bufferIndices;
    }

    const std::vector<SubsetAttrib>& SubsetFormat::getAttribArray(const int bufferIndex) const {
        assert(m_impl);

        return m_impl->indexedAttribs[bufferIndex];
    }

    SubsetFormat& SubsetFormat::operator= (const SubsetFormat &other) {
        m_impl->fields = other.m_impl->fields;
        m_impl->bufferIndices = other.m_impl->bufferIndices;
        m_impl->indexedAttribs = other.m_impl->indexedAttribs;

        return *this;
    }
}
