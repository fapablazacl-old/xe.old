
#pragma once

#ifndef __xe_gfx_deviceinfo_hpp__
#define __xe_gfx_deviceinfo_hpp__

#include <string>

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

    inline bool operator== (const DeviceInfo &info1, const DeviceInfo &info2) {
        if (info1.name != info2.name) {
            return false;
        }

        if (info1.desc != info2.desc) {
            return false;
        }

        if (info1.driver != info2.driver) {
            return false;
        }

        if (info1.lang != info2.lang) {
            return false;
        }

        return true;
    }

    inline bool operator!= (const DeviceInfo &info1, const DeviceInfo &info2) {
        return !(info1 == info2);
    }

    inline bool operator< (const DeviceInfo &info1, const DeviceInfo &info2) {
        if (info1.name >= info2.name) {
            return false;
        }

        if (info1.desc >= info2.desc) {
            return false;
        }

        if (info1.driver >= info2.driver) {
            return false;
        }

        if (info1.lang >= info2.lang) {
            return false;
        }

        return true;
    }
}}

#endif
