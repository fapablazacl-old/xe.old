
#pragma once 

#ifndef __xe_gfx_imagefi_hpp__
#define __xe_gfx_imagefi_hpp__

#include <FreeImage.h>
#include <xe/gfx/Image.hpp>

namespace xe {
    class ImageFI : public Image {
    public:
        explicit ImageFI(FIBITMAP *bitmap);

        virtual ~ImageFI();
        
        virtual ImageDesc getDesc() const override;

        virtual void* getPointer() override;
        
        virtual const void* getPointer() const override;
        
    private:
        FIBITMAP *m_bitmap = nullptr;
    };
}

#endif
