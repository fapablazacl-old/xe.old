
#pragma once 

#ifndef __xe_gfx_program__
#define __xe_gfx_program__

#include <memory>
#include <string>

#include <xe/PreDef.hpp>
#include "xe/gfx/UniformFormat.hpp"
#include "xe/gfx/ShaderType.hpp"

namespace xe { 
    struct ShaderSource {
        ShaderType type;
        std::string source;
    };

    class XE_API Program {
    public:
        virtual ~Program();

        virtual int getUniform(const std::string &name) const = 0;

        virtual int getAttrib(const std::string &name) const = 0;
    };

    typedef std::unique_ptr<Program> ProgramPtr;
}

#endif 
