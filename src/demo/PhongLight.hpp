
#pragma once

#include "Renderable.hpp"

#ifndef __xe_sg_phonglight_hpp__
#define __xe_sg_phonglight_hpp__

#include <cstdint>
#include <xe/Vector.hpp>
#include <xe/gfx/Device.hpp>

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

    class PhongLight : public Renderable {
    public:
        PhongLight();

        virtual ~PhongLight();

        PhongLightProperties* getProperties() {
            return &m_properties;
        }

        const PhongLightProperties* getProperties() const {
            return &m_properties;
        }

        void render(GraphicsDevice *device);

        virtual std::type_index getTypeIndex() const override {
            return std::type_index(typeid(PhongLight));
        }

    private:
        PhongLightProperties m_properties;
    };
}

#endif
