
#pragma once

#ifndef __xe_gfx_programd3d10_hpp__
#define __xe_gfx_programd3d10_hpp__

#include <list>
#include <xe/gfx/Program.hpp>

namespace xe { namespace gfx {

    class ProgramD3D10 : public Program {
    public:
        ProgramD3D10(const std::list<ShaderSource> &sources);

        virtual ~ProgramD3D10();

        virtual int getUniform(const std::string &name) const override;

        virtual int getAttrib(const std::string &name) const override;
    };
}}

#endif
