
#include <xe/sfx/Source.hpp>
#include <AL/al.h>
#include "BufferAL.hpp"

namespace xe { namespace sfx { namespace al {
    class SourceAL : public Source {
    public:
        SourceAL();
        virtual ~SourceAL();
        
        virtual SourceDesc getDesc() const override;
        virtual void setDesc(const SourceDesc &desc) override;
        
        virtual Buffer* getBuffer() const override;
        
        virtual void setBuffer(Buffer* buffer) override;
        
    private:
        SourceDesc m_desc;
        BufferAL *m_buffer = nullptr;
    };
}}}
