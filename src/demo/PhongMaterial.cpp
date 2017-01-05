
#include "PhongMaterial.hpp"

#include <xe/gfx/GraphicsDevice.hpp>

namespace demo {

    static xe::UniformFormat s_format = {{
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

    PhongMaterial::PhongMaterial() {
        m_layers.resize(4);
    }

    PhongMaterial::~PhongMaterial() {}

    void PhongMaterial::render(xe::GraphicsDevice *device) {
        assert(device);

        // render material properties
        device->setUniform(&s_format, &m_properties);
    }
}
