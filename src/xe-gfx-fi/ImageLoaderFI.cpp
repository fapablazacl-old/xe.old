
#include "ImageLoaderFI.hpp"
#include "ImageFI.hpp"

namespace xe {

    void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message) {
        std::cerr << message << std::endl;
        
        if (fif != FIF_UNKNOWN) {
            std::cerr << "Error at parsing format " << FreeImage_GetFormatFromFIF(fif) << std::endl;
        }
    }
    
    unsigned StreamRead (void *buffer, unsigned size, unsigned count, fi_handle handle) {
        Stream *stream = (Stream*) handle;
        
        assert(stream);
        assert(stream->isReadable());
        
        //std::clog << "xe::StreamRead: size=" << size << ", count=" << count << std::endl;
        
        return stream->read(buffer, size, count);
    }
    
    unsigned StreamWrite (void *buffer, unsigned size, unsigned count, fi_handle handle) {
        Stream *stream = (Stream*) handle;
        
        assert(stream);
        assert(stream->isWrittable());
        
        return stream->write(buffer, size * count);
    }
    
    std::ostream& operator<< (std::ostream &os, xe::StreamOffset position) {
        switch (position) {
        case xe::StreamOffset::Current: os << "StreamOffset::Current"; break;
        case xe::StreamOffset::Set: os << "StreamOffset::Set"; break;
        case xe::StreamOffset::End: os << "StreamOffset::End"; break;
        }
        
        return os;
    }
    
    int StreamSeek(fi_handle handle, long offset, int origin) {
        assert(handle);
        
        Stream *stream = (Stream*) handle;
        
        StreamOffset position;
        
        switch (origin) {
        case SEEK_SET:
            assert(offset >= 0);
            
            position = StreamOffset::Set; 
            break;
            
        case SEEK_CUR: 
            position = StreamOffset::Current; 
            break;
            
        case SEEK_END:
            assert(offset == 0);
            position = StreamOffset::End; 
            break;
            
        default:
            assert(false);
        }
        
        //std::clog << "xe::StreamSeek: offset=" << offset << ", origin=" << position << std::endl;
        
        if (stream->seek(offset, position)) {
            return 0;
        } else {
            return 1;
        }
    }
    
    long StreamTell(fi_handle handle) {
        assert(handle);
        
        Stream *stream = (Stream*) handle;
        
        //std::clog << "xe::StreamTell: tell=" << stream->tell() << std::endl;
        
        return stream->tell();
    }

    static FreeImageIO createIO() {
        FreeImageIO io;
        io.read_proc = StreamRead;
        io.write_proc = StreamWrite;
        io.seek_proc = StreamSeek;
        io.tell_proc = StreamTell;
        
        return io;
    }
    
    ImageLoaderFI::ImageLoaderFI() {
        ::FreeImage_Initialise();
        ::FreeImage_SetOutputMessage(FreeImageErrorHandler);
    }
    
    ImageLoaderFI::~ImageLoaderFI() {
        ::FreeImage_SetOutputMessage(NULL);
        ::FreeImage_DeInitialise();
    }

    class ImageProxyFI : public ImageProxy {
    public:
        ImageProxyFI(xe::Stream *stream) : m_stream(stream) {
            assert(stream);
            
            FreeImageIO io = createIO();
            
            m_fif = ::FreeImage_GetFileTypeFromHandle(&io, (fi_handle)stream);
        }
        
        virtual ~ImageProxyFI() {}
        
        virtual bool isValid() const {
            return m_fif != FIF_UNKNOWN;
        }
        
        virtual std::string getErrorMessage() const {
            return m_errorMessage;
        }
        
        virtual ImagePtr getImage() const {
            assert(m_fif != FIF_UNKNOWN);
            assert(m_stream);
            
            FreeImageIO io = createIO();
            FIBITMAP *bitmap = ::FreeImage_LoadFromHandle(m_fif, &io, (fi_handle)m_stream);
            assert(bitmap);
            return std::make_unique<ImageFI>(bitmap);
        }
        
    private:
        xe::Stream *m_stream;
        FREE_IMAGE_FORMAT m_fif = FIF_UNKNOWN;
        
        std::string m_errorMessage;
    };
    
    ImageProxyPtr ImageLoaderFI::createProxy(xe::Stream *stream) {
        assert(stream);
        
        return std::make_unique<ImageProxyFI>(stream);
    }
}
