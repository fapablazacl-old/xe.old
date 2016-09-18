
#pragma once

#ifndef __xe_gfx_deviceinfo_hpp__
#define __xe_gfx_deviceinfo_hpp__

#include <xe/PreDef.hpp>
#include <string>
#include <iosfwd>

namespace xe { namespace gfx {
    /**
     * @brief Underlying device implementation technology
     */
    enum class Driver {
        Software,   //! Software implementation
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
        CG
    };
    
    /**
     * @brief Graphics Device description
     */
    struct DeviceInfo {
        std::string name;
        std::string desc;
        Driver driver;
        Language lang;
    };

    extern XE_API bool operator== (const DeviceInfo &info1, const DeviceInfo &info2);

    inline bool operator!= (const DeviceInfo &info1, const DeviceInfo &info2) {
        return !(info1 == info2);
    }

    extern XE_API bool operator< (const DeviceInfo &info1, const DeviceInfo &info2);
}}

extern XE_API std::ostream& operator<< (std::ostream& os, const xe::gfx::DeviceInfo &info);

#endif
