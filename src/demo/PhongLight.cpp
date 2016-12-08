
#include "PhongLight.hpp"

namespace xe { namespace sg {
    static xe::gfx::UniformFormat s_format = {{
        {"l_type", 1, xe::DataType::Int32, 1},
        {"l_ambient", 4, xe::DataType::Float32, 1}, 
        {"l_diffuse", 4, xe::DataType::Float32, 1}, 
        {"l_specular", 4, xe::DataType::Float32, 1}, 
        {"l_position", 3, xe::DataType::Float32, 1}, 
        {"l_direction", 3, xe::DataType::Float32, 1}
    }};

    PhongLight::PhongLight() {}

    PhongLight::~PhongLight() {}

    void PhongLight::render(xe::gfx::Device *device) {
        assert(device);

        device->setUniform(&s_format, &m_properties);
    }
}}
