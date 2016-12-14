
#include "ImageLoaderFI.hpp"
#include "ImageFI.hpp"

namespace xe { namespace gfx { 

    ImageLoaderFI::ImageLoaderFI() {
        ::FreeImage_Initialise();
    }
    
    ImageLoaderFI::~ImageLoaderFI() {
        ::FreeImage_DeInitialise();
    }
    
    bool ImageLoaderFI::tryLoad(xe::Stream *stream) {
        assert(stream);
        
        return false;
    }
    
    unsigned StreamRead (void *buffer, unsigned size, unsigned count, fi_handle handle) {
        Stream *stream = (Stream*) handle;
        
        assert(stream);
        assert(stream->isReadable());
        
        return stream->read(buffer, size * count);
    }
    
    unsigned StreamWrite (void *buffer, unsigned size, unsigned count, fi_handle handle) {
        Stream *stream = (Stream*) handle;
        
        assert(stream);
        assert(stream->isWrittable());
        
        return stream->write(buffer, size * count);
    }
    
    int StreamSeek(fi_handle handle, long offset, int origin) {
        Stream *stream = (Stream*) handle;
        
        assert(stream);
        
        StreamOffset position;
        
        switch (origin) {
        case SEEK_CUR: 
            position = StreamOffset::Current; 
            break;
            
        case SEEK_SET:
            position = StreamOffset::Set; 
            break;
            
        case SEEK_END:
            position = StreamOffset::End; 
            break;
            
        default:
            assert(false);
        }
        
        return stream->seek(offset, position);
    }
    
    long StreamTell(fi_handle handle) {
        Stream *stream = (Stream*) handle;
        
        assert(stream);
        
        return stream->tell();
    }
    
    ImagePtr ImageLoaderFI::load(xe::Stream *stream) {
        assert(stream);
        
        FreeImageIO io;
        io.read_proc = StreamRead;
        io.write_proc = StreamWrite;
        io.seek_proc = StreamSeek;
        io.tell_proc = StreamTell;
        
        FIBITMAP *bitmap = ::FreeImage_LoadFromHandle(FIF_UNKNOWN, &io, (fi_handle)stream);
        
        if (bitmap) {
            return std::make_unique<ImageFI>(bitmap);
        } else {
            return ImagePtr();
        }
    }
}}
