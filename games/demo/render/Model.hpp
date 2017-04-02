
#pragma once

#ifndef __demo_model_hpp__
#define __demo_model_hpp__

#include "ModelPart.hpp"
#include <memory>

namespace demo {
    /** 
     * @brief Standard vertex definition
     */
    struct Vertex {
        xe::Vector3f coord;
        xe::Vector3f normal;
        xe::Vector2f texCoord;
        
        Vertex() {}

        Vertex(const xe::Vector3f &coord_, const xe::Vector3f &normal_, const xe::Vector2f &texCoord)
            : coord(coord_), normal(normal_), texCoord(texCoord) {}
    };

    struct ModelPartGeometry {
        std::vector<Vertex> vertices;
        std::vector<std::uint32_t> indices;
    };

    /**
     * @brief Geometric object
     */
    class Model {
    public:
        Model() {}

        virtual ~Model();

        std::size_t getPartCount() const;

        ModelPart* getPart(const std::size_t index);

        const ModelPart* getPart(const std::size_t index) const;

    private:
        std::vector<ModelPart> m_parts;
        std::vector<ModelPartGeometry> m_geometries;
    }; 
}

#endif
