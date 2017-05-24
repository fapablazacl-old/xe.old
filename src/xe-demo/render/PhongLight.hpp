
#pragma once

#ifndef __xe_sg_phonglight_hpp__
#define __xe_sg_phonglight_hpp__

#include <cstdint>
#include <xe/math/Vector.hpp>
#include <xe/gfx/GraphicsDevice.hpp>
#include <xe/sg/Renderable.hpp>

namespace xe { 

    enum class LightType : std::int32_t {
        Point = 0,
        Directional = 1
    };

    struct PhongLightProperties {
        LightType type = LightType::Point;

        xe::Vector4f ambient = {0.2f, 0.2f, 0.2f, 1.0f};
        xe::Vector4f diffuse = {0.8f, 0.8f, 0.8f, 1.0f};
        xe::Vector4f specular = {0.0f, 0.0f, 0.0f, 1.0f};

        xe::Vector3f position = {0.0f, 0.0f, 0.0f};
        xe::Vector3f direction = {0.0f, 0.0f, -1.0f};
    };

    class PhongPipeline;
    class PhongLight : public Renderable {
    public:
        PhongLight(PhongPipeline *pipeline);

        virtual ~PhongLight();

        PhongLightProperties* getProperties() {
            return &m_properties;
        }

        const PhongLightProperties* getProperties() const {
            return &m_properties;
        }

        virtual void render() override;

    private:
        PhongLightProperties m_properties;
        PhongPipeline *m_pipeline;
    };
}

#endif
