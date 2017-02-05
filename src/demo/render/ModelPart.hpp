
#pragma once

#ifndef __demo_modelpart_hpp__
#define __demo_modelpart_hpp__

#include <vector>
#include <xe/Vector.hpp>
#include <xe/gfx/Material.hpp>
#include <xe/gfx/Mesh.hpp>

namespace demo {
    struct ModelPart {
        xe::gfx::Material *material = nullptr;
        xe::gfx::Mesh *mesh = nullptr;
    };
}

#endif
