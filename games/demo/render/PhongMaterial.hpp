
#pragma once

#ifndef __demo_phongmaterial_hpp__
#define __demo_phongmaterial_hpp__

#include <xe/math/Vector.hpp>
#include <xe/gfx/Material.hpp>

namespace demo {
    class PhongMaterial : public xe::Material {
    public:
        struct Properties {
            int texture = 0;
            xe::Vector4f ambient = {0.2f, 0.2f, 0.2f, 1.0f};
            xe::Vector4f diffuse = {0.8f, 0.8f, 0.8f, 1.0f};
            xe::Vector4f specular = {0.0f, 0.0f, 0.0f, 1.0f};
            xe::Vector4f emission = {0.0f, 0.0f, 0.0f, 1.0f};
            float shininess = 0.0f;
        };

    public:
        PhongMaterial();

        virtual ~PhongMaterial();

        virtual void render(xe::GraphicsDevice *device) override;

        Properties* getProperties() {
            return &m_properties;
        }

        const Properties* getProperties() const {
            return &m_properties;
        }

    private:
        Properties m_properties;
    };
}

#endif
