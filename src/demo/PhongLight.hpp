
#pragma once

#include "Renderable.hpp"

#ifndef __xe_sg_phonglight_hpp__
#define __xe_sg_phonglight_hpp__

#include <cstdint>
#include <xe/Vector.hpp>
#include <xe/gfx/Device.hpp>

namespace xe { namespace sg {

    enum class LightType : std::int32_t {
        Point = 0,
        Directional = 1
    };

    struct PhongLightProperties {
        xe::Vector4f ambient = {0.0f, 0.0f, 0.0f, 1.0f};
        xe::Vector4f diffuse = {0.8f, 0.8f, 0.8f, 1.0f};
        xe::Vector4f specular = {0.0f, 0.0f, 0.0f, 1.0f};

        xe::Vector3f position = {0.0f, 0.0f, 0.0f};
        xe::Vector3f direction = {0.0f, 0.0f, 0.0f};

        LightType type = LightType::Directional;
    };

    class PhongLight : public Renderable {
    public:
        PhongLight();

        virtual ~PhongLight();

        PhongLightProperties getProperties() const {
            return m_properties;
        }

        void setProperties(const PhongLightProperties &properties) {
            m_properties = properties;
        }

        void render(xe::gfx::Device *device);

    private:
        PhongLightProperties m_properties;
    };
}}

#endif
