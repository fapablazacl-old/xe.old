
#pragma once

#ifndef __xe_gfx_deviceinfo_hpp__
#define __xe_gfx_deviceinfo_hpp__

#include <xe/PreDef.hpp>
#include <string>
#include <iosfwd>

namespace xe {

    /**
     * @brief Underlying device implementation technology
     */
    enum class Driver {
        Software,   //! Software implementation
        D3D_10,     //! Microsoft Direct3D 10
        GL_1_5,     //! Fixed Function OpenGL
        GL_core,    //! OpenGL Core Profile
        GLES_1_1,   //! Fixed Function Embedded OpenGL
        GLES_2_0,   //! Embedded OpenGL
        VK          //! Vulkan
    };

    /** 
     * @brief Shader Language
     */
    enum class Language {
        GLSL,
        HLSL
    };
    
    /**
     * @brief Graphics SoundDevice description
     */
    struct GraphicsDeviceInfo {
        std::string name;
        std::string desc;
        Driver driver;
        Language lang;
    };

    extern XE_API bool operator== (const GraphicsDeviceInfo &info1, const GraphicsDeviceInfo &info2);

    inline bool operator!= (const GraphicsDeviceInfo &info1, const GraphicsDeviceInfo &info2) {
        return !(info1 == info2);
    }

    extern XE_API bool operator< (const GraphicsDeviceInfo &info1, const GraphicsDeviceInfo &info2);
}

extern XE_API std::ostream& operator<< (std::ostream& os, const xe::GraphicsDeviceInfo &info);

#endif
