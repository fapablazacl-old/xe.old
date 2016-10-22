
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
            //m_impl->typedAttribs[attrib.bufferType].push_back(attrib);
        }

        /*
        for (auto &pair : m_impl->typedAttribs) {
            std::sort(pair.second.begin(), pair.second.end(), [](const MeshAttrib &a1, const MeshAttrib &a2) {
                return a1.bufferIndex < a2.bufferIndex;
            });
        }
        */

        assert(this->isValid());
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

    bool MeshFormat::isValid() const {
        assert(m_impl);

        // check correctly classified
        for (int bufferIndex : this->getBufferIndices()) {
            const auto &attribs = this->getAttribs(bufferIndex);

            for (const MeshAttrib &attrib : attribs) {
                
                if (attrib.bufferType == BufferType::Unknown) {
                    return false;
                }
                
                if (attrib.bufferType != attribs[0].bufferType) {
                    return false;
                }
            }
        }

        // check only one index buffer
        auto count = std::count_if(std::begin(m_impl->attribs), std::end(m_impl->attribs), [](const MeshAttrib &attrib) {
            return attrib.bufferType == BufferType::Index;
        });
        
        return count>=0 && count<=1;
    }

    bool MeshFormat::isIndexed() const {
        auto count = std::count_if(std::begin(m_impl->attribs), std::end(m_impl->attribs), [](const MeshAttrib &attrib) {
            return attrib.bufferType == BufferType::Index;
        });

        return count > 0;
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
