
#include "PhongMaterial.hpp"

#include <xe/gfx/Device.hpp>

namespace demo {

    static xe::gfx::UniformFormat s_format = {{
        {"m_texture", 1, xe::DataType::Int32, 1},
        {"m_ambient", 4, xe::DataType::Float32, 1}, 
        {"m_diffuse", 4, xe::DataType::Float32, 1}, 
        {"m_specular", 4, xe::DataType::Float32, 1}, 
        {"m_emissive", 4, xe::DataType::Float32, 1}, 
        {"m_shininess", 1, xe::DataType::Float32, 1}
    }};

    static const std::vector<std::string> s_textureNames = {
        "m_texture"
    };

    PhongMaterial::PhongMaterial() {}

    PhongMaterial::~PhongMaterial() {}

    void PhongMaterial::render(xe::gfx::Device *device) {
        assert(device);

        // render material properties
        device->setUniform(&s_format, &m_properties);
    }
}
