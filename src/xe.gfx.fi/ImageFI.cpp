
#include "ImageFI.hpp"

#include <xe/DataType.hpp>

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
        desc.type = ImageType::Img2D;
        
        FREE_IMAGE_TYPE type = FreeImage_GetImageType(m_bitmap);
        
        /*
    FIT_UNKNOWN = 0,	//! unknown type
	FIT_BITMAP  = 1,	//! standard image			: 1-, 4-, 8-, 16-, 24-, 32-bit
	FIT_UINT16	= 2,	//! array of unsigned short	: unsigned 16-bit
	FIT_INT16	= 3,	//! array of short			: signed 16-bit
	FIT_UINT32	= 4,	//! array of unsigned long	: unsigned 32-bit
	FIT_INT32	= 5,	//! array of long			: signed 32-bit
	FIT_FLOAT	= 6,	//! array of float			: 32-bit IEEE floating point
	FIT_DOUBLE	= 7,	//! array of double			: 64-bit IEEE floating point
	FIT_COMPLEX	= 8,	//! array of FICOMPLEX		: 2 x 64-bit IEEE floating point
	FIT_RGB16	= 9,	//! 48-bit RGB image			: 3 x 16-bit
	FIT_RGBA16	= 10,	//! 64-bit RGBA image		: 4 x 16-bit
	FIT_RGBF	= 11,	//! 96-bit RGB float image	: 3 x 32-bit IEEE floating point
	FIT_RGBAF	= 12	//! 128-bit RGBA float image	: 4 x 32-bit IEEE floating point
    */
        
        unsigned bpp = FreeImage_GetBPP(m_bitmap);
        
        switch (type) {
        case FIT_BITMAP:
            switch (bpp) {
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
        
            break;
        
        case FIT_RGB16: 
            assert(bpp == 48);
            desc.format = PixelFormat::R16G16B16;
            break;
            
        case FIT_RGBA16:
            assert(bpp == 64);
            desc.format = PixelFormat::R16G16B16A16;
            break;
            
        default:
            std::cout << type << std::endl;
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
