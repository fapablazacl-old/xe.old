
#include "PhongLight.hpp"
#include "PhongPipeline.hpp"

namespace xe { 
    static xe::UniformFormat s_format = {{
        {"l_type", 1, xe::DataType::Int32, 1},
        {"l_ambient", 4, xe::DataType::Float32, 1}, 
        {"l_diffuse", 4, xe::DataType::Float32, 1}, 
        {"l_specular", 4, xe::DataType::Float32, 1}, 
        {"l_position", 3, xe::DataType::Float32, 1}, 
        {"l_direction", 3, xe::DataType::Float32, 1}
    }};

    PhongLight::PhongLight(PhongPipeline *pipeline) : m_pipeline(pipeline) {
        assert(pipeline);
    }

    PhongLight::~PhongLight() {}

    void PhongLight::render() {
        m_pipeline->getDevice()->setUniform(&s_format, &m_properties);
    }
}
