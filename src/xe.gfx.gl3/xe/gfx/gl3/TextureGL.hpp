#pragma once

#ifndef __gl3_texture__
#define __gl3_texture__

#include <cassert>

#include "OpenGL.hpp"

#include "xe/DataType.hpp"
#include "xe/Vector.hpp"
#include "xe/gfx/Texture.hpp"

namespace xe {

    class TextureGL : public xe::Texture {
    public:
        TextureGL(const TextureDesc &desc, const PixelFormat sourceFormat, const DataType sourceType, const void* sourceData);

        GLuint getId() const {
            return m_id;
        }

        GLenum getTarget() const {
            return m_target;
        }

        virtual xe::TextureDesc getDesc() const override {
            return m_desc;
        }

        virtual xe::Buffer* getBuffer(xe::TextureCubeSide side = xe::TextureCubeSide::Unknown, size_t level = 0) override;

        virtual const xe::Buffer* getBuffer(xe::TextureCubeSide side = xe::TextureCubeSide::Unknown, size_t level = 0) const override;

    private:
        GLuint m_id = 0;
        GLenum m_target;
        TextureDesc m_desc;
    };

    typedef std::unique_ptr<TextureGL> TextureGLPtr;
}

#endif 
