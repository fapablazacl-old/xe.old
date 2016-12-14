
#include "ImageFI.hpp"

namespace xe { namespace gfx { 
    ImageFI::ImageFI(FIBITMAP *bitmap) 
        : m_bitmap(bitmap) {
        assert(m_bitmap);
    }
    
    ImageFI::~ImageFI() {
        assert(m_bitmap);
        ::FreeImage_Unload(m_bitmap);
    }
    
    ImageDesc ImageFI::getDesc() const {
        assert(m_bitmap);
        
        ImageDesc desc;
    
        desc.width = ::FreeImage_GetWidth(m_bitmap);
        desc.height = ::FreeImage_GetHeight(m_bitmap);
        desc.depth = 0;
        desc.type = ImageType::Img2D;
        
        // TODO: Determine more accurately the format
        switch (FreeImage_GetBPP(m_bitmap)) {
        case 16:
            desc.format = PixelFormat::R5G6B5;
            break;
            
        case 24:
            desc.format = PixelFormat::R8G8B8;
            break;
            
        case 32:
            desc.format = PixelFormat::B8G8R8A8;
            break;
            
        default:
            assert(false);
        }
        
        return desc;
    }
    
    void* ImageFI::getPointer() {
        assert(m_bitmap);
        
        return ::FreeImage_GetBits(m_bitmap);
    }
    
    const void* ImageFI::getPointer() const {
        assert(m_bitmap);
        
        return ::FreeImage_GetBits(m_bitmap);
    }
}}
